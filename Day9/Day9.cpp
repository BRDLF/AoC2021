#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void showVector(vector<int> &inputvector){
	for(int x=0 ; x < inputvector.size() ; x++){
		cout << inputvector.at(x);
	}
	cout << endl;
	return;
}

int main(){
	fstream myfile("Day9.txt");
	string linebuffer;
	vector<vector<int>> lava_grid;

	if(!myfile.is_open())
	{
		cerr << "Could not find/open file";
	}
	else
	{
		while(myfile >> linebuffer)
		{
			vector<int> temp_vect;
			showVector(temp_vect);
			for(int x = 0 ; x < linebuffer.size() ; x++)
			{
				int to_add = stoi(linebuffer.substr(x, 1), nullptr, 10);
				temp_vect.push_back(to_add);
				
			}
			showVector(temp_vect);
			lava_grid.push_back(temp_vect);
		}
	}

char c;
cin >> c;
return 0;

}