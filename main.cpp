#include "tree.h"
#include "model.h"
#include "memory_buffer.h"
#include "file_buffer.h"
#include <iostream>

int main(){

	Model m;
	ProbabilitiesSet pp;
	MemorySymbolBuffer message{"abracadabra"};
	Context ctx;
	Symbol sym;
	uint siz;

	while(!message.eof()){
		message >> sym;
		pp = m.getSymbolProbability(ctx, sym);
		siz = pp.size();
		for(ProbabilityRange p : pp){
			if(--siz == 0)
				std::cout << (char)sym << " ";
			else
				std::cout << "ESC ";
			std::cout << "["  << p.low_num << "/" << p.den << ", " << p.high_num << "/" << p.den << ")" << std::endl;
		}
		m.updateModel(ctx, sym);
		ctx.push_back(sym);
		if( ctx.size() > 2) ctx.pop_front();
	}

	return 0;
}