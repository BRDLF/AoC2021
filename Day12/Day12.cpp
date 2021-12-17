#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>

using namespace std;
using Cave = map<string, set<string>>;

Cave theCave;

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
	
	addLink(theCave, "start", "A");
	addLink(theCave, "start", "b");
	addLink(theCave, "A", "c");
	addLink(theCave, "A", "b");
	addLink(theCave, "b", "d");
	addLink(theCave, "A", "end");
	addLink(theCave, "b", "end");

	printCave(theCave);

	char c;
	cin >> c;
	return 0;
}