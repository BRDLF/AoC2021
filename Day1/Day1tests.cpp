#include <iostream>
#include <fstream>

int main() {
std::ifstream myfile("input.txt");
int lnum=0, pnum =0, icounter =0, cnum =0, oldest=0, older=0, wicounter=0;

if ( myfile.is_open()) {
    while (myfile >>pnum) {
    std::cout << oldest << " " << older << " " << lnum << " " << pnum << "\n"; 
    myfile >> lnum;
    std::cout << oldest << " " << older << " " << lnum << " " << pnum << "\n"; 
    myfile >> older;
    std::cout << oldest << " " << older << " " << lnum << " " << pnum << "\n"; 
    myfile >> oldest;
    std::cout << oldest << " " << older << " " << lnum << " " << pnum << "loop end\n"; 
    // if(cnum !=0 & pnum > lnum) {icounter++;}
    // if(cnum > 2 & pnum > oldest) {wicounter++;}
    // std::cout << oldest << " " << older << " " << lnum << " " << pnum << " " << icounter << " " << wicounter<< "\n"; 
    // oldest = older;
    // older = lnum;
    // lnum = pnum;
    cnum++;
}
}
else {
    std::cerr << "Can't open file\n";
}
std::cout << "icounter " << icounter << "\nwicounter" << wicounter;
char c;
std::cin >> c;
return 0;
}