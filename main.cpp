#include "tree.h"
#include "model.h"
#include "memory_buffer.h"
#include "file_buffer.h"
#include "arithmetic_compressor.h"
#include <iostream>

int main(int argc, char* argv[]){

	uint in_size, out_size;
	float RC;

	if( argc < 4 ){
		std::cerr << "Too few arguments... " << std::endl;
		return 0;
	}

	std::string compress = std::string{argv[1]};
	std::string input_file_name = std::string{argv[2]};
	std::string output_file_name = std::string{argv[3]};

	// std::string lixo = "God of War is an action-adventure hack and slash video game series loosely based on Greek mythology, originally created by David Jaffe at Sony's Santa Monica Studio. Debuting in 2005, the series has become a flagship title for the PlayStation brand, consisting of seven games across multiple platforms. An eighth installment is currently in development; it will be a soft reboot for the series and will be loosely based on Norse mythology. The series' story centers around its playable character, Kratos, a Spartan warrior tricked into killing his wife and daughter by his former master, the God of War Ares. Kratos kills Ares at the behest of the goddess Athena and takes his place as the new God of War, but is still haunted by the nightmares of his past. Revealed to be a demigod and the son of Zeus, the King of the Olympian Gods who betrays Kratos, the Spartan then seeks revenge against the gods for their machinations. What follows is a series of attempts to free himself from the influence of the gods and the Titans and exact revenge. Santa Monica has developed all main entries, while Ready at Dawn and Javaground/Sony Online Entertainment-Los Angeles (SOE-LA) developed the three side games. Sony Interactive Entertainment (SIE; formerly Sony Computer Entertainment) has published all games except the mobile phone installment; it was published by Sony Pictures Digital. There are two eras of games in the God of War series. The first era are the first seven games, which are based on Greek mythology with vengeance as a central motif. Its main trilogy-God of War (2005), God of War II (2007), and God of War III (2010)-was released for the PlayStation 2 (PS2) and PlayStation 3 (PS3) video game consoles. The fourth main installment, Ascension (2013), a prequel to the entire series, was also released for the PS3 and features multiplayer. The three side games include Chains of Olympus (2008) and Ghost of Sparta (2010) for the PlayStation Portable (PSP), and Betrayal (2007) for mobile phones that support the Java Platform, Micro Edition (Java ME). Santa Monica is currently working on the eighth installment, also titled God of War (2018), for the PlayStation 4 (PS4). It will begin the second era, which will be based on Norse mythology. In addition to the individual games, two collections featuring remastered versions of both PS2 installments, God of War Collection (2009), and both PSP installments, Origins Collection (2011), were released on the PS3 by Bluepoint Games and Ready at Dawn, respectively. Another collection, God of War Saga (2012), was released for the PS3 and features God of War Collection, Origins Collection, and God of War III. Sanzaru Games ported God of War Collection to the PlayStation Vita in 2014. In celebration of the franchise's tenth anniversary, God of War III Remastered was released on PS4 in 2015 and was ported by Wholesale Algorithms. Games in the series have been praised for being the best action games for the PlayStation brand, and some of the best action games of all time. In June 2012, Sony reported that the series had sold more than 21 million copies worldwide. Strong sales and support of the series led to the franchise's expansion into other media, such as a comic book series-God of War (2010-11)-two novels-God of War (2010) and God of War II (2013)-and a web-based graphic novel-Rise of the Warrior (2012-13). Two documentaries have been produced and a film adaptation of the original installment has been in development since 2005. Merchandise promoting the series has also been produced, including artwork, clothing, toys, and prop replicas, as well as the games' soundtracks, including a heavy metal album, Blood & Metal (2010), featuring original music by various bands who were inspired by the series.";


	// MemorySymbolBuffer in1{lixo}, out2;
	// MemoryBitBuffer inter;

	// Model m{10};
	// ArithmeticCompressor comp{&m};

	// in_size = in1.size();
	// inter.writeBlock((uchar)10);
	// inter.writeBlock(in_size/8);
	// comp.encode(in1, inter);
	// out_size = inter.size();

	// RC = (float)in_size / out_size;
	// std::cout << "\nInput  size = " << in_size << " bits" << std::endl;
	// std::cout << "Output size = " << out_size << " bits" << std::endl;
	// std::cout << "RC          = " << RC << " : 1" << std::endl;

	// uchar x;
	// uint y;
	// inter.readBlock(x);
	// inter.readBlock(y);
	// comp.decode(inter, out2, y);
	// out2.print();
	// std::cerr << std::endl;

	if(compress == "-c"){

		uchar k;
		if( argc < 5 ) k = 2;
		else k = std::stoi(std::string{argv[4]});

		FileSymbolBuffer input{input_file_name};
		FileBitBuffer output{output_file_name};

		Model m{k};
		ArithmeticCompressor comp{&m};

		in_size = input.size();
		output.writeBlock(k);
		output.writeBlock(in_size/8);
		comp.encode(input, output);
		out_size = output.size();

		RC = (float)in_size / out_size;
		std::cout << "\nInput  size = " << in_size << " bits" << std::endl;
		std::cout << "Output size = " << out_size << " bits" << std::endl;
		std::cout << "RC          = " << RC << " : 1" << std::endl;
	}
	else{
		uchar k;
		uint num_symbols;

		FileBitBuffer input{input_file_name};
		FileSymbolBuffer output{output_file_name};

		input.readBlock(k);
		input.readBlock(num_symbols);
		Model m{k};
		ArithmeticCompressor comp{&m};
		comp.decode(input, output, num_symbols);
		std::cout << "\n";
	}

	return 0;
}