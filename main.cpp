#include "tree.h"
#include "model.h"
#include "memory_buffer.h"
#include "file_buffer.h"
#include <iostream>

int main(){

	Model m;
	ProbabilitiesSet pp;
	std::string message = "abracadabra";
	Context ctx;
	Symbol sym;
	uint siz;

	for(char c : message){
		sym = (Symbol)c;
		pp = m.getSymbolProbability(ctx, sym);
		siz = pp.size();
		for(ProbabilityRange p : pp){
			if(--siz == 0)
				std::cout << (ushort)sym << " ";
			else
				std::cout << "ESC ";
			std::cout << "["  << p.low_num << "/" << p.den << ", " << p.high_num << "/" << p.den << ")" << std::endl;
		}
		m.updateModel(ctx, sym);
		ctx.push_back(sym);
		if( ctx.size() > 2) ctx.pop_front();
	}

	for(uint i = 0; i <= 11; i++)
		std::cout << i << " " << m.getSymbol( Context{ 'a' }, i ) << std::endl;

	return 0;
}