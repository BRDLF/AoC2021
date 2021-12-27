#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <ctype.h>

using namespace std;
using Cave = map<string, set<string>>;
using Route = map<string, bool>;

Cave theCave;
set<string> routes;

bool addRoom(Cave &fcave, string froom);
void addLink(Cave &fcave, string froom1, string froom2);
void printCave(Cave fcave);
void traverseCave(Cave &fcave);
string currRouteRoom(string froute);
void moveRoute(Cave &fcave, set<string> &froutes);
bool isVisitable(string froute, string froom);
bool isVisitable(string froute, string froom, bool &fdubsmall);

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

	moveRoute(theCave, routes);

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

	Route droutes;
	droutes["start"] = false;

	Route::iterator it = droutes.begin();
	while(droutes.empty()==false){
		//get the active room
		string lroom = currRouteRoom(it->first);
		//if we are in the end, go to the next stored route and skip the eval
		if(lroom == "end"){
			cout << "Current route: " << it->first << endl;
			//cout << "We found end, skipping\n";
			froutes.insert(it->first);
			droutes.erase(it->first); 
			it = droutes.begin();
			continue;
		}

		//cout << endl << lroom << "\n---\n";
		//for each connected room to current
		auto const &caveit = fcave.at(lroom);
		for(auto const &lstring: caveit){
			//if we can visit it
			//cout << lstring << ": ";
			bool dubsmall = it->second;
			if(isVisitable(it->first, lstring, dubsmall)){
				//create a new route
				string toAppend = it->first;
				toAppend.append(",").append(lstring);
				//cout << "toAppend: " << toAppend << endl;
				droutes[toAppend] = dubsmall;
			}
		}

		droutes.erase(it->first); 
		it = droutes.begin();
	}
}

bool isVisitable(string froute, string froom, bool &fdubsmall){
	if (froom == "start"){
		//cout << "Can't revisit start\n\n";
		return false;												//We can't visit the start room again.
	}
	if (isupper(froom[0])){
		//cout << "Big room\n\n";
		return true;												//If "Large" room, always return false "Can be visited"
	} 
	
	if (froute.find(froom) != string::npos){				//If small room is in froute
		if(fdubsmall == false){ 								//If we haven't double dipped a small room
		//cout << "Using dubsmall\n\n";
		fdubsmall = true;											//set dubsmall to true ("We have visited a small room twice")
		return true;												//travel to small room
	}
	  else{
		//cout << "Has visited\n\n";
		return false;												//If small room is in froute and we have used our double visit, return true "Cannot be visited"
	  }
	}
	else{
		//cout << "Hasn't been visited\n\n";
		return true;												//If not found, return false. "Can be visited"
	}
}