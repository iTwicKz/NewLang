#include <string>
using namespace std;

class Lang{
	private:
		bool forUsed;
		string keyIsUsed[];
		vector<string> error;
		int errorCount;
		string identifiers;
		string constants;
		string operators;
		string delimiters;
	
	public:
		Lang();
		void parseLine(string line);
		void parseUpper(string line, int index);
		void parseLower(string line, int index);
		void isKeyword(string word);
		void keyWordError(string word, string messError);
		void addIdentifier(string word);
