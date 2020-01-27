#include <vector> 
#include <string> 
#include <iostream> 
#include <regex>

enum instrtype{
	inc, decjz
}; 

class instruction{
	public:
	std::string label;
	instrtype type;
	unsigned long long int targreg; 
	std::string jumplabel;

	instruction(std::string l, instrtype t, unsigned long long int targ, std::string jump){
		label = l; 
		type = t; 
		targreg = targ; 
		jumplabel = jump;
	}
};

class simulator{
	public:
	std::vector<unsigned long long int> registers; 
	std::vector<instruction> instructions;
	int currinst;
	bool trace; 

	simulator(){
		currinst = 0;
		trace = false;
	}

	void getregs(){
		std::string spec;
		
		
		while (true){
			getline(std::cin, spec); 
			//Allow the first line to be a comment
			if (spec[0] != '#'){
				break;
			}
		}
		
		std::string currnum = "";

		for (int i = 0; i < spec.length(); i++){
			char a = spec.at(i); 
			if (isdigit(a)){
				currnum += a;
			}
			else{
				if (currnum.length() > 0){
					registers.push_back(std::stoi(currnum));
				}
				currnum = "";
			}
		}

		if (currnum.length() > 0){
			registers.push_back(std::stoi(currnum));
		}
	}
	void getinstructions(){
		std::string currinst = "";
		while(getline(std::cin, currinst)){
			if (currinst[0] != '#'){
				//Split the line up
				std::vector<std::string> splitinstr;
				std::string curr = "";
				for (int i = 0; i < currinst.length(); i++){
					if (isalnum(currinst.at(i))){
						curr += currinst.at(i);
					}
					else{
						if(curr.length() > 0){
							splitinstr.push_back(curr);
						}
						curr = "";
					}
				}

				if(curr.length() > 0){
					splitinstr.push_back(curr);
				}
				if (splitinstr.size() == 0){
					break; 
				}
				
				if (splitinstr.size() == 4){
					instructions.push_back(instruction(splitinstr[0], decjz, std::stoi(splitinstr[2].substr(1)), splitinstr[3]));
				}
				else if (splitinstr.size() == 2){
					instructions.push_back(instruction("", inc, std::stoi(splitinstr[1].substr(1)), ""));
				}
				else{
					if (splitinstr[1] == "inc"){
						instructions.push_back(instruction(splitinstr[0], inc, std::stoi(splitinstr[2].substr(1)), ""));
					}
					else{
						instructions.push_back(instruction("", decjz, std::stoi(splitinstr[1].substr(1)), splitinstr[2]));
					}
				}
			}
		}
	}

	void extendregs(unsigned long long reg){
		//If the register being asked for doesn't exist
		if (reg >= registers.size()){
			int currsize = registers.size();
			registers.resize(reg + 1); //Resize the registers 
			for (int i = currsize; i <= reg; i++){ //Init the values
				registers[i] = 0;
			}
		}
	}

	void run(){
		while(true){
			if (currinst >= instructions.size()){
				break;
			}

			if(trace){
				printregs();
				//std::cout << instructions[currinst].label << "-" << instructions[currinst].type << "-r" << instructions[currinst].targreg << "-" << instructions[currinst].jumplabel << '\n'; 
			}

			//Ensure that the register exists
			extendregs(instructions[currinst].targreg);

			if (instructions[currinst].type == inc){
				registers[instructions[currinst].targreg] += 1; 
				currinst += 1;
			}
			else{
				if (registers[instructions[currinst].targreg] == 0){
					//Need to jump
					if (instructions[currinst].jumplabel == "HALT"){
						return;
					}
					else{
						int found = 0; 

						for (int i = 0; i < instructions.size(); i++){
							if (instructions[i].label == instructions[currinst].jumplabel){
								found += 1; 
								currinst = i; 
								break;
							}
						}

						if (found != 1){
							std::cout << "Label: " << instructions[currinst].jumplabel << "invalid!" << '\n'; 
							return; 
						}

					}
				}
				else{
					registers[instructions[currinst].targreg] += -1;
					currinst += 1;
				}
			}
		}
	}

	void printregs(){
		std::cout << "registers"; 
		for (int i = 0; i < registers.size(); i++){
			std::cout << " " << registers[i];
		}
		std::cout << '\n';
	}
};

int main(int argc, char* argv[]){
	simulator sim;

	if (argc > 1){
		if (std::string(argv[1]) == "-t"){
			sim.trace = true;
		}
	}

	sim.getregs(); 

	sim.getinstructions(); 

	sim.run();

	sim.printregs();

	return 0; 
}
