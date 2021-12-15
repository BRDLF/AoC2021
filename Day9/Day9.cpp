#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <list>

using namespace std;



int get_basin(int x, int y, vector<vector <int>> outer)
{
	set<pair<int, int>> basin;
	basin.insert(make_pair(x, y));
	
	//for(set<pair<int,int>>::iterator it = basin.begin(); it!=basin.end() ; it--)
	set<pair<int,int>>::iterator it = basin.begin();
	do
	{
		pair<int, int> tp = *it;
		int tx = tp.first;
		int ty = tp.second;
		//cout << "\ntx: " << tx << " ty: " << ty << endl;
		//Comp
		if(tx!=0 && outer.at(ty).at(tx-1) != 9){
			if(basin.emplace(make_pair(tx-1, ty)).second){
				//cout << "Left: It seems that " << outer.at(ty).at(tx-1) << " is 1 greater than " << outer.at(ty).at(tx) << endl << "Basin: " << basin.size() <<endl;;
				it = basin.begin();
				continue;
			}
			
		}
		if(tx+1!=outer.at(ty).size() && outer.at(ty).at(tx+1) != 9 ){
			if(basin.emplace(make_pair(tx+1, ty)).second){
				//cout << "Right: It seems that " << outer.at(ty).at(tx+1) << " is 1 greater than " << outer.at(ty).at(tx) << endl << "Basin: " << basin.size() <<endl;;
				it = basin.begin();
				continue;
			}
		}
		if(ty!=0 && outer.at(ty-1).at(tx) != 9){
			if(basin.emplace(make_pair(tx, ty-1)).second){
				//cout << "Up: It seems that " << outer.at(ty-1).at(tx) << " is 1 greater than " << outer.at(ty).at(tx) << endl << "Basin: " << basin.size() <<endl;;
				it = basin.begin();
				continue;
			}
		}
		if(ty+1!=outer.size() && outer.at(ty+1).at(tx) != 9){
			if(basin.emplace(make_pair(tx, ty+1)).second){
				//cout << "Down: It seems that " << outer.at(ty+1).at(tx) << " is 1 greater than " << outer.at(ty).at(tx) << endl << "Basin: " << basin.size() <<endl;;
				it = basin.begin();
				continue;
			}
		}
		it++;
	}
	while(it != basin.end());
	cout << " Size: " << basin.size() <<endl;
	return basin.size();
}

bool is_lowest(int x, int y, vector<vector <int>> outer, vector<int> inner)
{
	if((x==0 || inner.at(x-1) > inner.at(x)) 
	&& (x+1==inner.size() || inner.at(x+1) > inner.at(x))
	&& (y==0 || outer.at(y-1).at(x) > inner.at(x))
	&& (y+1==outer.size() || outer.at(y+1).at(x) > inner.at(x))
	)
	{
		cout << "Basin root: " << x << " " << y;
		return 1;
	}
	
	return 0;
}

void showVector(vector<int> &inputvector)
{
	for(int x=0 ; x < inputvector.size() ; x++){
		cout << inputvector.at(x);
	}
	cout << endl;
	return;
}

int main()
{
	list<int> l_basins;
	fstream myfile("Day9.txt");
	string linebuffer;
	vector<vector<int>> lava_grid;
	int risk = 0;
	int ptwo = 1;

	if(!myfile.is_open())
	{
		cerr << "Could not find/open file";
	}
	else
	{
		while(myfile >> linebuffer)
		{
			vector<int> temp_vect;
			//showVector(temp_vect);
			for(int x = 0 ; x < linebuffer.size() ; x++)
			{
				int to_add = stoi(linebuffer.substr(x, 1), nullptr, 10);
				temp_vect.push_back(to_add);
				
			}
			showVector(temp_vect);
			lava_grid.push_back(temp_vect);
		}

		for( int y = 0 ; y < lava_grid.size() ; y++ )
		{
			vector<int> temp_vect = lava_grid.at(y);
			for( int x = 0 ; x < temp_vect.size() ; x++ )
			{
				//cout << "Testing y: " << y << " and x " << x << " "<< lava_grid.at(y).at(x) << " ";
				if(is_lowest(x, y, lava_grid, temp_vect))
				{
					risk += (1 + lava_grid.at(y).at(x));
					l_basins.push_back(get_basin(x, y, lava_grid));
				} 
			}
		}

		for (list<int>::iterator it = l_basins.begin() ; it != l_basins.end() ; it++)
		{
			cout << *it << " ";
		}
		l_basins.sort(std::greater<int>());
		cout << endl;
		for (list<int>::iterator it = l_basins.begin() ; it != l_basins.end() ; it++)
		{
			cout << *it << " ";
		}
		cout << endl;
		l_basins.resize(3);
		cout << endl;
		for (list<int>::iterator it = l_basins.begin() ; it != l_basins.end() ; it++)
		{
			cout << *it << " ";
			ptwo *= *it;
			cout << ptwo << " ";
		}
		
		cout << endl;
	}

cout << "Risk is " << risk << endl;
char c;
cin >> c;
return 0;

}