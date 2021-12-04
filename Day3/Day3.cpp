#include <iostream>
#include <iomanip>
#include <list>
#include <fstream>
#include <math.h>

using namespace std;

void filternum(list<string> &source, int address, char filter){
    if(source.size() == 0){
        cout << "Empty source, leaving\n";
        return;
    }
    else if(source.size() == 1){
        cout << "We have a match!\n"; 
        return;
    }
    string buffer;
    // cout << "In filternum\n";
    for(list<string>::iterator funit=source.begin(); funit!=source.end(); funit){
        buffer = *funit;
        if(buffer.at(address) == filter){
            funit = source.erase(funit);
            // cout << "I erased " << buffer << " in position " << address << " because of the filter: " << filter << endl;
        } 
        else funit++;
    }
    for(list<string>::iterator funit=source.begin(); funit!=source.end(); funit++){
        buffer = *funit;
        // cout << buffer << " remains in the list\n";
         } 
    // cout << "Leaving filternum\n";
    return;
}

main(){
    ifstream myfile("Day3.txt");
    int loopcnt =0;
    string buffer;
    int bitcount[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    int gamma =0;
    int epsilon = 0;
    long poweruse =0;
    list <string> bufferlist;
    list <string> oxygenlist;
    string oxygen;
    list <string> scrubberlist;
    string scrubber;
    list<string>::iterator it;

if(!myfile.is_open()){
    cerr << "Error opening file\n";
}
else{
    
    while(myfile >> buffer){
        bufferlist.push_back(buffer);
        oxygenlist.push_back(buffer);
        scrubberlist.push_back(buffer);
        it = bufferlist.begin();
        advance(it, loopcnt);
        // cout << setw(3) << loopcnt << " " << setw(12) << *it << "\n";
        for(int x = 0; x < 12 ; x++){
            if(buffer.at(x) == '1'){
                bitcount[x] ++;
            }
        }
        it++;
        loopcnt++;
    }
}
cout << "Part 1 results\n";
for(int x = 0; x < 12 ; x++){
    // cout << "Bit at " << x << "is " << bitcount[x] << "\n";
    if(bitcount[x]*2 > loopcnt){
        // cout << "Adding bit " << x << " to gamma: " << gamma << " ";
        gamma += pow(2, (11-x));
    }
    else{
        // cout << "Adding bit " << x << " to epsilon: " << epsilon << " ";
        epsilon += pow(2, (11-x));
    }
}
cout << "Total loops: " << loopcnt << "\nGamma: " << gamma << "\nEpsilon: " << epsilon << endl;
poweruse = gamma*epsilon;
cout << "Power use: " << poweruse <<  "\nEnd Part 1 results\n\n";

cout << "Start part 2\n";
for(int x = 0; x < 12 ; x++){ //oxygenlist block
    if(oxygenlist.size() == 1) break;
    int commoncount = 0;
    for(list<string>::iterator funit=oxygenlist.begin(); funit!=oxygenlist.end(); funit++){
        buffer = *funit;     
        if(buffer.at(x) == '1') commoncount++; //count common
    }
    cout << "In the Oxygen loop at index " << x << " there are " << commoncount << " instances of 1 out of " << oxygenlist.size() << " cases\n";
    if (commoncount*2 >= oxygenlist.size()) {
        cout << commoncount*2 << " is greater than or equal to " << oxygenlist.size() << endl;
        cout << "1 is most common or equal, removing 0\n";
        filternum(oxygenlist, x, '0'); //remove all with 0
    }
    else{
        cout << commoncount*2 << " is less than " << oxygenlist.size() << endl;
        cout << "0 is most common or equal, removing 1\n";
        filternum(oxygenlist, x, '1'); //remove all with 1
    }
}
for(int x = 0; x < 12 ; x++){ //scrubber block
    if(scrubberlist.size() == 1) break;
    int commoncount = 0;
    for(list<string>::iterator funit=scrubberlist.begin(); funit!=scrubberlist.end(); funit++){
        buffer = *funit;     
        if(buffer.at(x) == '1') commoncount++; //count common
    }
    cout << "In the Scrubber loop at index " << x << " there are " << commoncount << " instances of 1 out of " << scrubberlist.size() << " cases\n";
    if (commoncount*2 >= scrubberlist.size()) {
        cout << commoncount*2 << " is greater than or equal to " << scrubberlist.size() << endl;
        cout << "1 is most common or equal, removing 1\n";
        filternum(scrubberlist, x, '1'); //remove all with 1
    }
    else{
        cout << commoncount*2 << " is less than " << scrubberlist.size() << endl;
        cout << "0 is most common, removing 0\n";
        filternum(scrubberlist, x, '0'); //remove all with 0
    }
}
cout << "End part 2\n\nStart part 2 results\n";

it = oxygenlist.begin();
oxygen = *it;
cout << "Oxygen is " << oxygen << " or " << stoi(oxygen, 0, 2) << endl;
it = scrubberlist.begin();
scrubber = *it;
cout << "Scrubber is " << scrubber << " or " << stoi(scrubber, 0, 2) << endl;
int life = stoi(oxygen, 0, 2)*stoi(scrubber, 0, 2);
cout<< "Life is " << life << "\nEnd Part 2 Results\n\n";
char c;
cin >> c;
return 0;
}