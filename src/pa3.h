#include <string>
using namespace std;

class Lang{
	private:
		bool forUsed;
		string keyIsUsed[];
		string errors[];
	public:
		Lang();
		void parseLine(string line);
		void parseUpper(string line, int index);
		void parseLower(string line, int index);
		void isKeyword(string word);
		void keyWordError(string word);
		void addIdentifier(string word);
