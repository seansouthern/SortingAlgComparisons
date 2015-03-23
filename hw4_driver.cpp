#include <stdlib.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <iostream>
#include <ctype.h>

#include "Algorithms.hpp"
#include "Utils.hpp"

// We need to initialize two static counters for recording the work
//  done by the recursive sort algorithms.
int Algorithms::staticCompCounter = 0;
int Algorithms::staticSwapCounter = 0;



int main()
{

	// Read in our dirty input text for cleaning
	std::ifstream inputText("input.txt");
	std::stringstream buffer;
	buffer << inputText.rdbuf();
	std::string buffString = buffer.str();

	// Define the characters we want to strip, mostly non-letter punctuation
	// Remember to escape quotation mark
	char chars[] = "\"-,.!;:{}_()?\r\t\n";

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
	unsigned int endPos = buffString.find(delimiter);
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
		// Also ignore single quotations on their own and not part of a
		// contraction
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


	Algorithms algs;
/*
	std::cout << "Running Insertion Sort on an unsorted array" << std::endl;
	std::string * insertionArray = copyArray(unsortedWords, 5000);
	algs.insertionSort(insertionArray, 5000);
	algs.printReport(0,100);

	std::cout << std::endl;

	std::cout << "Running Insertion Sort on an already sorted array" << std::endl;
	algs.insertionSort(insertionArray, 5000);
	algs.printReport(0,100);

	std::cout << std::endl;

	std::cout << "Running Selection Sort on an unsorted array" << std::endl;
	std::string * selectionArray = copyArray(unsortedWords, 5000);
	std::string * selectSorted = algs.selectionSort(selectionArray, 5000);
	algs.printReport(1,100);

	std::cout << std::endl;

	std::cout << "Running Selection Sort on an already sorted array" << std::endl;
	algs.selectionSort(selectSorted, 5000);
	algs.printReport(1,100);
*/
	std::cout << std::endl;

	Algorithms::staticCompCounter = 0;
	Algorithms::staticSwapCounter = 0;
	std::cout << "Running Merge Sort on an unsorted array" << std::endl;
	std::string * mergeArray = copyArray(unsortedWords, 5000);
	mergeArray = algs.mergeSort(mergeArray, 5000);
	algs.printReport(2, 100);

	std::cout << std::endl;

	//reset our static counters that monitor the recursive algorithms
	// between successive runnings of the algs
	Algorithms::staticCompCounter = 0;
	Algorithms::staticSwapCounter = 0;
	std::cout << "Running Merge Sort on an already sorted array" << std::endl;
	mergeArray = algs.mergeSort(mergeArray, 5000);
	algs.printReport(2, 100);

	std::cout << std::endl;



	Algorithms::staticCompCounter = 0;
	Algorithms::staticSwapCounter = 0;
	std::string * quickArray = copyArray(unsortedWords, 5000);
	//printArray(quickArray, 5000);
	std::cout << "Running Quick Sort on an unsorted array" << std::endl;
	quickArray = algs.quickSort(quickArray, 0, 4999);
	algs.printReport(3,100);

	std::cout << std::endl;

	Algorithms::staticCompCounter = 0;
	Algorithms::staticSwapCounter = 0;
	//printArray(quickArray, 5000);
	std::cout << "Running Quick Sort on an already sorted array" << std::endl;
	quickArray = algs.quickSort(quickArray, 0, 4999);
	algs.printReport(3,100);

	std::cout << std::endl;

	/*
	 *
	 * 12. Repeat the above steps 1-11 for arrays of size 10, 50, 100, 1000 and 5000 strings. In addition, create test
files that have the first 25%, 50% and 75% of words already sorted. Rerun the above steps and record
the algorithms' runtimes (number of comparisons). Fill out the table below, plot it as a graph, and write
one (1) paragraph what you learned/observed. Submit this write-up as a pdf file with your code – name
this file Analysis.pdf.
Runtimes
In
	 */

	std::string * unsortedWords5000 = 	copyArray(unsortedWords, 5000);
	std::string * unsortedWords1000 =	copyArray(unsortedWords, 1000);
	std::string * unsortedWords100	=	copyArray(unsortedWords, 100);
	std::string * unsortedWords50	=	copyArray(unsortedWords, 50);
	std::string * unsortedWords10	=	copyArray(unsortedWords, 10);


	// Total dimensions are [4 PreSortLevels][5 SizesOfInput][4 SortingAlgs][2 AlgorithmWorkCounters]

	// 0pc Sorted Lists, size 5000 1000 100 50 10
	int * unsorted5000longResults = runAllAlgs(unsortedWords5000, 5000);
	int * unsorted1000longResults = runAllAlgs(unsortedWords1000, 1000);
	int * unsorted100longResults = runAllAlgs(unsortedWords100, 100);
	int * unsorted50longResults = runAllAlgs(unsortedWords50, 50);
	int * unsorted10longResults = runAllAlgs(unsortedWords10, 10);


	// 25pc Sorted Lists, size 5000 1000 100 50 10
	std::string * semi25pc5000long = generate25pcSortedLists(unsortedWords5000, 5000);
	std::string * semi25pc1000long = generate25pcSortedLists(unsortedWords1000, 1000);
	std::string * semi25pc100long = generate25pcSortedLists(unsortedWords100, 100);
	std::string * semi25pc50long = generate25pcSortedLists(unsortedWords50, 50);
	std::string * semi25pc10long = generate25pcSortedLists(unsortedWords10, 10);

	int * semi25pc5000longResults = runAllAlgs(semi25pc5000long, 5000);
	int * semi25pc1000longResults = runAllAlgs(semi25pc1000long, 1000);
	int * semi25pc100longResults = runAllAlgs(semi25pc100long, 100);
	int * semi25pc50longResults = runAllAlgs(semi25pc50long, 50);
	int * semi25pc10longResults = runAllAlgs(semi25pc10long, 10);

	// 50pc Sorted Lists, size 5000 1000 100 50 10
	std::string * semi50pc5000long = generate50pcSortedLists(unsortedWords5000, 5000);
	std::string * semi50pc1000long = generate50pcSortedLists(unsortedWords1000, 1000);
	std::string * semi50pc100long = generate50pcSortedLists(unsortedWords100, 100);
	std::string * semi50pc50long = generate50pcSortedLists(unsortedWords50, 50);
	std::string * semi50pc10long = generate50pcSortedLists(unsortedWords10, 10);

	int * semi50pc5000longResults = runAllAlgs(semi50pc5000long, 5000);
	int * semi50pc1000longResults = runAllAlgs(semi50pc1000long, 1000);
	int * semi50pc100longResults = runAllAlgs(semi50pc100long, 100);
	int * semi50pc10longResults = runAllAlgs(semi50pc10long, 10);
	int * semi50pc50longResults = runAllAlgs(semi50pc50long, 50);

	// 75pc Sorted Lists, size 5000 1000 100 50 10
	std::string * semi75pc5000long = generate75pcSortedLists(unsortedWords5000, 5000);
	std::string * semi75pc1000long = generate75pcSortedLists(unsortedWords1000, 1000);
	std::string * semi75pc100long = generate75pcSortedLists(unsortedWords100, 100);
	std::string * semi75pc50long = generate75pcSortedLists(unsortedWords50, 50);
	std::string * semi75pc10long = generate75pcSortedLists(unsortedWords10, 10);

	int * semi75pc5000longResults = runAllAlgs(semi75pc5000long, 5000);
	int * semi75pc1000longResults = runAllAlgs(semi75pc1000long, 1000);
	int * semi75pc100longResults = runAllAlgs(semi75pc100long, 100);
	int * semi75pc50longResults = runAllAlgs(semi75pc50long, 50);
	int * semi75pc10longResults = runAllAlgs(semi75pc10long, 10);

	std::cout << "Results" << std::endl;


	std::cout << std::setw(30) << "Insertion Sort" << std::setw(30) << "Selection Sort" <<std::setw(30) << "Merge Sort" <<std::setw(30) <<  "Quick Sort" <<  std::endl;


	printArrayLine(unsorted5000longResults, 8);
	printArrayLine(unsorted1000longResults, 8);
	printArrayLine(unsorted100longResults, 8);
	printArrayLine(unsorted50longResults, 8);
	printArrayLine(unsorted10longResults, 8);

	printArrayLine(semi25pc5000longResults, 8);
	printArrayLine(semi25pc1000longResults, 8);
	printArrayLine(semi25pc100longResults, 8);
	printArrayLine(semi25pc50longResults, 8);
	printArrayLine(semi25pc10longResults, 8);

	printArrayLine(semi50pc5000longResults, 8);
	printArrayLine(semi50pc1000longResults, 8);
	printArrayLine(semi50pc100longResults, 8);
	printArrayLine(semi50pc50longResults, 8);
	printArrayLine(semi50pc10longResults, 8);

	printArrayLine(semi75pc5000longResults, 8);
	printArrayLine(semi75pc1000longResults, 8);
	printArrayLine(semi75pc100longResults, 8);
	printArrayLine(semi75pc50longResults, 8);
	printArrayLine(semi75pc10longResults, 8);



	// Cleanup, deallocate your used heap memory
	//delete[] insertionArray;
	//delete[] selectionArray;
	//delete[] mergeArray;
	//delete[] quickArray;



	delete[] unsortedWords5000;
	delete[] unsortedWords1000;
	delete[] unsortedWords100;
	delete[] unsortedWords50;
	delete[] unsortedWords10;


	std::cout << "Finished" << std::endl;
}
