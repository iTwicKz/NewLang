#include <string>		//strings
#include <vector>   	//for output strings
#include <iostream>		//takes in file name
#include <fstream>		//reading file
#include <stack>		//finding depth of loops
#include <cmath> 		//absolute value

using namespace std;

string line;				//input file is taken line by line

vector<string> error; 		//errors
vector<string> constants;	//constants
vector<string> identifiers;	//identifiers

int errorCount = 0;			//allows for error to be counted

stack <string> loopStack;	//traces depth of loop
int loopMax = 0;			//max depth reached
int loopCount = 0;			//depth at moment

int leftParenCount = 0;		//counts total left parentheses
int rightParenCount = 0;	//counts total right parentheses

//++++++++++++++++++++++++++++++ DICTIONARIES +++++++++++++++++++++++++++++++++++++++++++++++++++//

const string operatorList[] = {"+", "-", "*", "/", "++", "--", "=", "==", "<", ">", "&&", "||", "!"};
 bool operatorsUsed[13];	//avoids repeats
const string delimiterList[] = {"(", ")", ";", ","};
 bool delimetersUsed[4];	//avoids repeats
const string keywords[] = {"BEGIN", "END", "FOR", "WHILE", "IF", "ELSE", "ELSEIF"};
 bool keyIsUsed[7];			//avoid repeats

//++++++++++++++++++++++++++++++ ERROR CHECKING +++++++++++++++++++++++++++++++++++++++++++//

int forUsed = 0;			//checks if previous line is FOR
int loopUsed = 0;			//checks if previous line is WHILE
bool keywordFirst = false;  //checks if first word is a keyword
bool ifIsUsed = false;		//checks if IF was used previously

//+++++++++++++++++++++++++++++++++ METHODS ++++++++++++++++++++++++++++++++++++++++++++//

int parseDigits(string line, int index){ //takes in digits
	
	string num = "";
	num += line.at(index);
	
	int size = static_cast<int>(line.size());			//static_cast USED TO PARSE type_size TO int
	if(index != size){ 
		index++;
		while(line.at(index) >= 48 && line.at(index) <= 57){   //appends other consequetive digits
			num += line.at(index);
			index++;
		}
	}

	bool isUsed = false;
	for(unsigned i = 0; i < constants.size(); i++){
		if(num.compare(constants[i]) == 0) isUsed = true;		//checks for duplicates
	}
	if(!isUsed){
		constants.push_back(num); }								//adds constant to vector
	
	return index--;
}

int parseSymbol(string line, int index){
	
	string curr = ""; 
	curr += line.at(index);			

	if(line.at(index) == '+' || line.at(index) == '-' || line.at(index) == '=' || line.at(index) == '&' || line.at(index) == '|'){
		string nextLet = "";								//checking for the double symbol operators
		if(index <= static_cast<int>(line.size())){
			nextLet += line.at(index + 1); 					//doubles symbol
			if(curr.compare(nextLet) == 0){
				curr = curr + curr;
				index++;
			}
		}
	}

	for(int i = 0; i < 4; i++){								//checking if delimiter
		if(delimiterList[i] == curr){
			delimetersUsed[i] = true;
			return index;
		}
	}

	for(int i = 0; i < 13; i++){							//checking if operator
		if(operatorList[i] == curr){
			operatorsUsed[i] = true;
			return index;
		}
	}
	return index;
}


int parseLower(string line, int index){						//looking for identifiers
	
	string tempKey = "";
	tempKey += line.at(index);
	if( index < static_cast<int>(line.size()) - 1)
		index++;

	while(line.at(index) >= 97 && line.at(index) <= 122){	//checks if next char is lowercase
		tempKey += line.at(index);							//if so, append
		if(index < static_cast<int>(line.size()) - 1){
			index++;

			  }
	}
	
	bool isUsed = false;			
	for(unsigned i = 0; i < identifiers.size(); i++){
		if(tempKey.compare(identifiers[i]) == 0) isUsed = true;	//checks for duplicates
	}
	if(!isUsed){
		identifiers.push_back(tempKey); }						//adds to vector
	index--;
	return index;
}


