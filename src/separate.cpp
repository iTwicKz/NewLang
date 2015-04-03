#include <string>
#include <vector>
#include "pa3.h"
using namespace std;

Lang:Lang(){
	this->forUsed = false;
	this->keyIsUsed[7] = {false};
	vector<string> this->error(1); 
	this->errorCount = 0;
	this->identifiers = "";
	this->constants = "";
	this->operators = "";
	this->delimeters = "";
	this->leftParenCount = 0;
	this->rightParenCount = 0;
}

void Lang::parseLine(string line){

	for(int i = 0; i < line.size(); i++){
		char curr = line.at(i);

		if(curr >= 65 && curr <= 90){  //check for capital letters
			i = parseUpper(line, i);
		}
		else if(curr >= 97 && curr <= 122){  //check for lowercase letters
			i = parseLower(line, i);
		}
		else if((curr == 33 || curr == 38 || curr == 40 || curr == 41 || curr == 42 || 
			     curr == 43 || curr == 45 || curr == 47) || (curr >= 59 && curr <= 62)){
			     curr == 43 || curr == 45 || curr == 47) || (curr >= 59 && curr <= 62)){
			i = parseSymbol(line, i);
		}

	}

}

int Lang::parseSymbol(string line, int index){

	const string delimiterList[] = {"(", ")", ";", ","};
	const string operatorList[] = {"+", "-", "*", "/", "++", "--", "=", "==", "<", ">", "&&", "||", "!"};

	string curr = line.at(index);

	if(line.at(index) == '+' || line.at(index) == '-' || line.at(index) == '=' || line.at(index) == '&' || line.at(index) == '|'){
		string nextLet = line.at(index + 1);
		if(curr.compare(nextLet) == 0){
			curr = curr + curr;
			index++;
		}
	}

	for(int i = 0; i < delimiterList.length; i++){
		if(delimiterList[i] == curr){
			parseDelimiter(delimiterList, curr);
			return index;
		}
	}

	for(int i = 0; i < operatorList.length; i++){
		if(operatorList[i] == curr){
			parseOperator(operatorList, curr);
			return index;
		}
	}
}

int Lang::parseUpper(string line, int index){

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

int Lang::parseLower(string line, int index){

	string tempKey = "";
	tempKey += line.at(index);
	index++;
	while(line.at(index) >= 97 && line.at(index) <= 122){
		tempKey += line.at(index);
		index++;
	}

	addIdentifier(tempKey);
	return index--;
}

void Lang::isKeyword(string word){
	const string keywords[] = {"BEGIN", "END", "FOR", "WHILE", "IF", "ELSE", "ELSEIF"};
	int keyIndex = -1;

	for(int i = 0; i < keywords.length; i++){
		if(word.compare(keywords[i]) == 0){
			keyIndex = i;
		}
	}

	bool keyIsUsed[7] = {false};

	if(keyIndex == -1){
		keyWordError(word, "noKeyword");
	}
	else{
		keyIsUsed[i] = true;
	}
}

void Lang::keyWordError(string word, string messError){

	if(messError.compare("noKeyword") == 0){ //if the error is from isKeyword
		error.push_back("Error(" + errorCount + "): " + word + " is not a keyword.");
		errorCount++;
	}
		
}


void Lang::addIdentifier(string word){
	identifiers = identifiers + " " + word;
}
