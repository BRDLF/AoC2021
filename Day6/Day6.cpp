#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int days = 256;


int main(){
    ifstream input("Day6.txt");
    std::string buffer;

    vector<long long> v_lantern;
    long long a_lantern[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    if(!input.is_open()){
        cout << "Unable to open file.\n";
    }
    else{
        input >> buffer;                //True Input
        // buffer = "3,4,3,1,2";        //Test Input
        cout << buffer << endl;
        size_t pos;
        // for(size_t pos = buffer.find(',');pos != string::npos; pos = buffer.find(',')){
        do{
            pos = buffer.find(',');
            int blantern = stoi(buffer.substr(0,pos), nullptr, 10);
            cout << blantern << " ";
            buffer.erase(0, pos+1);

            a_lantern[blantern]++;
        }
        while(pos != string::npos);
        cout << endl;

        for(int x = 0 ; x < 9 ; x++){
            cout << a_lantern[x] << " ";
        }

        for(size_t d = 0; d < days ; d++){
            cout << "Day " << d+1 << endl;
            long long breeding = 0;
            for (size_t x = 0 ; x < 9 ; ++x){
                if(x == 0){
                    breeding = a_lantern[x];
                    a_lantern[x] = 0; 
                }
                else{
                    a_lantern[x-1] = a_lantern[x];
                    a_lantern[x] = 0;
                }
            }
            a_lantern[6] += breeding;
            a_lantern[8] += breeding;
        }
        long long total = 0;
        for (size_t x = 0 ; x < 9 ; ++x){
            total += a_lantern[x];
        }
        cout << "The total lanternfish is: " << total;
        // for(size_t d = 0 ; d < days ; d++){
        //     cout << "Day " << d+1 << endl;

        //     for(size_t x = 0 ; x < v_lantern.size() ; x++){
            
        //         v_lantern.at(x)--;
        //     }
        //     for(size_t x = 0 ; x < v_lantern.size() ; x++){
            
        //         //if lantern = -1
        //         if(v_lantern.at(x) == -1){
        //             v_lantern.at(x) = 6;
        //             v_lantern.push_back(8);

        //         }
        //     }
        //     // cout << "Fish: " << v_lantern.size() << endl << endl;
            
        // }
        // cout << endl << count_fish(v_lantern) << endl;

    } 

    char c;
    std::cin >> c;
    return 0;
}