#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;
struct Node{
	char data;
	Node *next;
};
class Stack{
	public:
		Stack();
		~Stack();
		void push(char a); //pushes a node onto top of stack
		char pop();	//pop top node off of the stack
		string toString();
		bool isEmpty();
		char getTop();
	private:
		Node *top;
};
Stack::Stack(){
	top = NULL;
}
Stack::~Stack(){
	while(!isEmpty())
		pop();
}
void Stack::push(char d){ //Add a character at the top of the stack
	Node *temp = new Node;
	temp->data = d;
	temp->next = top;
	top = temp;
}
char Stack::pop(){//Delete the element at the top of the stack if stuck is not empty
	if(!isEmpty()){
		char value = top->data;
		Node *oldtop = top;
		top = oldtop -> next;
		delete oldtop;
		return value;
	}else{
		return 'n';
	}
}
string Stack::toString(){//Print stack elements
	string result = "";
	if(isEmpty()){
		result = result + "$";
	}else{
		Node *current = top;
		while(current !=NULL){
			result = result + current->data;
			current = current ->next;
		}
		result = result +"$";
		reverse(result.begin(), result.end()); 
		return result;
	}
}
bool Stack::isEmpty(){//Check if stack is empty
	return(top==NULL);
}
char Stack::getTop(){//Return the element that is at the top of the stack
	char val;
	Node *current = top;
	if(isEmpty()){
		return '$';
	}
	val = current->data;
	return val;
	
}
using namespace std;
std::vector<std::string> split_ws( std::string str )//Split string based on spaces
{
    std::vector<std::string> result ;

    std::istringstream stm(str) ;
    std::string token ;
    while( stm >> token ) result.push_back(token);

    return result ;
}
int main(){
	cout<<"For Grammar G"<<endl;
	cout<<"***************"<<endl;
	cout<<"S->[A]"<<endl;
	cout<<"A->BE"<<endl;
	cout<<"B->x|y|S"<<endl;
	cout<<"E->:A|+A|empty"<<endl;
	cout<<"***************"<<endl;
	Stack *s = new Stack();
	string Array1[4][7] = {{"] A ["," "," "," "," "," "," "},{"E B"," "," "," ","E B","E B"," "},{"S"," "," "," ","x","y"," "},{" "," ","A :","A +"," "," "," "}};
	cout<<"Give a string with spaces (etc [ x : y ])"<<endl;
	string input;
	getline(cin, input);
	int size=0;
	for( std::string s : split_ws(input) ){
		size++;
		if(s !="[" && s!="]" && s!=":" && s!="+" && s!="x" && s!="y"){ //If not only final symbols contained in the given string then its not recognized
			cout<<"Urecognized character: "<<s<<endl;
			exit(1);
		}
	}
	size++;
	string SymbolsGiven[size]; //matrix that contains the given string + a dollar and all final symbols given
	int index=0;
	for( std::string s : split_ws(input) ){
		SymbolsGiven[index]=s;
		index++;
	}
	SymbolsGiven[index]='$';
	s->push('S');
	int currentinput = 0;
	for(;;){
		int i,j;
		char curr = SymbolsGiven[currentinput][0];
		cout<<"Stack:"<<s->toString()<<"   ";
		cout<<"Input: ";
		for(int z=currentinput;z<size;z++){
			cout<<SymbolsGiven[z];
		}
		cout<<"   ";
		if((s->getTop() =='['&& curr=='[')||(s->getTop()==']'&& curr==']')||(s->getTop()==':'&& curr==':')||(s->getTop()=='+'&& curr=='+')||(s->getTop()=='x'&& curr=='x')||(s->getTop()=='y'&& curr=='y')){//Αν το σύμβολο εισόδου βρίσκεται και στην κορυφή της στοίβας τότε αφαιρείτα
			cout<<endl;																																														
			s->pop();
			currentinput++; //go to the next input symbol
			if(SymbolsGiven[currentinput][0]=='$' && s->getTop()=='$'){//If the input symbol is dollar and stack is empty then the string is recognized
				cout<<"Stack:"<<s->toString()<<"   ";
				cout<<"Input: ";
				for(int z=currentinput;z<size;z++){
					cout<<SymbolsGiven[z];
				}
				cout<<"   ";
				char curr = SymbolsGiven[currentinput][0];
				cout<<"\n"<<"The string "<<input<<"is recognized by the Top Down parser"<<endl;
				break;
			}
			continue;
		}else{
			cout<<"Array Element:"<<"M"<<"("<<s->getTop()<<","<<curr<<")"<<"   "; //Else based on the input symbol and what is the element at the top of the stack search the matrix for the rule that will be used.
			if(s->getTop()=='S' && curr=='['){
				i=0;
				j=0;
				cout<<"Production:S->[A]"<<endl;
			}else if(s->getTop() =='A' && curr=='['){
				i=1;
				j=0;
				cout<<"Production:S->BE"<<endl;
			}else if(s->getTop() =='A' && curr=='x'){
				i=1;
				j=4;
				cout<<"Production:S->BE"<<endl;
			}else if(s->getTop() =='A' && curr=='y'){
				i=1;
				j=5;
				cout<<"Production:S->BE"<<endl;
			}else if(s->getTop() =='B' && curr=='['){
				i=2;
				j=0;
				cout<<"Production:B->S"<<endl;
			}else if(s->getTop() =='B' && curr=='x'){
				i=2;
				j=4;
				cout<<"Production:B->x"<<endl;
			}else if(s->getTop() =='B' && curr=='y'){
				i=2;
				j=5;
				cout<<"Production:B->y"<<endl;
			}else if(s->getTop() =='E' && curr==']'){
				i=3;
				j=1;
				cout<<"Production:E->empty"<<endl;
			}else if(s->getTop() =='E' && curr==':'){
				i=3;
				j=2;
				cout<<"Production:B->:A"<<endl;
			}else if(s->getTop() =='E' && curr=='+'){
				i=3;
				j=3;
				cout<<"Production:B->+A"<<endl;
			}else{ //No rule found
				i=10;
				j=10;
				cout<<"Not such a rule found"<<endl;
			}
		}
		if(i==3 && j==1){ //If the rule is Ε->ε then just remove the element at the top of the stack.
			s->pop();
		}else if(i==10 && j==10){ //If no rule found to continue then its obvious that the string is not recognized
			cout<<"Unrecognized"<<endl;
			break;
		}else{ 
			s->pop();
			for( std::string k : split_ws(Array1[i][j])){
				char instack = k[0];
				s->push(instack);
			}
		}
	}
	return 0;
}