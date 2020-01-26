#include <vector> 
#include <string> 
#include <iostream> 

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

	simulator(){
		currinst = 0;
	}

	void getregs(){
		std::string spec;
		getline(std::cin, spec); 
		
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
			
		}
	}
	void run(){

	}

	void printregs(){
		std::cout << "registers"; 
		for (int i = 0; i < registers.size(); i++){
			std::cout << " " << registers[i];
		}
		std::cout << '\n';
	}
};

int main(){
	simulator sim;
	sim.getregs(); 

	sim.getinstructions(); 

	sim.run();

	sim.printregs();
}