void errorParser(string word, string messError){

	if(messError.compare("noKeyword") == 0){ 			//ERROR FOR INVALID KEYWORD
		error.push_back(word + " is not a keyword.");
		errorCount++;
	}
	else if(messError.compare("noSemicolon") == 0){ 	//ERROR FOR NO SEMICOLON
		error.push_back("Missing semicolon");
		errorCount++;
	}
	else if(messError.compare("leftParen") == 0){ 		//ERROR FOR MISSING LEFT PARENTHESES
		error.push_back("Invalid parentheses: Missing ( in " + word);
		errorCount++;
	}
	else if(messError.compare("rightParen") == 0){ 		//ERROR FOR MISSING RIGHT PARENTHESES
		error.push_back("Invalid parentheses: Missing ) in " + word);
		errorCount++;
	}
	else if(messError.compare("parenInOrder") == 0){	//ERROR FOR PARENTHESES OUT OF ORDER
		error.push_back("Invalid parentheses: Parentheses out of order in " + word);
		errorCount++;
	}
	else if(messError.compare("forLoopParen") == 0){ 	//ERROR FOR NON-LOGICAL STATEMENT
		error.push_back("Invalid statement after for loop");
		errorCount++;
	}
	else if(messError.compare("tooManyCommas") == 0){ 	//ERROR FOR MORE THAN TWO COMMAS IN FOR
		error.push_back("For loop statement has too many commas.");
		errorCount++;
	}
	else if(messError.compare("noIf") == 0){            //ERROR FOR NO IF BEFORE ELSE
		error.push_back("No IF before this " + word);
		errorCount++;
	}
	else if(messError.compare("missingBegin") == 0){ 	//ERROR FOR NO BEGIN
		error.push_back("Missing BEGIN");
		errorCount++;
	}
	else if(messError.compare("endMissing") == 0){ 		//ERROR FOR NO END
		error.push_back("Missing END");
		errorCount++;
	}
	else if(messError.compare("missForBegin") == 0){ 	// ERROR FOR NO LOOP BEFORE BEGIN
		error.push_back("Missing Loop before BEGIN");
		errorCount++;
	}
	else if(messError.compare("noBegin") == 0){ 		// ERROR FOR NO BEGIN AFTER LOOP
		error.push_back("No BEGIN after " + word);
		errorCount++;
	}
	else if(messError.compare("invalidParen") == 0){ 	//ERROR FOR INVALID PARENTHESES
		error.push_back("Invalid Parentheses.");
		errorCount++;
	}
		
}

void checkCommas(int left, int right){			//checks for commas after for loop
	int comma1 = -1;
	int comma2 = -1;
	bool overCommas = false;
	for(unsigned i = 0; i < line.size(); i++){
		
		if(line.at(i) == ',' && comma1 > -1){ comma2 = i; break; }		//if there is already one comma
		else if(line.at(i) == ',') comma1 = i;							//if initial comma is found
		else if(line.at(i) == ',' && comma1 > -1 && comma2 > -1) {overCommas = true;}	 //if there are already two commas
	}

	if(overCommas) errorParser("", "tooManyCommas");
	else if(!(comma1 > left && comma2 > left && comma1 < right && comma2 < right)){
		errorParser("", "forLoopParen");	//Commas are not in parentheses
	}

}

void checkParentheses(string which){   						//Checks if parentheses are in order
	
	int leftParenIndex = -1;
	int rightParenIndex = -1;
	
	for(unsigned i = 0; i < line.length(); i++){
		if(line.at(i) == '(') leftParenIndex = i;			//finds left parentheses
		else if(line.at(i) == ')') rightParenIndex = i;		//finds right parentheses
	}
	if(leftParenIndex < 0) errorParser(which, "leftParen");
	else if(rightParenIndex < 0) errorParser(which, "rightParen");
	else if(rightParenIndex - leftParenIndex < 0) errorParser(which, "parenInOrder"); //checks )(

	if(which.compare("For loop") == 0){
		checkCommas(leftParenIndex, rightParenIndex);
	}
}

