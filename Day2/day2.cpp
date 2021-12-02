#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
ifstream myfile("day2.txt");
string buffer;
string direction;
int distance;
int aim;
int total_distance = 0;
int total_depth = 0;
int answer;

if(!myfile.is_open()){
    cerr << "Error opening file\n";
}
else{
    while(myfile >> direction){
        myfile >> distance;
        cout << "direction " << direction <<"\n";
        cout << "distance " << distance << "\n";
        if(direction == "forward") {
            total_distance += distance;
            total_depth += aim * distance;
        }
        else if(direction == "up"){
            aim -= distance;
        }
        else if(direction == "down"){
            aim += distance;
        }
    }

}
answer = total_distance * total_depth;
cout << "Total Forward: " << total_distance << "\n";
cout << "Total Depth: " << total_depth << "\n";
cout << "Answer: " << answer << "\n";
char c;
cin >> c;
return 0;
}