#include <string>
#include <vector>
#include <array>
#include <stdio.h>

using namespace std;


bool forUsed = false;
vector<string> error(); 
string errorString = "";
int errorCount = 0;
string identifiers = "Identifiers: ";
string constants = "Constants: ";
bool keyIsUsed[7] = {false};

bool operatorsUsed[13] = {false};
bool delimetersUsed[4] = {false};
int leftParenCount = 0;
int rightParenCount = 0;

const string operatorList[] = {"+", "-", "*", "/", "++", "--", "=", "==", "<", ">", "&&", "||", "!"};
const string delimiterList[] = {"(", ")", ";", ","};
const string keywords[] = {"BEGIN", "END", "FOR", "WHILE", "IF", "ELSE", "ELSEIF"};



int parseDigits(string line, int index){
	string num = "";
	num += line.at(index);
	index++;
	while(line.at(index) >= 48 && line.at(index) <= 57){
		num += line.at(index);
		index++;
	}

	constants += num + " ";
	return index--;
}

int parseSymbol(string line, int index){

	string curr = ""; 
	curr += line.at(index);

	if(line.at(index) == '+' || line.at(index) == '-' || line.at(index) == '=' || line.at(index) == '&' || line.at(index) == '|'){
		string nextLet = "";
		nextLet += line.at(index + 1);
		if(curr.compare(nextLet) == 0){
			curr = curr + curr;
			index++;
		}
	}

	for(int i = 0; i < 4; i++){
		if(delimiterList[i] == curr){
			//parseDelimiter(curr);
			delimetersUsed[i] = true;
			return index;
		}
	}

	for(int i = 0; i < 13; i++){
		if(operatorList[i] == curr){
			//parseOperator(curr);
			operatorsUsed[i] = true;
			return index;
		}
	}
}


int parseLower(string line, int index){

	string tempKey = "";
	tempKey += line.at(index);
	index++;
	while(line.at(index) >= 97 && line.at(index) <= 122){
		tempKey += line.at(index);
		index++;
	}

	if(identifiers.find(tempKey) == string::npos){
		identifiers += tempKey + " ";}
	return index--;
}


void keyWordError(string word, string messError){

	if(messError.compare("noKeyword") == 0){ //if the error is from isKeyword
		
		errorString += "Error(" + to_string(errorCount) + "): " + word + " is not a keyword." + "\n";
		//string errorMessage = "Error(" + errString + "): " + word + " is not a keyword."
		
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
		keyWordError(word, "noKeyword");
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
	index++;
	while(line.at(index) >= 65 && line.at(index) <= 90){
		tempKey += line.at(index);
		index++;
	}

	isKeyword(tempKey);
	return index--;

}

void parseLine(string line){

	for(int i = 0; i < line.size(); i++){
		char curr = line.at(i);

		if(curr >= 65 && curr <= 90){  //check for capital letters
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
}

void print(){
	cout << "Keywords: ";
	for(int i = 0; i < 7; i++){
		if(keyIsUsed[i]){
			cout << keywords[i] << " ";
		}
	} cout << endl;

	cout << identifiers;

	cout << constants;

	cout << "Operatros: ";
	for(int i = 0; i < 13; i++){
		if(operatorsUsed[i]){
			cout << operatorList[i] << " ";
		}
	} cout << endl;

	cout << "Delimiters: ";
	for(int i = 0; i < 4; i++){
		if(delimetersUsed[i]){
			cout << delimiterList[i] << " ";
		}
	} cout << endl;

}