void isKeyword(string word){						//checks if uppercase is keyword
	
	int keyIndex = -1;

	for(int i = 0; i < 7; i++){
		if(word.compare(keywords[i]) == 0){			//looks through dictionary of Keywords
			keyIndex = i;
		}
	}

	if(loopUsed == 2){
		if(keyIndex != 0){
			errorParser("loop.", "noBegin");		//checks if there was a BEGIN after loop
			loopCount--;
		}
	}
	
	if(keyIndex == -1){
		errorParser(word, "noKeyword");				//if no keyword match if found
	}
	else{
		keyIsUsed[keyIndex] = true;					//ensure that no duplicate prints
	}

	switch(keyIndex){
		case 0:{ //BEGIN
			if(loopUsed != 2) errorParser("", "missForBegin"); //Makes sure there was a previous loop
			break;
		}
		case 1:{ //END
			string check = loopStack.top();
			if(check.compare("BEGIN") == 0){				//checks if there is a BEGIN
				loopStack.pop();
			}
			else errorParser("", "missingBegin");			//if not, create an error
			
			if(loopCount > loopMax) loopMax = loopCount;	//checks for max loop depth
			loopCount--;									//decreases current loop depth count

			break;
		}
		case 2:{ //FOR
			loopUsed = 1;						//marks that FOR has started
			checkParentheses("For loop");		//checks parentheses
			loopStack.push("BEGIN");			//adds BEGIN to stack
			loopCount++;						//increases count
		
			break;
		}
		case 3:{ //WHILE
			loopUsed = 1;						//marks that WHILE has started
			checkParentheses("While loop");		//checks parentheses
			loopStack.push("BEGIN");			//adds BEGIN to stack
			loopCount++;						//increases count
			break;
		}
		case 4:{ //IF
			ifIsUsed = true;
			checkParentheses("If statement");						//checks for parentheses
			break;
		}
		case 5:{ //ELSE
			if(!ifIsUsed) errorParser("Else statement", "noIf");	//checks for if
			break;
		}
		case 6:{ //ELSEIF
			if(!ifIsUsed) errorParser("Else-if statement", "noIf");	//checks for if
			checkParentheses("Else-if statement");					//checks for parentheses
			break;
		}
	}

}


int parseUpper(string line, int index){

	string tempKey = "";
	tempKey += line.at(index);
	if(index < static_cast<int>(line.size()))
		index++;
	while(line.at(index) >= 65 && line.at(index) <= 90){
		tempKey += line.at(index);
		if(index == static_cast<int>(line.size()) - 1) break;
		else index++;
	}
	
	isKeyword(tempKey);
	return index--;

}

void parenCheck(string line){					//increases parentheses count, which is checked later
	
	for(unsigned i = 0; i < line.size(); i++){
		if(line.at(i) == '(') leftParenCount++;
		if(line.at(i) == ')') rightParenCount++;
	}
}

void parseLine(string line){

	for(int i = 0; i < static_cast<int>(line.size()); i++){
		char curr = line.at(i);

		if(loopUsed == 2){
			if(curr != 'B'){					//ensures that loop is followed by BEGIN
				errorParser("loop.", "noBegin");
				loopCount--;
				loopUsed = 0;
			}
		}

		if(curr >= 65 && curr <= 90){  			//check for capital letters
			if(i == 0) keywordFirst = true;
			i = parseUpper(line, i);
		}
		else if(curr >= 97 && curr <= 122){  	//check for lowercase letters
			i = parseLower(line, i);
		}
												//check for all special characters
		else if(curr == '+' || curr == '-' || curr == '*' || curr == '/' || curr == '=' || 
			     curr == '<' || curr == '>' || curr == '&' || curr == '|' || curr == '!' ||
			      curr == '(' || curr == ')' || curr == ';' || curr == ','){
			
			i = parseSymbol(line, i);
		}
		else if(curr >= 48 && curr <= 57){ 		//check for digits
			i = parseDigits(line, i);
		}
	}

	if(!keywordFirst){			//checks if there was initially a keyword
		if(line.at(static_cast<int>(line.size()) - 1) != ';'){	//if not, the statement must end with semicolon
			errorParser("", "noSemicolon");
		}
	}
	
}

