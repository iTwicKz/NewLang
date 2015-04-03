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
	this->operatosr = "";
	this->delimeters = "";
}

void Lang::parseLine(string line){

	for(int i = 0; i < line.size(); i++){
		char curr = line.at(i);

		if(curr >= 65 && curr <= 90){
			parseUpper(line, i);
		}
		else if(curr >= 97 && curr <= 122){
			parseLower(line, i);
		}
	}

}

void Lang::parseUpper(string line, int index){

	string tempKey = "";
	tempKey += line.at(index);
	index++;
	while(line.at(index) >= 65 && line.at(index) <= 90){
		tempKey += line.at(index);
		index++;
	}

	isKeyword(tempKey);


}

void Lang::parseLower(string line, int index){

	string tempKey = "";
	tempKey += line.at(index);
	index++;
	while(line.at(index) >= 97 && line.at(index) <= 122){
		tempKey += line.at(index);
		index++;
	}

	addIdentifier(tempKey);


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
