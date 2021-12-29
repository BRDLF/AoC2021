#include <iostream>
#include <fstream>
#include <set>
#include <map>

int main(){
	std::fstream input("test.txt");
	
	std::set<char> charset;
	std::string polymerTemplate;
	std::map<std::string, char> pairInsertion;

	if(!input.is_open()){
		std::cerr << "Could not open file\n\n";
	}
	else{
		std::string linebuffer;
		getline(input, polymerTemplate);
		std::cout << polymerTemplate;
		while(input >> linebuffer){
			std::string pt1 = linebuffer;
			std::cout << std::endl << linebuffer << " ";
			input >> linebuffer;
			std::cout << linebuffer << " ";
			input >> linebuffer;
			std::cout << linebuffer << " ";
			char pt2 = linebuffer[0];
			pairInsertion.insert(std::pair<std::string, char>(pt1, pt2));
		}


	}
	
	
	char c;
	std::cin >> c;
	return 0;
}