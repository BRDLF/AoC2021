#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using octogrid = vector <vector <int>>;

const int cycles = 100;


void show_grid(octogrid fgrid){
	cout << "Showgrid\n";
	for (int x = 0 ; x < fgrid.size() ; x++){
		for (int y = 0 ; y < fgrid[x].size() ; y++){
			cout << fgrid[x][y];
		}
		cout << endl;
	}
	return;
}

void octoburst(octogrid &fgrid, int col, int row){
	cout << "Octoburst\n";			//showing numpad notation of what number we are checking in respect to 
	fgrid[col][row] = 200;			//5 ; This is to set to an "impossibly high" number so that we can track who has already burst this cycle. To be set to 0 later
	if(col!=0){
		fgrid[col-1][row]++; 		//4
		if(row!=0){
			fgrid[col-1][row-1]++;	//7
		}
		if(row+1!=fgrid[col].size()){
			fgrid[col-1][row+1]++;	//1
		}
	}
	if(row!=0){
		fgrid[col][row-1]++;			//8
	}
	if(row+1!=fgrid[col].size()){
		fgrid[col][row+1]++;			//2
	}
	if(col+1!=fgrid.size()){
		int ncol = col+1;
		fgrid.at(col+1)[row]++; 		//6
		if(row!=0){
			fgrid.at(col+1)[row-1]++;	//9
		}
		if(row+1!=fgrid[col].size()){
			fgrid.at(col+1)[row+1]++;	//3
		}
	}
}

size_t octocycle(octogrid &fgrid){
	cout << "Octocycle\n";
	int f_return = 0;
	int f_loop = 0;

	//iterate once
	for(int col = 0 ; col < fgrid.size() ; col++){
			for(int row = 0 ; row < fgrid[col].size() ; row++){
				fgrid[col][row]++;
			}
		}

	//explode as many times as we can
	do{
		f_loop = 0;

		for(int col = 0 ; col < fgrid.size() ; col++){
			for(int row = 0 ; row < fgrid[col].size() ; row++){
				if(fgrid[col][row] > 9 && fgrid[col][row] < 200){
					cout << col << " " << " " << row << " " << fgrid[col][row] <<endl;
					octoburst(fgrid, col, row);
					f_loop++;
				}
			}
		}

		f_return += f_loop;
		cout << "f_loop: " << f_loop << " f_return: " << f_return << endl;
	}while(f_loop!=0);

	//reset all exploded (>200) to 0
	for(int col = 0 ; col < fgrid.size() ; col++){
			for(int row = 0 ; row < fgrid[col].size() ; row++){
				if(fgrid[col][row] >= 200){
					fgrid[col][row] = 0;
				}
			}
	}
	//cout << "leaving octocycle\n";

	return f_return;
}

int main(){
	octogrid thegrid;
	fstream input("Day11.txt");
	size_t flashes = 0;

	if(!input.is_open()){
		cout << "Could not open file" << endl;
	}
	else{
		string linebuffer;
		int lcounter = 0;
		while(input >> linebuffer){
			//cout << linebuffer << endl;
			vector<int> b_vect;
			for(int n = 0 ; n < linebuffer.size() ; n++){
				//cout << n;
				string lc = linebuffer.substr(n, 1);
				//cout << lc;
				int li = stoi(lc, nullptr, 10);
				b_vect.push_back(li);
			}
			thegrid.push_back(b_vect);
			//cout << endl;
		}
		show_grid(thegrid);

		//for(int lcy = 0 ; lcy < cycles ; lcy++ ){
		//	int lflash = octocycle(thegrid);
		//	//octocycle(thegrid);
		//	flashes += lflash;
		//	cout << "Day " << lcy << "\nFlashes: " << flashes << endl;
		//}
		int pt2cycles = 1;
		do{
			int lflash = octocycle(thegrid);
			int target = (thegrid.size() * thegrid[0].size());
			cout << "Day " << pt2cycles << "\nFlashes: " << lflash << "Target: " << target << endl;
			if(lflash == target){
				cout << "All flash on day " << pt2cycles << endl;
				break;
			}
			pt2cycles++;
		}while(1);
		//octocycle(thegrid);
		show_grid(thegrid);
	}

	cout << "flashes: " << flashes << endl;
	char c;
	cin >> c;
	return 0;
}