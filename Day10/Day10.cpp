#include <iostream>
#include <fstream>
#include <stack>
#include <list>

using namespace std;

int calc_error(stack<char> &thestack, char fc){
	cout << fc;
	if(thestack.empty()){
		thestack.push(fc);
	}
	else{
		switch (fc){
			case ')':
			if(thestack.top() == '('){
				thestack.pop();
			}
			else{
				return 3;
			}
			break;

			case ']':
			if(thestack.top() == '['){
				thestack.pop();
			}
			else{
				return 57;
			}
			break;

			case '}':
			if(thestack.top() == '{'){
				thestack.pop();
			}
			else{
				return 1197;
			}
			break;

			case '>':
			if(thestack.top() == '<'){
				thestack.pop();
			}
			else{
				return 25137;
			}
			break;
			default:
			thestack.push(fc);
		}
	}
	return 0;
}

size_t calc_auto(stack<char> &mystack){
	cout << "Enterred calc_auto";
	size_t f_auto = 0;
	while(mystack.size()){
		switch (mystack.top()){
			case '(':
				cout << mystack.top();
				f_auto *= 5;
				f_auto += 1;
				mystack.pop();
				break;
				
			case '[':
				cout << mystack.top();
				f_auto *= 5;
				f_auto += 2;
				mystack.pop();
				break;
				
			case '{':
				cout << mystack.top();
				f_auto *= 5;
				f_auto += 3;
				mystack.pop();
				break;
				
			case '<':
				cout << mystack.top();
				f_auto *= 5;
				f_auto += 4;
				mystack.pop();
				break;
		}
	}
	cout << "Line auto: " << f_auto << endl;
	return f_auto;
}

int main(){
	fstream input("Day10.txt");
	
	int err_score = 0;
	list<size_t> auto_score;

	if(!input.is_open()){
		cerr << "Couldn't open/locate file.\n";
	}
	else{
		
		string linebuffer;
		while(input >> linebuffer){
			stack<char> mystack;
			for(int n = 0; n<linebuffer.size() ; n++){
				char c = linebuffer[n];
				//cout << c;
				int charscore = calc_error(mystack, c);
				if(charscore){
					err_score += charscore;
					break;
				}
				if(!mystack.empty()){
					//c = mystack.top();
				}
				if(n+1 == linebuffer.size()){
					cout << "Incomplete line";
					auto_score.push_back(calc_auto(mystack));
				}
				//cout << c;
			}
			cout << endl;
			
		}
	}
	auto_score.sort();
	while(auto_score.size() != 1){
		auto_score.pop_front();
		auto_score.pop_back();
	}
	cout << "Error score: " << err_score << endl;
	cout << "Auto score: " << auto_score.front() << endl;
	char t;
	cin >> t;
	return 0;
}