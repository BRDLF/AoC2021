#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

void foldPaper(set<pair<int,int>> &fpaper, pair<int,int> ffold, int &fmx, int &fmy);
void showPaper(int fmx, int fmy, set<pair<int,int>> fpaper);

int main(){
	fstream input("Day13.txt");
	set<pair<int,int>> paper_holes;
	if(!input.is_open()){
		cerr << "Could not open file\n\n";
	}
	else{
		string linebuffer;
		queue<pair<int,int>> fold_line;
		int mx = 0;
		int my = 0;
		while(input >> linebuffer){
			int ix = 0;
			int iy = 0;
			int pos = linebuffer.find(",");
			if(pos==string::npos){
				if(pos = linebuffer.find("=")!=string::npos){
					if(linebuffer.substr(pos-1, 1) == "x") ix = stoi(linebuffer.substr(pos+1,linebuffer.length()-(pos+1)), nullptr, 10);
					if(linebuffer.substr(pos-1, 1) == "y") iy = stoi(linebuffer.substr(pos+1,linebuffer.length()-(pos+1)), nullptr, 10);
					//cout << linebuffer.substr(pos-1, linebuffer.length()-(pos-1)) << endl;
					//cout << "<" << ix << "," << iy << ">\n";
					fold_line.push(pair<int,int>(ix, iy));
				} 
				
			}
			else{
				//cout << linebuffer << ": ";
				ix = stoi(linebuffer.substr(0, pos), nullptr, 10);
				linebuffer.erase(0, pos + 1);
				iy = stoi(linebuffer.substr(0, linebuffer.length()), nullptr, 10);
				//cout << "<" << ix << "," << iy << ">\n";
				mx = mx > ix ? mx : ix;
				my = my > iy ? my : iy;
				//cout << "<" << mx << "," << my << ">" << endl;
				paper_holes.insert(pair<int,int>(ix, iy));
			}
		}
		mx++; my++;
		cout << endl;

		while(fold_line.size() != 0){
			foldPaper(paper_holes, fold_line.front(), mx, my);
			fold_line.pop();
		}
		
		showPaper(mx, my, paper_holes);
		
		cout << endl;
	}

	cout << "Visible holes: " << paper_holes.size() << endl;
	char c;
	cin >> c;
	return 0;
}

void foldPaper(set<pair<int,int>> &fpaper, pair<int,int> ffold, int &fmx, int &fmy){
	set<pair<int,int>> bpaper;
	set<pair<int,int>>::iterator it=bpaper.begin();
	if(ffold.first == 0) fmy = ffold.second;
	if(ffold.second == 0) fmx = ffold.first;
	while(!fpaper.empty()){
		set<pair<int,int>>::iterator it = fpaper.begin();
		pair<int,int> eval = *it;
		if(ffold.first == 0 && eval.second != ffold.second){ //vertical fold
		eval.second = eval.second > ffold.second ? (ffold.second - (eval.second - ffold.second)) : eval.second;
		}
		if(ffold.second == 0 && eval.first != ffold.first){ //horizontal fold
		eval.first = eval.first > ffold.first ? (ffold.first - (eval.first - ffold.first)) : eval.first;
		}
		bpaper.insert(eval);
		fpaper.erase(it);
	}
	fpaper = bpaper;
}

void showPaper(int fmx, int fmy, set<pair<int,int>> fpaper){
	bool tp[fmx][fmy];
		for(int lx = 0 ; lx < fmx ; lx++){
			for(int ly = 0 ; ly < fmy ; ly++){
				tp[lx][ly] = false;
			}
		}
		for(set<pair<int,int>>::iterator it = fpaper.begin() ; it != fpaper.end() ; it++){
				pair<int,int> bp= *it;
				tp[bp.first][bp.second] = true;
				//cout << "<" << bp.first << "," << bp.second << ">\n";
		}
		for(int ly = 0 ; ly < fmy ; ly++){
			for(int lx = 0 ; lx < fmx ; lx++){
				if(tp[lx][ly] == false) cout << ".";
				if(tp[lx][ly] == true) cout << "#";
			}
			cout << endl;
		}
}