Lang:Lang(){
	this->forUsed = false;
	this->keyIsUsed[7] = {false};
	this->errors
}

void parseLine(string line){

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

void parseUpper(string line, int index){

	string tempKey = "";
	tempKey += line.at(index);
	index++;
	while(line.at(index) >= 65 && line.at(index) <= 90){
		tempKey += line.at(index);
		index++;
	}

	isKeyword(tempKey);


}

void parseLower(string line, int index){

	string tempKey = "";
	tempKey += line.at(index);
	index++;
	while(line.at(index) >= 97 && line.at(index) <= 122){
		tempKey += line.at(index);
		index++;
	}

	addIdentifier(tempKey);


}

void isKeyword(string word){
	const string keywords[] = {"BEGIN", "END", "FOR", "WHILE", "IF", "ELSE", "ELSEIF"};
	int keyIndex = -1;

	for(int i = 0; i < keywords.length; i++){
		if(word.compare(keywords[i]) == 0){
			keyIndex = i;
		}
	}

	bool keyIsUsed[7] = {false};

	if(keyIndex == -1){
		keyWordError(word);
	}
	else{
		keyIsUsed[i] = true;
	}
}

void keyWordError(string word){
	//add an error to a list of error key words which occur
}


void Lang::addIdentifier(string word){

}
