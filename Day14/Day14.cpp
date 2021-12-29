#include <iostream>
#include <fstream>
#include <climits>
#include <set>
#include <map>
using pC = std::map<std::string, unsigned long long>;
const int STEPS = 40;

pC genEmptyCount(std::map<std::string, char> fpI);
void initialize(pC &fpCount, std::string fpT);
void showCounts(pC fpC);
void showInsertions(std::map<std::string, char> fpI);
void polymerize(pC &fpC, std::map<std::string, char> fpI);
std::map<char, unsigned long long> genemptyEC(pC fpC);
void countElems(pC fpC);

int main(){
	std::fstream input("Day14.txt");
	
	//std::map<char, unsigned long long> elemCount;
	
	std::string polymerTemplate;

	std::map<std::string, char> pairInsertion;

	if(!input.is_open()){
		std::cerr << "Could not open file\n\n";
	}
	else{
		std::string linebuffer;
		getline(input, polymerTemplate);
		std::cout << polymerTemplate << "\n";
		while(input >> linebuffer){
			std::string pt1 = linebuffer;
			input >> linebuffer;
			input >> linebuffer;
			char pt2 = linebuffer[0];
			pairInsertion.insert(std::pair<std::string, char>(pt1, pt2));
			//elemCount.insert(std::pair<char, unsigned long long>(pt2, 0));
		}
	pC pairCount = genEmptyCount(pairInsertion);
	initialize(pairCount, polymerTemplate);
	//showInsertions(pairInsertion);
	showCounts(pairCount);
	for(int x = 0; x < STEPS ; x++){
		polymerize(pairCount, pairInsertion);
	}
	showCounts(pairCount);
	countElems(pairCount);
	}

	char c;
	std::cin >> c;
	return 0;
}

void initialize(pC &fpCount, std::string fpT){
	for(int l = 0 ; l < fpT.size()-1;l++){
		std::string substr = fpT.substr(l, 2);
		for(pC::iterator it = fpCount.begin() ; it != fpCount.end() ; it++){
			if(substr==it->first){
				it->second++;
			}
		}
	}
}

pC genEmptyCount(std::map<std::string, char> fpI){
	pC toReturn;
	std::map<std::string, char>::iterator fit;
	for(fit=fpI.begin(); fit!=fpI.end(); ++fit)
    {
        std::pair<std::string,unsigned long long> p (fit->first,0);
        toReturn.insert(p);
    }
    return toReturn;
}


void showCounts(pC fpC){
	for(std::map<std::string, unsigned long long>::iterator it = fpC.begin() ; it != fpC.end() ; it++){
		if(it->second > 0){
			std::cout << it->first << " " << it->second << "\n";
		}
	}
	std::cout << "\n";
}

void showInsertions(std::map<std::string, char> fpI){
	for(std::map<std::string, char>::iterator it = fpI.begin(); it != fpI.end() ; it++){
		std:: cout << "<" << it->first << ", " << it->second << ">\n";
	}
}

void polymerize(pC &fpC, std::map<std::string, char> fpI){
	pC newCounts = genEmptyCount(fpI);
	
	for(pC::iterator fit = fpC.begin() ; fit != fpC.end() ; fit++){
		if(fit->second > 0){
			std::string cs = fit->first;
			char toIns = fpI.at(cs);
			std::string ns1 = cs.substr(0, 1).insert(1, 1, toIns);
			std::string ns2 = cs.substr(1, 1).insert(0, 1, toIns);
			newCounts.at(ns1) += fit->second;
			newCounts.at(ns2) += fit->second;
		}
	}
	fpC = newCounts;
	return;
}

std::map<char, unsigned long long> genemptyEC(pC fpC){
	std::map<char, unsigned long long> toReturn;
	for(pC::iterator fit = fpC.begin() ; fit != fpC.end() ; fit++){

		char c1 = fit->first.front();
		char c2 = fit->first.back();

		toReturn.insert(std::pair<char, unsigned long long>(c1, 0));
		toReturn.insert(std::pair<char, unsigned long long>(c1, 0));
	}
	return toReturn;
}

void countElems(pC fpC){
	std::map<char, unsigned long long> eC = genemptyEC(fpC);
	unsigned long long high = 0;
	unsigned long long low = ULLONG_MAX;
	for(pC::iterator fit = fpC.begin() ; fit != fpC.end() ; fit++){
		char c1 = fit->first.front();
		char c2 = fit->first.back();
		eC.at(c1) += fit->second;
		eC.at(c2) += fit->second;
	}

	for(std::map<char, unsigned long long>::iterator fit = eC.begin() ; fit!=eC.end() ; fit++){
		unsigned long long iC = fit->second;
		iC = (iC+1)/2;
		high = iC > high ? iC : high;
		low = iC < low ? iC : low;
		std::cout << fit->first << ": " << fit->second << ": " << iC << "\n";
	}
	std::cout << "\nH: " << high << " L: " << low << "\nD: " << high-low << "\n";
	return;
}