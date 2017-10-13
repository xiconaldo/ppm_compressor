#include "arithmetic_compressor.h"

ArithmeticCompressor::ArithmeticCompressor(Model* model){
	this->model = model;
}

void ArithmeticCompressor::encode(SymbolBuffer& input, BitBuffer& output){

	uint low = 0x00000000U;
	uint high = 0x7FFFFFFFU;

	uint range;
	ulong aux;
	int pending_bits = 0;
	Symbol symbol;
	Context context;
	ProbabilitiesSet prob;

	while( !input.eof() ){

		input >> symbol;
		prob = model->getSymbolProbability(context, symbol);
		int siz = prob.size();
		for(ProbabilityRange p : prob){

			range = (high - low + 1) / p.den;
			high = low + range * p.high_num - 1;
			low =  low + range * p.low_num;

			while( high < g_Half || low >= g_Half){
				if(high < g_Half){
					output << 0;
					high <<= 1;
					low <<= 1;
					high += 1U;

					while ( pending_bits ){
						pending_bits--;
						output << 1;
					}
				}
				else if(low >= g_Half){
					output << 1;

					high -= g_Half;
					low -= g_Half;
					high <<= 1;
					low <<= 1;
					high += 1U;

					while ( pending_bits ){
						output << 0;
						pending_bits--;
					}
				}
			}
			
			while ( low >= g_FirstQuarter && high < g_ThirdQuarter ){
				pending_bits++;
				high -= g_FirstQuarter;
				low -= g_FirstQuarter;
				low <<= 1;
				high <<= 1;
				high += 1U;
			}
		}

		model->updateModel(context, symbol);
		context.push_back(symbol);
		if(context.size() > model->getK()) context.pop_front();
		
	}

	if( low < g_FirstQuarter ){
        output << 0;
        for( int i = 0; i < pending_bits+1; i++ )
            output << 1;
    }
    else {
        output << 1;
    }
}

void ArithmeticCompressor::decode(BitBuffer& input, SymbolBuffer& output, int size){

	model->clearModel();

	uint low = 0x00000000U;
	uint high = 0x7FFFFFFFU;
	uint range;
	uint value;
	Bit bit;
	bool minus_1_flag = false;
	uint count;
	uint aux_count;

	Symbol symbol;
	Context context;
	Context aux_context;
	ProbabilitiesSet prob;
	int pending_bits = 0;

	uint i = 31;
	for (; i > 0 ; i-- ) {
		input >> bit;
		value <<= 1;
		value += bit;
	}

	while(true) {
		aux_context = context;
		minus_1_flag = false;

		while(true){

			while(true){
				if(minus_1_flag){
					aux_count = model->getCount(-1);
					break;
				}

				aux_count = model->getCount(aux_context);
	
				if( aux_count ) break;
				if( aux_context.empty() ){
					minus_1_flag = true;
					aux_count = model->getCount(-1);
					break;
				}
				aux_context.pop_front();
			}

			range = (high - low + 1) / aux_count;
			count = (value - low) / range;

			if( !minus_1_flag ){
				symbol = model->getSymbol(aux_context, count);
				prob = model->getSymbolProbability(aux_context, symbol);
			}
			else{
				symbol = model->getSymbol(-1, count);
				prob = model->getSymbolProbability(-1, symbol);
				minus_1_flag = false;
			}

			auto p = prob[0];

			high =  low + range * p.high_num - 1;
			low =  low + range * p.low_num;
			
			while( low >= g_Half || high < g_Half ) {
				if( high < g_Half){
					low <<= 1;
					high <<= 1;
					value <<= 1;

					high += 1U;
					input >> bit;
					value += bit;
					
				}
				else if( low >= g_Half){
					low -= g_Half;
					high -= g_Half;
					value -= g_Half;

					low <<= 1;
					high <<= 1;
					value <<= 1;

					high += 1U;
					input >> bit;
					value += bit;
				}

				pending_bits = 0;
			}

			while( low >= g_FirstQuarter && high < g_ThirdQuarter){
				pending_bits++;
				low -= g_FirstQuarter;
				high -= g_FirstQuarter;
				value -= g_FirstQuarter;

				low <<= 1;
				high <<= 1;
				value <<= 1;

				high += 1U;
				input >> bit;
				value += bit;
				
			}

			if(symbol > 255){
				if(!aux_context.empty())
					aux_context.pop_front();
				else
					minus_1_flag = true;
			}
			else{
				break;
			}
		}
		
		output << symbol;
		if(--size == 0) break;
		model->updateModel(context, symbol);
		context.push_back(symbol);
		if(context.size() > model->getK()) context.pop_front();
	}
}