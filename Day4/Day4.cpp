#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include <fstream>
#include <math.h>

using namespace std;

int winning_boards;

bool checkline(bool line[5]){       //checks a line passed to function, returns true if all are true.
    // cout << "checkline start: ";
    for (int x =0; x < 5; x++){
        // if(line[x]) cout << line[x];
        // else cout << "0 ";
        // cout << line[x] << " ";
        if (line[x]==false) {
            // cout << "false at pos " << x << endl;
            return false;
        }
    }
    cout << endl << "End checkline\n";
    return true;
}

void print_bools(bool line[5]){
    cout << "This line is ";
    for(int x = 0; x < 5; x ++){
        cout << line[x] << " ";    
    }
    cout << endl;
}

class bingoboard {
    private:
    int board[25];
    bool logic[25];
    bool winner;

    public:
    

    bingoboard(){
        cout << "creating a bingoboard" << endl;
        winner = false;
    }

    void set_number(int pos, int num){
        board[pos] = num;
        logic[pos] = false;
        return;
    }

    int get_number(int pos){
        if (pos > 25) pos = pos%25;
        return board[pos];
    }

    int get_score(){
        // cout << "Calling score\n";
        int score = 0;
        for(int x = 0 ; x < 25 ; x++){
            if (logic[x] == false){
                // cout << "Added to score: " << board[x] << endl;
                score += board[x];
            }
        }
        return score;
    }

    void call_number(int num_called){
        // cout << "Calling number " << num_called << endl;
        for(int x = 0;x<25;x++){
            // cout << " at position " << x << " the number is " << board[x] << endl;
            if (num_called==board[x]){
                // cout << "Match for number " << num_called << " at pos " << x << endl;
                logic[x] = true;
            }
        }
        return;
    }

    void show_board(){
        for( int y = 0; y < 25; y++){
            cout << setw(2) << board[y] << " ";
            if((y+1)%5 == 0){ 
            cout << endl;
            }
        }

        cout << endl << "Score is " << get_score() << endl << endl;
    }

    void show_board_logic(){
        for( int y = 0; y < 25; y++){
            cout << setw(2) << logic[y] << " ";
            if((y+1)%5 == 0){ 
            cout << endl;
            }
        }

        cout << endl << "Score is " << get_score() << endl << endl;
    }

    bool is_winner(){
        bool checker[5] = {false, false, false, false, false};                    //line buffer to match grid
        if(winner == true) {
                // cout << "Already won\n";
                return false;                //don't bother if we've already won
            }
        // cout << "Testing for a winner\n";
        
        // cout << "Starting horizontal\n";
        for(int x=0; x < 5; x++){               //check horizontal, X = line#
            // cout << "Loading horizontal: " << x << " ";
            if(winner == true) {
                // cout << "Already won\n";
                return false;                //don't bother if we've already won
            }
            for(int y=0; y<5; y++){     
                checker[y] = logic[(5*x)+y];   //load bufferline
            }
            // cout << "Loaded horizontal: " << x << " ";
            // print_bools(checker);
            if(checkline(checker)){
                winner = true;
                winning_boards += 1;
                cout << "This board has won at horizontal line " << x+1 << " with a score of " << get_score() << endl;
                return true;                      //leave horicheck 
            }
        }

        for(int x=0; x < 5; x++){           //check vertical, X = line#
            if(winner == true) {
                // cout << "Already won\n";
                return false;                //don't bother if we've already won
            }
            for(int y=0; y<5; y++){
                checker[y] = logic[x+(5*y)];   //load bufferline
            }
            // cout << "Loaded vertical: " << x << " ";
            // print_bools(checker);
            if(checkline(checker)){
                winner = true;              //Set win
                winning_boards += 1;
                cout << "This board has won at the vertical line " << x+1 << " witha score of " << get_score() << endl;
                return true;                      //leave vertcheck
            }

        }
        return winner;
    }
};

int main(){
    ifstream myfile("Day4.txt");
    string buffer;
    vector <int> bingocalls;

    bingoboard bingobuffer;
    vector  <bingoboard> bingoboards;

    //Process file

    //Bingo calls
    myfile >> buffer;
    cout << "The first extraction is: " << buffer <<endl;
    size_t pos = 0;
    string delim = ",";
    for(int x = 0; (pos=buffer.find(delim)) != string::npos ; x++)
    {
        bingocalls.push_back(stoi(buffer.substr(0, pos), nullptr, 10));
        // cout << "Added to bingocalls " << bingocalls.at(x) << endl;
        buffer.erase(0, pos + delim.length());
        pos = buffer.find(delim);
    }

    //Bingo boards
    if(!myfile.is_open()){
        cerr << "Error loading file" << endl;
    }
    else{
        for(int x = 0; !myfile.eof() ; x++){
            for (int y = 0; y < 25; y++){
                myfile >> buffer;   
                if( myfile.fail() ) break;
                bingobuffer.set_number(y, stoi(buffer, nullptr, 10));
                // cout << "Curent bingobuffer number " << bingobuffer.get_number(y) << " score is " << bingobuffer.get_score() << endl;
            }
        
        if( myfile.fail() ) break;
      
        bingoboards.push_back(bingobuffer); //add buffered board 2 vector
        }
    }

    //Display boards
    for(int x = 0; x < bingoboards.size(); x++){
  
        bingobuffer = bingoboards.at(x);    //load board buffer from boardlist
        cout << "Board #" << x+1 << endl;
        
        bingobuffer.show_board();
    
    }

    //Call each number
    for( int x = 0; x < bingocalls.size() ; x++){
        bool find_winner = false;
        std::vector<bingoboard>::iterator it;

        // cout << "calling number " << bingocalls.at(x);

        //Edit each board for the call
        for( int y = 0; y < bingoboards.size() ; y++){
            // cout << " on board " << y+1 << endl;
            it = bingoboards.begin() + y;
            bingobuffer = bingoboards.at(y);
            bingobuffer.call_number(bingocalls.at(x));
            bingoboards.erase(it);
            bingoboards.insert(it, bingobuffer);
        }

        //Show Boards after call
        // for( int y = 0; y < bingoboards.size() ; y++){
        //     cout << " on board " << y+1 << endl;
        //     it = bingoboards.begin() + y;
        //     bingobuffer = bingoboards.at(y);
        //     bingobuffer.show_board_logic();
        // }

        //Check if any board has won from the call
        for( int y = 0; y < bingoboards.size() ; y++){
            
            it = bingoboards.begin() + y;
            bingobuffer = bingoboards.at(y);
            if(bingobuffer.is_winner()){
                int winning_number = bingocalls.at(x);
                cout << "We found a winning board: " << y+1 << endl << "The number called was: " << winning_number << endl << "The score of the board is : " << bingobuffer.get_score() <<endl << "For a total of: " << bingobuffer.get_score() * winning_number << endl;   
                cout << "This board won in position: " << winning_boards << endl;
                find_winner = true;
                bingoboards.erase(it);
                bingoboards.insert(it, bingobuffer);
                if (winning_boards== bingoboards.size()){
                    cout << "It was the last board to win\n";
                }
                // break;
            }
        }
        // if (find_winner) break;
        
        
    }

    // //Display boards
    // for(int x = 0; x < bingoboards.size(); x++){
  
    //     bingobuffer = bingoboards.at(x);    //load board buffer from boardlist
    //     cout << "Board #" << x+1 << endl;
        
    //     bingobuffer.show_board();
    
    // }

    //end of program pause for records
    char c;
    cin >> c;
    return 0;
}