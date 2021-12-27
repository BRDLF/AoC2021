#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <ctype.h>

using namespace std;
using Cave = map<string, set<string>>;

Cave theCave;
set<string> routes;

bool addRoom(Cave &fcave, string froom);
void addLink(Cave &fcave, string froom1, string froom2);
void printCave(Cave fcave);
void traverseCave(Cave &fcave);
string currRouteRoom(string froute);
void moveRoute(Cave &fcave, set<string> &froutes);
bool isVisited(string froute, string froom);

int main(){
	fstream input("day12.txt");
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

	routes.insert("start");
	moveRoute(theCave, routes);

	//cout << theCave["start"][0];

	cout << "Routes: " << routes.size() <<endl;
	char c;
	cin >> c;
	return 0;
}


//Fun Starts Now

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
	return;
}

string currRouteRoom(string froute){
	int pos = froute.rfind(',');
	if (pos != string::npos){
		//cout << froute.substr(pos + 1, froute.length()-(pos + 1)) << endl;
		return froute.substr(pos + 1, froute.length()-(pos + 1));
	}
	//cout << froute << endl;
	return froute;
}

void moveRoute(Cave &fcave, set<string> &froutes){

	set<string>::iterator it = froutes.begin();
	do{
		//cout << "Current route: " << *it << endl;
		//get the active room
		string lroom = currRouteRoom(*it);
		//if we are in the end, go to the next stored route and skip the eval
		if(lroom == "end"){
			it++;
			continue;
		}

		//cout << endl << lroom << "\n---\n";
		//for each connected room to current
		auto const &caveit = fcave.at(lroom);
		for(auto const &lstring: caveit){
			//if we can visit it
			//cout << lstring << ": ";
			if( !isVisited(*it, lstring)){
				//create a new route
				string toAppend = *it;
				toAppend.append(",").append(lstring);
				//cout << "toAppend: " << toAppend << endl;
				froutes.insert(toAppend);
			}
		}

		froutes.erase(*it); 
		it = froutes.begin();
	}while(it != froutes.end());
}

bool isVisited(string froute, string froom){
	if (isupper(froom[0])){
		//cout << "Big room\n\n";
		return false;												//If "Large" room, always return false "Can be visited"
	} 
	if (froute.find(froom) != string::npos){
		//cout << "true\n\n";
		return true;												//If room is in froute, return true "Cannot be visited"
	}
	else{
		//cout << "false\n\n";
		return false;												//If not found, return false. "Can be visited"
	}
}