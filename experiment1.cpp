#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <math.h>

using namespace std;

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
		cout << "Sqsum = " << sqsum << endl;
	}
	return sqrt(sqsum);

}

int main()
{
	string word1, word2;
	vector<int> score1, score2;

	cout << "Input word1\n>>";
	cin >> word1;



	if (!onlyLetters(word1))
	{
		cout << "ERR: Only letters\n";
		return 1;
	}
	word1 = convertToUpper(word1);

	cout << "Calculating score1...\n";

	score1 = calculateScoreVector(word1);

	cout << "Getting magnitude...:\n";
	cout << calculateVectorMagnitude(score1);

	return 0;

}