void print(){

	//+++++++ printing keywords +++++++++++++++++++++++++++++++++++++++++++//
	cout << "Keywords: ";
	for(int i = 0; i < 7; i++){
		if(keyIsUsed[i]){
			cout << keywords[i] << " ";
		}
	} cout << endl;

	//++++++++ printing identifiers +++++++++++++++++++++++++++++++++//
	cout<< "Identifiers: ";
	for(unsigned i = 0; i < identifiers.size(); i++){
		cout << identifiers[i] << " ";
	}
	cout<<endl;

	//++++++++ printing constants ++++++++++++++++++++++++++++//
	cout<< "Constants: ";
	for(unsigned i = 0; i < constants.size(); i++){
		cout << constants[i] << " ";
	}
	cout<<endl;

	//++++++++ printing operators +++++++++++++++++++++//
	cout << "Operatros: ";
	for(int i = 0; i < 13; i++){
		if(operatorsUsed[i]){
			cout << operatorList[i] << " ";
		}
	} cout << endl;

	//++++++++ printing delimiters ++++++++++++++//
	cout << "Delimiters: ";
	for(int i = 0; i < 4; i++){
		if(delimetersUsed[i]){
			cout << delimiterList[i] << " ";
		}
	} cout << endl << endl;

	//++++++++ printing all errors +++++++//
	for(int i = 0; i < errorCount; i++){
		cout << "Error(" << i+1 << "): " << error[i] << endl;
	}
}

int main(int argc, char* argv[]){
	try{
		cout << "Please enter the file path:" << endl;
		const char* fileName = argv[1];		//recieves fileName through command
		cout << fileName << endl << endl;
		if(argc > 0){
		ifstream input (fileName, ios::in);	//intializes stream for input file			
		loopStack.push("Start");			//sets bases of the stack

		//if(argc > 1){
		if(input.is_open()){				//checks if file is open
			while (getline(input, line)){	//iterates line by line
					
				parseLine(line);	

				//++++++Reitializing Values+++++++++//
				keywordFirst = false;

				if(loopUsed > 0){					//sees if loop was in this line
					loopUsed++;
				}
				if(loopUsed > 2){					//sees if loop was two lines ago
					loopUsed = 0;					//if so, reset count
				}
				

				parenCheck(line);							//checks parentheses in line
				if(leftParenCount != rightParenCount){
					errorParser("", "invalidParen");
				}

				leftParenCount = 0;
				rightParenCount = 0;

			}
			input.close();

			if(loopStack.top().compare("Start") != 0){    //sees if there is anything left in stack
				errorParser("", "endMissing");
			}

			loopMax += abs(loopCount);					//checks if there is uncalled for loop depth
			if(loopMax > 0) cout << "The depth of nested loops is " << loopMax << endl << endl;
			else cout<<"Program does not contain loops" << endl << endl;

			print();			//prints rest of values
		}

		else cout << "Unable to open file";
	}


		

	}
	catch (exception const &exc)			//catches error due to invalid input file
    {
        cerr << "Exception caught " << exc.what() << "\n";
    }
    catch (...)								//catches any other errors
    {
        cerr << "Unknown exception caught\n";
    }
}

//static_cast<int>(variable) used to convert from size_type to int value so that code compiles in g++
