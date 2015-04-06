#include <string>
#include <vector>
//#include <array>
#include <iostream>
#include <fstream>

using namespace std;

vector<string> error; 
vector<string> constants;
vector<string> identifiers;
string errorString = "";
int errorCount = 0;
//string identifiers = "";
//string constants = "Constants: ";
bool keyIsUsed[7] = {false};

bool operatorsUsed[13];
bool delimetersUsed[4];
int leftParenCount = 0;
int rightParenCount = 0;

//++++++++++++++++++++++++++++++ DICTIONARIES ++++++++++++++++++++++++++++++++++++++++++//

const string operatorList[] = {"+", "-", "*", "/", "++", "--", "=", "==", "<", ">", "&&", "||", "!"};
const string delimiterList[] = {"(", ")", ";", ","};
const string keywords[] = {"BEGIN", "END", "FOR", "WHILE", "IF", "ELSE", "ELSEIF"};

//++++++++++++++++++++++++++++++ ERROR CHECKING +++++++++++++++++++++++++++++++++++++++++++//

bool forUsed = false;
bool keywordFirst = false;


int parseDigits(string line, int index){
	
	string num = "";
	num += line.at(index);
	
	int size = static_cast<int>(line.size());
	if(index != size){ //make sure its not last
		index++;
		while(line.at(index) >= 48 && line.at(index) <= 57){
			num += line.at(index);
			index++;
		}
	}

	bool isUsed = false;
	for(unsigned i = 0; i < constants.size(); i++){
		if(num.compare(constants[i]) == 0) isUsed = true;
	}
	if(!isUsed){
		constants.push_back(num); }
	
	return index--;
}

int parseSymbol(string line, int index){
	
	string curr = ""; 
	curr += line.at(index);

	if(line.at(index) == '+' || line.at(index) == '-' || line.at(index) == '=' || line.at(index) == '&' || line.at(index) == '|'){
		string nextLet = "";
		if(index <= static_cast<int>(line.size())){
			nextLet += line.at(index + 1); 
			if(curr.compare(nextLet) == 0){
				curr = curr + curr;
				index++;
			}
		}
	}

	for(int i = 0; i < 4; i++){
		//delimetersUsed[i] = false;
		if(delimiterList[i] == curr){
			//parseDelimiter(curr);
			delimetersUsed[i] = true;
			return index;
		}
	}

	for(int i = 0; i < 13; i++){
		if(operatorList[i] == curr){
			//operatorsUsed[i] = false;
			//parseOperator(curr);
			operatorsUsed[i] = true;
			return index;
		}
	}
	return index;
}


int parseLower(string line, int index){
	
	string tempKey = "";
	tempKey += line.at(index);
	if( index < static_cast<int>(line.size()) - 1)
		index++;

	while(line.at(index) >= 97 && line.at(index) <= 122){
		tempKey += line.at(index);
		cout<<index;
		if(index <= static_cast<int>(line.size())){
			index++;

			break;  }
	}
	
	bool isUsed = false;
	for(unsigned i = 0; i < identifiers.size(); i++){
		if(tempKey.compare(identifiers[i]) == 0) isUsed = true;
	}
	if(!isUsed){
		identifiers.push_back(tempKey); }
	index--;
	cout<<tempKey;
	cout<<index;
	//cout <<index;
	return index--;
}


void errorParser(string word, string messError){

	if(messError.compare("noKeyword") == 0){ //if the error is from isKeyword
		error.push_back(word + " is not a keyword.");
		errorCount++;
	}

	else if(messError.compare("noSemicolon") == 0){

		error.push_back("Missing semicolon");
		errorCount++;
	}
		
}


void isKeyword(string word){
	
	int keyIndex = -1;

	for(int i = 0; i <7; i++){
		if(word.compare(keywords[i]) == 0){
			keyIndex = i;
		}
	}

	if(keyIndex == -1){
		errorParser(word, "noKeyword");
	}
	else{
		keyIsUsed[keyIndex] = true;
	}
/*
	switch(keyIndex){
		case 0: //DO THIS PART
	}
*/
}


int parseUpper(string line, int index){


	string tempKey = "";
	tempKey += line.at(index);
	if(index < static_cast<int>(line.size()))
		index++;
	while(line.at(index) >= 65 && line.at(index) <= 90){
		tempKey += line.at(index);
		//cout<< "parseUpper";
		if(index == static_cast<int>(line.size()) - 1) break;
		else index++;
	}
	
	isKeyword(tempKey);
	return index--;

}

void parseLine(string line){

	for(int i = 0; i < static_cast<int>(line.size()); i++){
		char curr = line.at(i);
		cout<<curr;
		if(curr >= 65 && curr <= 90){  //check for capital letters
			if(i == 0) keywordFirst = true;
			i = parseUpper(line, i);
		}
		else if(curr >= 97 && curr <= 122){  //check for lowercase letters
			i = parseLower(line, i);

		}
		else if(curr == '+' || curr == '-' || curr == '*' || curr == '/' || curr == '=' || 
			     curr == '<' || curr == '>' || curr == '&' || curr == '|' || curr == '!' ||
			      curr == '(' || curr == ')' || curr == ';' || curr == ','){
			
			i = parseSymbol(line, i);
		}
		else if(curr >= 48 && curr <= 57){ //check for digits
			i = parseDigits(line, i);
		}

	}

	if(!keywordFirst){

		if(line.at(static_cast<int>(line.size()) - 1) != ';'){

			errorParser("", "noSemicolon");
			
		}
	}
	
}

void print(){

	//printing keywords
	cout << "Keywords: ";
	for(int i = 0; i < 7; i++){
		if(keyIsUsed[i]){
			cout << keywords[i] << " ";
		}
	} cout << endl;

	//printing identifiers
	cout<< "Identifiers: ";
	for(unsigned i = 0; i < identifiers.size(); i++){
		cout << identifiers[i] << " ";
	}
	cout<<endl;

	//printing constants
	cout<< "Constants: ";
	for(unsigned i = 0; i < constants.size(); i++){
		cout << constants[i] << " ";
	}
	cout<<endl;

	//printing operators
	cout << "Operatros: ";
	for(int i = 0; i < 13; i++){
		if(operatorsUsed[i]){
			cout << operatorList[i] << " ";
		}
	} cout << endl;

	//printing delimiters
	cout << "Delimiters: ";
	for(int i = 0; i < 4; i++){
		//cout << "Del";
		if(delimetersUsed[i]){
			cout << delimiterList[i] << " ";
		}
	} cout << endl << endl;

	//printing all errors
	for(int i = 0; i < errorCount; i++){
		cout << "Error(" << i+1 << "): " << error[i] << endl;
	}
}

int main(){
	try{
	cout << "Please enter the file path:" << endl;
	string fileName;
	//cin >> fileName;

	ifstream input ("program.txt");
	string line;

	if(input.is_open()){
		while (getline(input, line)){
			cout << line << endl;
			parseLine(line);
			
			//reseting some errors
			keywordFirst = false;
		}
		input.close();
	}

	else cout << "Unable to open file";

	print();
	}
	catch (exception const &exc)
    {
        cerr << "Exception caught " << exc.what() << "\n";
    }
    catch (...)
    {
        cerr << "Unknown exception caught\n";
    }
}

//static_cast<int>(variable) used to convert from size_type to int value so that code compiles in g++
