#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <math.h>
#include <fstream>

using namespace std;

class WordlistElement
{
public:
	WordlistElement():word{""}, scoreVector{{0}}, differenceMagnitude{0}
	{}

	WordlistElement(string pword, vector<int> pscoreVector, double pdifferenceMagnitude):
	word{pword}, scoreVector{pscoreVector}, differenceMagnitude{pdifferenceMagnitude}
	{}

	string getWord()
	{
		return word;
	}
	vector<int> getScoreVector()
	{
		return scoreVector;
	}
	double getDifferenceMagnitude()
	{
		return differenceMagnitude;
	}
	
	void setWord(string pword)
	{
		word = pword;
	}
	void setScoreVector(vector<int> pscoreVector)
	{
		scoreVector = pscoreVector;
	}
	void setDifferenceMagnitude(double pdifferenceMagnitude)
	{
		differenceMagnitude = pdifferenceMagnitude;
	}
private:
	string word;
	vector<int> scoreVector;
	double differenceMagnitude;
};

string convertToUpper(string word)
{
	for (int i=0; i<word.length(); i++)
	{
		word[i] = toupper(word[i]);
	}
	return word;
}

bool onlyLetters(const string& word)
{
	for (int i=0; i<word.length(); i++)
	{
		if(!isalpha(word[i]))
			return false;
	}
	return true;
}

vector<int> calculateScoreVector(const string& word)
{
	vector<int> scoreVector;
	for (int i=0; i<word.length(); i++)
	{
		scoreVector.push_back(word[i] - 65);
	}
	return scoreVector;
}

double calculateVectorMagnitude(const vector<int>& score)
{
	long sqsum;
	for (int i=0; i<score.size(); i++)
	{
		sqsum += pow(score[i], 2);
	}
	return sqrt(sqsum);

}

vector<int> calculateVectorialDifference(vector<int> vector1, vector<int> vector2)
{
	vector<int> difference;

	while(vector1.size() > vector2.size())
	{
		vector2.push_back(0);
//		cout << "Adding padding element 0 to vector2\n";
	}
	while(vector2.size() > vector1.size())
	{
		vector1.push_back(0);
//		cout << "Adding padding element 0 to vector1\n";
	}
	for (int i = 0; i<vector1.size(); i++) 
	{
		difference.push_back(vector1[i] - vector2[i]);
	}
	return difference;

}

void loadList(vector<WordlistElement>& pwordlistVector,ifstream& pwordlistFile, const vector<int>& refScore)
{
	WordlistElement element;
	string tmpword;

	while(pwordlistFile.good())
	{
		getline(pwordlistFile, tmpword);
		if(tmpword != "")
		{
		element.setWord(tmpword);
		element.setScoreVector(calculateScoreVector(tmpword));
		element.setDifferenceMagnitude(calculateVectorMagnitude(calculateVectorialDifference(calculateScoreVector(tmpword), refScore)));
		pwordlistVector.push_back(element);
		}
	}
//	cout << "finished reading file\n";
	pwordlistFile.close();
}

void getMinimum(vector<WordlistElement>& pwordlistVector)
{
	string out = pwordlistVector[0].getWord();
//	cout << "initial word = " << out << endl;
//	cout << "size = " << pwordlistVector.size() << endl;
	for(int i=1; i<pwordlistVector.size(); i++)
	{
		if(pwordlistVector[i].getDifferenceMagnitude() < pwordlistVector[i-1].getDifferenceMagnitude())
		{
			out = pwordlistVector[i].getWord();
//			cout << "temp winner = " << out << endl;
		}
			
	}
	cout << "Most similar word in wordlist: " << out << '\n';
}

int main(int argc, char** argv)
{
	WordlistElement word1;
	vector<WordlistElement> wordlistVector;
	ifstream wordlistFile;
	if (argc < 3)
	{
		cout << "ERR: 2 args: <word> <wordlistfile>\n";
		return 4;
	}
	word1.setWord(argv[1]);
	wordlistFile.open(argv[2]);
	word1.setScoreVector(calculateScoreVector(word1.getWord()));


	if (!wordlistFile.good())
	{
		cout << "ERR: Unable to open wordlist file\n";
		return 2;
	}

	if (!onlyLetters(word1.getWord()))
	{
		cout << "ERR: Only letters\n";
		return 1;
	}
	word1.setWord(convertToUpper(word1.getWord()));
	loadList(wordlistVector, wordlistFile, word1.getScoreVector());
	if(wordlistVector.size() < 1)
	{
		cout << "ERR: empty wordlist";
		return 5;
	}
	getMinimum(wordlistVector);

	return 0;

}
