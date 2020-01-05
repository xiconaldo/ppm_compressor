#include "arithmetic_compressor.h"

ArithmeticCompressor::ArithmeticCompressor(uchar k, uint tree_mode) :
	model{k, tree_mode}
{}

void ArithmeticCompressor::encode(SymbolBuffer& input, BitBuffer& output, double& entropy, bool clear_model){

	uint low = 0x00000000U;
	uint high = 0x7FFFFFFFU;

	uint range;
	uint percent = 0;
	uint total_percent = input.size()/8;
	uint pending_bits = 0;
	Symbol symbol;
	Context context;
	ProbabilitiesSet prob;
	entropy = 0.0;

	while( !input.eof() ){
		input >> symbol;
		prob = model.getProbabilities(context, symbol);

		for(ProbabilityRange p : prob){

			entropy -= std::log2(double(p.high_num - p.low_num)/p.den);

			range = (high - low + 1) / p.den;
			high = low + range * p.high_num - 1;
			low =  low + range * p.low_num;

			while( high < ONE_HALF || low >= ONE_HALF){
				if(high < ONE_HALF){
					output << 0;
					high <<= 1;
					low <<= 1;
					high += 1U;

					while ( pending_bits ){
						pending_bits--;
						output << 1;
					}
				}
				else if(low >= ONE_HALF){
					output << 1;

					high -= ONE_HALF;
					low -= ONE_HALF;
					high <<= 1;
					low <<= 1;
					high += 1U;

					while ( pending_bits ){
						output << 0;
						pending_bits--;
					}
				}
			}

			while ( low >= ONE_QUARTER && high < THREE_QUARTERS ){
				pending_bits++;
				high -= ONE_QUARTER;
				low -= ONE_QUARTER;
				low <<= 1;
				high <<= 1;
				high += 1U;
			}
		}

		if(++percent % 10000U == 0 || percent == total_percent)
			std::cerr << "\rCompressing " << std::setw(percent*40/total_percent) << std::setfill('|') << ""
					  << std::setw(40-percent*40/total_percent) << std::setfill(' ') << ""
					  << std::fixed << std::setw(7) << std::setprecision(2)
					  << percent * 100.0f / total_percent << " %";

		model.updateModel(context, symbol);
		context.push_back(symbol);
		if(context.size() > model.getK()) context.pop_front();

	}

	if( low < ONE_QUARTER ){
        output << 0;
        for( uint i = 0; i < pending_bits+1; i++ )
            output << 1;
    }
    else {
        output << 1;
	}

	entropy /= total_percent;
	if(clear_model) model.clearModel();
}

void ArithmeticCompressor::decode(BitBuffer& input, SymbolBuffer& output, uint size, bool clear_model){

	uint low = 0x00000000U;
	uint high = 0x7FFFFFFFU;
	uint range, value = 0U, count, aux_count;
	uint total_percent = size;
	uint percent = 0;
	bool minus_1_flag = false;

	Bit bit;
	Symbol symbol;
	Context context, aux_context;
	ProbabilityRange prob;

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
					aux_count = model.getContextSize();
					break;
				}

				aux_count = model.getContextSize(aux_context);

				if( aux_count ) break;
				if( aux_context.empty() ){
					minus_1_flag = true;
					aux_count = model.getContextSize();
					break;
				}
				aux_context.pop_front();
			}

			range = (high - low + 1) / aux_count;
			count = (value - low) / range;

			if( !minus_1_flag ){
				symbol = model.getSymbol(aux_context, count);
				prob = model.getSingleProbability(aux_context, symbol);
			}
			else{
				symbol = model.getSymbol(count);
				prob = model.getSingleProbability(symbol);
				minus_1_flag = false;
			}

			high =  low + range * prob.high_num - 1;
			low =  low + range * prob.low_num;

			while( low >= ONE_HALF || high < ONE_HALF ) {
				if( high < ONE_HALF){
					low <<= 1;
					high <<= 1;
					value <<= 1;

					high += 1U;
					input >> bit;
					value += bit;

				}
				else if( low >= ONE_HALF){
					low -= ONE_HALF;
					high -= ONE_HALF;
					value -= ONE_HALF;

					low <<= 1;
					high <<= 1;
					value <<= 1;

					high += 1U;
					input >> bit;
					value += bit;
				}
			}

			while( low >= ONE_QUARTER && high < THREE_QUARTERS){

				low -= ONE_QUARTER;
				high -= ONE_QUARTER;
				value -= ONE_QUARTER;

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

		if(++percent % 10000U == 0 || percent == total_percent)
			std::cerr << "\rDecompressing " << std::setw(percent*38/total_percent) << std::setfill('|') << ""
					  << std::setw(38-percent*38/total_percent) << std::setfill(' ') << ""
					  << std::fixed << std::setw(7) << std::setprecision(2)
					  << percent * 100.0f / total_percent << " %";

		if(--size == 0) break;
		model.updateModel(context, symbol);
		context.push_back(symbol);
		if(context.size() > model.getK()) context.pop_front();
	}

	if(clear_model) model.clearModel();
}
