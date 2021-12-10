#include <iostream>
 #include <fstream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

int main(){

	int occurrences = 0;
	string linebuffer;
	long total = 0;

	fstream input("Day8.txt");

	if(!input.is_open()){
		cerr << "Could not open file\n";
	}
	else{
		while(input.ignore( 256, '|' ) ) {
			getline( input, linebuffer, '\n');
			cout << linebuffer << endl;
			istringstream iss(linebuffer);
				int digit = 0;

				while(iss >> linebuffer){
					int num =0;

					switch(linebuffer.size( ) ){

						case 2:
						num = 1;
						occurrences++;
						break;
						
						case 3:
						num = 7;
						occurrences++;
						break;

						case 4:
						num = 4;
						occurrences++;
						break;
						
						case 5:
                  if( linebuffer.find( 'b') == string::npos) num = 2;
                  else if( linebuffer.find( 'e') == string::npos) num = 3;
                  else if( linebuffer.find( 'a') == string::npos) num = 5; 
                  break;

               	case 6:
               	cout << linebuffer << endl;
                  if( linebuffer.find( 'a') == string::npos) {
                  	num = 6;
                  }else
                  if( linebuffer.find( 'g') == string::npos) {
                  	num = 9;
                  }else
                  if( linebuffer.find( 'f') == string::npos){
                     num = 0;
                  }
                  break;

                  case 7:
                  num = 8;
               	occurrences++;
                  break;
               }
                // cout << linebuffer << " is " << linebuffer.size() << " characters long." << endl;
                // if( linebuffer.size() == 2 || linebuffer.size() == 3 || linebuffer.size() == 4 || linebuffer.size() == 7){
                //     occurrences++;
                // }
                cout << "num: " << num << " digit: " << digit << endl;
                total += num * pow( 10, ( 3-digit));


                digit++;
            }
            



        }
        cout << "# of occurrences: " << occurrences << endl;
        cout << "# of total: " << total << endl;
    }

    char c;
    cin >> c;
    return 0;


}