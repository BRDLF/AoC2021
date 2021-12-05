#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include <fstream>
#include <math.h>

using namespace std;

const int map_x = 1000;
const int map_y = 1000;

uint8_t map[map_x][map_y];

int active_vents(){
    int vents_active = 0;
    for( int x = 0 ; x < map_x ; x++){
        for( int y = 0; y < map_y ; y++){
            if( map[x][y] > 1){
                vents_active++;
            }
        }
    }
    return vents_active;
}

void draw_line(int r1, int s1, int r2, int s2){
    int greater_r;
    int lesser_r; 
    int node_s;
    bool direction = false;
    if( r1 > r2 ){
        greater_r = r1;
        lesser_r = r2;
        node_s = s2;
        if (s1 > s2){
            direction = true;
        }
    }
    else{
        greater_r = r2;
        lesser_r = r1;
        node_s = s1;
        if (s2 > s1){
            direction = true;
        }
    }
    for( lesser_r ; lesser_r < greater_r+1 ; lesser_r++){
        map[lesser_r][node_s]++;
        if(direction){
            node_s++;
        }
        else{
            node_s--;
        }
    }
}

void draw_line_x(int x, int r1, int r2){

    int greater = r1 >= r2 ? r1 : r2;
    int lesser = r1 < r2 ? r1 : r2;
    for( lesser; lesser < greater+1 ; lesser++){
        // cout << lesser << " ";
        map[x][lesser]++;
    }
    // cout << endl;
}

void draw_line_y(int y, int r1, int r2){

    int greater = r1 >= r2 ? r1 : r2;
    int lesser = r1 < r2 ? r1 : r2;
    for( lesser; lesser < greater+1 ; lesser++){
        // cout << lesser << " ";
        map[lesser][y]++;
    }
    // cout << endl;
}

void map_vent(int x1, int y1, int x2, int y2){

    if(x1 == x2){
        draw_line_x(x1, y1, y2);
    }

    else if (y1 == y2){
        draw_line_y(y1, x1, x2);
    }
    else{
        cout << "No linearity\n";
        draw_line(x1, y1, x2, y2);
    }
    return;
}

class vent {

    private:
    int x1;
    int y1;
    int x2;
    int y2;

    public:
    vent(){
        // cout << "Making empty vent\n";
        return;
    }
    void setVent(pair<int, int> head, pair<int, int> tail){
        // cout << "Making and initializing a vent\n";
        x1 = head.first;
        y1 = head.second;
        x2 = tail.first;
        y2 = tail.second;
        // cout << "x1: " << x1 << " y1: " << y1 << "\nx2: " << x2 << " y2 " << y2 << endl;
        return;
    }
    int get_x1() {
        return x1;
    }
    int get_y1() {
        return y1;
    }
    int get_x2(){
        return x2;
    }
    int get_y2() {
        return y2;
    } 
    

};



int main(){
    ifstream myfile("Day5.txt");
    string buffer;
    pair <int, int> ventA;
    pair <int, int> ventB;

    vent buffer_vent;
    vector <vent> vent_catalogue;

    //Process input
    size_t posA =0;
    size_t posB =0;
    string delim = " -> ";
    if(!myfile.is_open()){
        cerr << "Error loading file" << endl;
    }
    else{
        
        //load vents
        while(getline(myfile, buffer)){
            size_t posA =0;
            size_t posB =0;
            string delim = " -> ";

            cout << buffer << endl;
            posA = buffer.find(",");
            posB = buffer.find(delim);

            ventA.first = stoi(buffer.substr(0, posA), nullptr, 10);
            ventA.second = stoi(buffer.substr(posA +1, posB), nullptr, 10);
            buffer.erase(0, posB + delim.length());

            cout << buffer << endl;
            posA = buffer.find(",");
            ventB.first = stoi(buffer.substr(0, posA), nullptr, 10);
            ventB.second = stoi(buffer.substr(posA+1, buffer.length()), nullptr, 10);
            buffer_vent.setVent(ventA, ventB);
            vent_catalogue.push_back(buffer_vent);
        }

        // for(vector<vent>::iterator it= vent_catalogue.begin(); it < vent_catalogue.size(); it++){
        for(int it = 0 ; it < vent_catalogue.size() ; it++){
            buffer_vent = vent_catalogue.at(it);        //loads buffer

            map_vent(buffer_vent.get_x1(), buffer_vent.get_y1(), buffer_vent.get_x2(), buffer_vent.get_y2());
        }

        cout << "Number of active vents: " << active_vents() << endl;

    }

    char c;
    cin >> c;
    return 0;
}