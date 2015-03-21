#include <stdlib.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <iostream>
#include <ctype.h>

void printArray(std::string * wordArray)
{
	for(int i = 0; i < 5000; i++)
	{
		std::cout << i << " : " <<  wordArray[i] << std::endl;
	}
}

std::string * copyArray(std::string wordArray[])
{
	// We allocate the copied array on heap because we may not have enough room
	//  in this stack frame.
	std::string * copyOfArray = new std::string[5000];
	//Straight copy from original array to the next
	for(int x = 0; x < 5000; x++)
	{
		copyOfArray[x] = wordArray[x];
	}
	return copyOfArray;
}


int main()
{
	// Read in our dirty input text for cleaning
	std::ifstream inputText("input.txt");
	std::stringstream buffer;
	buffer << inputText.rdbuf();
	std::string buffString = buffer.str();

	// Define the characters we want to strip, mostly non-letter punctuation
	// Remember to escape quotation mark
	char chars[] = "\"-,.!;:{}()?\r\t\n";

	// Loop over entire text for each unwanted character
	for (unsigned int i = 0; i < strlen(chars); ++i)
	{
		// Iterate over every character in the text
		for(unsigned int j = 0; j < buffString.length(); j++ )
		{
			// Check whether each character is an instance of
			// the currently considered undesirable character
			// Replace it with whitespace if it matches
			if(buffString.at(j) == chars[i])
			{
				buffString.replace(j, 1, " ");
			}
			// If it doesn't match, try to convert it to lowercase
			// Will do nothing if the operation is invalid
			else if(buffString.at(j) != chars[i])
			{
				buffString.replace(j, 1, std::string(1, tolower(buffString.at(j))));
			}
		}
	}


	// Declare our array of valuable words
	std::string unsortedWords[5000];

	// Declare a string token for storing in our Words array
	// Define the delimiter to split words by (" ")
	// Define our initial start and end positions and a loop counter
	//	to stop us when we reach 5000 stored words
	std::string token;
	std::string delimiter = " ";
	int startPos = 0;
	int endPos = buffString.find(delimiter);
	int i = 0;

	// Tokenize the document into words split by the delimiter (" ")
	// Stop when you reach the terminating null character or you
	// 	store 5000 words
	while(endPos != std::string::npos && i < 5000) {
		// Take a substring spanning from the previous endPosition to the next occurrence
		// of the delimiter which endPos should already be set to, the second parameter is the
		// the number of characters long the substring will be
		token = buffString.substr(startPos, (endPos-startPos));

		// There may be more than one space between words, these will be
		// returned as zero length substrings and we should ignore them
		if(token.size() != 0 && token != "'")
		{
			// Store the word in our unsorted array
			unsortedWords[i] = token;
			// This counter stops the loop when we have 5000 words
			i++;
		}
		// Set our next start position as directly after the end point found
		// previously plus the length of the delimiter.
		startPos = endPos + delimiter.length();
		// Set the next end point to be the next occurrence of whitespace
		endPos = buffString.find(delimiter, startPos);
	}

	//printArray(unsortedWords);
	std::string * newArray = copyArray(unsortedWords);
	printArray(newArray);

	delete[] newArray;
	delete[] unsortedWords;
	std::cout << "Finished" << std::endl;
}

