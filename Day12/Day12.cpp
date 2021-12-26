#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;
using Cave = map<string, set<string>>;

Cave theCave;
list<list<string>> routes;

bool addRoom(Cave &fcave, string froom){
	set<string> mtset;
	auto rval = fcave.emplace(pair<string, set<string>>(froom, mtset));
	return rval.second;
}

void addLink(Cave &fcave, string froom1, string froom2){
		addRoom(fcave, froom1);
		addRoom(fcave, froom2);
		fcave.at(froom1).insert(froom2);
		fcave.at(froom2).insert(froom1);
	
	
}

void printCave(Cave fcave){
	for (auto const &pair: fcave) {
      	cout << "{" << pair.first << ": ";
				for(auto const &lstring: pair.second){
					cout << lstring << ", ";
				}
			cout << "}\n";
    }
	cout << endl;
}
int main(){
	fstream input("Day12.txt");
	if(!input.is_open()){
		cerr << "Couldn't open file\n";
	}
	else{
		string linebuffer;
		while(input >> linebuffer){
			// cout << linebuffer << endl;
			int pos = linebuffer.find('-');
			addLink(theCave, linebuffer.substr(0, pos), linebuffer.substr(pos+1, linebuffer.size() - pos));
		}
	}

	

	printCave(theCave);

	char c;
	cin >> c;
	return 0;
}