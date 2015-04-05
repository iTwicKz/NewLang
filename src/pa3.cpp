#include <string>
#include <iostream>
#include <fstream>
#include "separate.cpp"

using namespace std;

int main(){
	cout << "Please enter the file path:" << endl;
	string fileName;
	cin >> fileName;

	//vector<string> fileLines;


	ifstream input (fileName);
	string line;

	if(input.is_open()){
		while (getline(input, line)){
			parseLine(line);
		}
		input.close();
	}

	else count << "Unable to open file";

	print();
}


	