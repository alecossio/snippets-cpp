#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <math.h>

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

bool onlyLetters(string word)
{
	for (int i=0; i<word.length(); i++)
	{
		if(!isalpha(word[i]))
			return false;
	}
	return true;
}

vector<int> calculateScoreVector(string word)
{
	vector<int> scoreVector;
	for (int i=0; i<word.length(); i++)
	{
		scoreVector.push_back(word[i] - 65);
	}
	return scoreVector;
}

double calculateVectorMagnitude(vector<int> score)
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
		cout << "Adding padding element 0 to vector2\n";
	}
	while(vector2.size() > vector1.size())
	{
		vector1.push_back(0);
		cout << "Adding padding element 0 to vector1\n";
	}
	for (int i = 0; i<vector1.size(); i++) 
	{
		difference.push_back(vector1[i] - vector2[i]);
	}
	return difference;

}

int main()
{
	string word1;
	vector<string> words;
	vector<vector<int>> scores;

	cout << "Input words, enter EOF to finish (Ctrl+D):\n>>";
	while(cin >> word1)
	{
		words.push_back(word1);
	}
	cout << "OK, calculating...\n";
	
	for (int i =0; i<words.size(); i++)
	{
		if (!onlyLetters(words[i]))
		{
			cout << "ERR: Only letters\n";
			return 1;
		}
		words[i] = convertToUpper(words[i]);
		cout << "Calculating score...\n";
		scores.push_back(calculateScoreVector(words[i]));
	}
	vector<int> difference = calculateVectorialDifference(scores[0], scores[1]);
	
	cout << "Getting magnitude...:\n";
	cout << calculateVectorMagnitude(difference);

	return 0;

}
