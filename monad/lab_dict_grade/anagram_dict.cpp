/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */
#include "anagram_dict.h"
#include <algorithm> /* I wonder why this is included... */
#include <fstream>
using namespace std;
/** 
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */ 
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
	string word;
	ifstream words(filename);
	if(words.is_open())
	{
    		/* Reads a line from words into word until the file ends. */
    	for(int i = 0;getline(words, word);i++)
    	{
			string sortedWord = word; 
			sort(sortedWord.begin(), sortedWord.end());
			auto lookup = dict.find(sortedWord);
			if (lookup != dict.end())
			{
				(lookup->second).push_back(word);
			}
			else
			{
				vector<string> allWords;
				allWords.push_back(word);
				dict.insert(make_pair(sortedWord, allWords));
			}
 		}
	}
	
	
}
/** 
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */ 
AnagramDict::AnagramDict(const vector< string >& words)
{
	for (auto& word : words)
	{
		string sortedWord = word;
		sort(sortedWord.begin(), sortedWord.end());
		auto lookup = dict.find(sortedWord);
		if (lookup != dict.end())
		{
			(lookup->second).push_back(word);
		}
		else
		{
			vector<string> allWords;
			allWords.push_back(word);
            dict.insert(make_pair(sortedWord, allWords));
		} 
	}
}
/**
 * @param word The word to find anagrams of. 
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the 
 * word list.
 */
vector< string > AnagramDict::get_anagrams(const string& word) const
{
   	string sortedWord = word;
   	sort(sortedWord.begin(), sortedWord.end());
    auto lookup = dict.find(sortedWord);
    if (lookup != dict.end())
    	return lookup->second;
    else
    	return vector<string>();
}      
/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector< vector< string > > AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
	auto lookup = dict.begin();
   	vector< vector < string > > allAnagrams;
    while (lookup != dict.end())
    {
    	if (!((lookup->second).size() < 2))
    		allAnagrams.push_back(lookup->second);
	lookup++;
    }
    return allAnagrams;
}

