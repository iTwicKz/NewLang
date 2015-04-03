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
		int leftParenCount;
		int rightParenCount;
	
	public:
		Lang();
		void parseLine(string line);
		int parseSymbol(string line, int index);
		int parseUpper(string line, int index);
		int parseLower(string line, int index);
		void isKeyword(string word);
		void keyWordError(string word, string messError);
		void addIdentifier(string word);
