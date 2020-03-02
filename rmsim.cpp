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

	bool getregs(){
		std::string spec;
		
		
		while (true){
			getline(std::cin, spec); 
			//Allow the first line to be a comment
			if (spec[0] != '#'){
				break;
			}
		}
		
		//Regex to ensure the registers line is properly formatted. 
		std::regex checkregs ("[[:blank:]]*registers[[:blank:]+[:d:]+]*[[:blank:]]*");		
		if (!std::regex_match(spec, checkregs)){
			std::cout << "Registers invalid!\n";
			return false; 
		}
		std::string currnum = "";

		//Pull out the numbers and init the registers. We have already checked it is valid so can throw out any other characters
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

		return true;
	}
	bool getinstructions(){
		std::string currinst = "";

		while(getline(std::cin, currinst)){
			if ((currinst[0] != '#') && (currinst.length() > 0)){
				/*Poorly thought out attempt at doing a regex to check that the instructions are valid before I parse them

				`Some people, when confronted with a problem, think "I know, I'll use regular expressions." Now they have two problems.`
					- Jamie Zawinski

				Felt particularly relevant once I got it to work.
				*/ 

				std::regex checkinstrs("(([[:blank:]]*[[:alpha:]][[:w:]]*([[:blank:]]*):)?)([[:blank:]]*)((inc[[:blank:]+]([[:blank:]]*)r[[:d:]]+)|(decjz[[:blank:]+]([[:blank:]]*)r[[:d:]]+[[:blank:]+]([[:blank:]]*)[[:alpha:]][[:w:]]*))([[:blank:]]*)");

				if (!std::regex_match(currinst, checkinstrs)){
					std::cout << "Instruction invalid\n";
					std::cout << currinst << '\n';
					return false;
				} 

				//Split the line up
				std::vector<std::string> splitinstr;
				std::string curr = "";
				for (int i = 0; i < currinst.length(); i++){
					if (isalnum(currinst.at(i))){ //We split on whitespace
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
				
				if (splitinstr.size() == 4){ //Must be a decjz with a label
					instructions.push_back(instruction(splitinstr[0], decjz, std::stoi(splitinstr[2].substr(1)), splitinstr[3]));
				}
				else if (splitinstr.size() == 2){ //Must be an increment without a label
					instructions.push_back(instruction("", inc, std::stoi(splitinstr[1].substr(1)), ""));
				}
				else{
					if (splitinstr[1] == "inc"){ //In the case we have an increment with a label
						instructions.push_back(instruction(splitinstr[0], inc, std::stoi(splitinstr[2].substr(1)), ""));
					}
					else{ //In this case we have a decjz with no label
						instructions.push_back(instruction("", decjz, std::stoi(splitinstr[1].substr(1)), splitinstr[2]));
					}
				}
			}
		}
		return true;
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
			}

			//Ensure that the register exists
			extendregs(instructions[currinst].targreg);

			if (instructions[currinst].type == inc){
				registers[instructions[currinst].targreg] += 1; 
				currinst += 1;
			}
			else{ //decjz instruction
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
				else{ //Don't need to jump
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

	if(!sim.getregs()){
		return 1; 
	}

	if(!sim.getinstructions()) {
		return 1;
	}

	sim.run();

	sim.printregs();

	return 0; 
}
