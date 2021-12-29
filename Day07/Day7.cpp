#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

int main(){
    ifstream input("Day7.txt");

    if(!input.is_open()){
        cout << "Unable to open file.\n";
    }
    else{
        std::string buffer;
        vector<int> vect_crabs;
        int last_crab = 0;
        int first_crab = INT32_MAX;
        int buffer_crab = 0;
        int fuel_use = INT32_MAX;

        input >> buffer;
        // buffer = "16,1,2,0,4,2,7,1,2,14";
        // cout << buffer << "\n\n\n";
        size_t pos;
        // for(size_t pos = buffer.find(',');pos != string::npos; pos = buffer.find(',')){
        do{
            pos = buffer.find(',');
            buffer_crab = stoi(buffer.substr(0,pos), nullptr, 10);
            // cout << buffer_crab << " ";
            if(buffer_crab < first_crab){
                first_crab = buffer_crab;
            }
            if(buffer_crab > last_crab){
                last_crab = buffer_crab;
            }
            buffer.erase(0, pos+1);
            vect_crabs.push_back(buffer_crab);
        }
        while(pos != string::npos);

        for(first_crab; first_crab <= last_crab ;  first_crab++ ){
            int fuel_buffer = 0;
            for(int x = 0 ; x < vect_crabs.size() ; x++ ){
                int abs_buffer = abs((vect_crabs.at(x) - first_crab));
                // cout << abs_buffer << " is the difference from  " << vect_crabs.at(x) << " to " << first_crab << endl << "Adding: ";
                for (int r = 1; r < abs_buffer+1 ; r++){
                    // cout << r << " ";
                    fuel_buffer += (r);
                }
                // cout << endl << abs_buffer << " ";
                
            }
            // cout << fuel_use << " " << fuel_buffer << "\n\n";
            fuel_use = fuel_use < fuel_buffer ? fuel_use : fuel_buffer;
        }
        cout << "The lowest fuel use is: " << fuel_use << endl;
    }

    char c;
    cin >> c;
    return 0;
}