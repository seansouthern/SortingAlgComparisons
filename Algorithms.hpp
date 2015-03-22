#include <string>
#include <stdlib.h>

class Algorithms
{
private:
	std::string * 	swapStrings	(std::string * wordArray, int firstIndex, int secondIndex);
	void			printReport	(int algUsed, int percent);
	std::string * 	merge(std::string * left, std::string * right, int leftLength, int rightLength);

public:
	std::string * insertionSort	( std::string * unsortedWords, int LengthArray);
	std::string * selectionSort	( std::string * unsortedWords, int lengthArray);
	std::string * mergeSort		( std::string * unsortedWords, int lengthArray);
	std::string * quickSort		( std::string * unsortedWords, int lengthArray);
	int comparisonCounter;
	int swapCounter;
};


std::string * Algorithms::swapStrings(std::string * wordArray, int firstIndex, int secondIndex)
{
	std::string temp;
	temp = wordArray[firstIndex];
	wordArray[firstIndex] = wordArray[secondIndex];
	wordArray[secondIndex] = temp;
	return wordArray;
}


void Algorithms::printReport( int algUsed, int percentUsed )
{
	std::string alg;
	switch(algUsed)
	{
	case 0: alg = " insertion";
	break;
	case 1: alg= "selection";
	break;
	case 2: alg = "merge";
	break;
	case 4: alg = "quick";
	break;
	}
	std::cout << comparisonCounter << " comparisons made for a " << percentUsed <<  "% " << alg << " sort" << std::endl;
	std::cout << swapCounter << " array element swaps made for a " << percentUsed << "% " << alg << " sort" << std::endl;

}


std::string * Algorithms::insertionSort ( std::string * unsortedWords, int lengthArray)
{
	comparisonCounter = 0;
	swapCounter = 0;

	int j;
	for(int i = 1; i < lengthArray - 1; i++)
	{
		j = i;
		while( j > 0 && unsortedWords[ j - 1 ] > unsortedWords[j])
		{
			swapStrings(unsortedWords, j, j-1);
			swapCounter++;
			j--;
		}
		comparisonCounter+=2;
	}
	printReport(0, 100);
	return unsortedWords;
}



std::string * Algorithms::selectionSort(std::string * unsortedWords, int lengthArray)
{
	comparisonCounter = 0;
	swapCounter = 0;

	int i;
	int j;
	int jMin;
	for(i = 0 ; i < lengthArray - 1; i++)
	{
		jMin = i;
		for(j = i+1; j < lengthArray; j++)
		{
			if(unsortedWords[j] < unsortedWords[jMin])
			{
				jMin = j;
			}
			comparisonCounter++;
		}
		if(jMin != j)
		{
			swapStrings(unsortedWords, i, jMin);
			swapCounter++;
		}
		comparisonCounter++;
	}
	printReport(1, 100);
	return unsortedWords;
}


//Merge Sort Pseudocode
/*
 * function merge_sort(list m)
    // Base case. A list of zero or one elements is sorted, by definition.
    if length(m) <= 1
        return m

    // Recursive case. First, *divide* the list into equal-sized sublists.
    var list left, right
    var integer middle = length(m) / 2
    for each x in m before middle
         add x to left
    for each x in m after or equal middle
         add x to right

    // Recursively sort both sublists
    left = merge_sort(left)
    right = merge_sort(right)

    // Then merge the now-sorted sublists.
    return merge(left, right)
 */

std::string * Algorithms::mergeSort(std::string * unsortedWords, int lengthArray)
{
	comparisonCounter = 0;
	swapCounter = 0;

	if(lengthArray <= 1)
	{
		return unsortedWords;
	}

	int leftLength = lengthArray/2;
	std::string * left = new std::string[leftLength];

	int rightLength = lengthArray - leftLength;
	std::string * right = new std::string[rightLength];
	std::cout << leftLength << " : is leftLength    " << rightLength << " : is rightLength   "  << std::endl;

	// Will round down
	int middle = lengthArray / 2;
	std::cout << middle << " : is the middle" << std::endl;
	for(int i = 0; i < middle; i++)
	{
		left[i] = unsortedWords[i];
	}

	for(int j = middle; j < lengthArray; j++)
	{
		right[j - middle] = unsortedWords[j];
	}
	// TODO Make sure array lengths are right, Double check this
	left = mergeSort(left, lengthArray - middle - 1); //middle);
	right = mergeSort(right, lengthArray - middle);

	return merge(left, right, leftLength, rightLength);

	printReport(2,100);

	return unsortedWords;

}

std::string * Algorithms::merge(std::string * left, std::string * right, int leftLength, int rightLength)
{
	std::string * resultList = new std::string[leftLength + rightLength];

	int l = 0;
	int r = 0;

	while(l < leftLength && r < rightLength)
	{
		if(left[l] <= right[r])
		{
			resultList[l+r] = left[l];
			l++;
		}
		else
		{
			resultList[l+r] = right[r];
			r++;
		}
		comparisonCounter++;
		swapCounter++;
	}

	while(l < leftLength)
	{
		resultList[l+r] = left[l];
		l++;
		swapCounter++;
	}
	while(r < rightLength)
	{
		resultList[l+r] = right[r];
		r++;
		swapCounter++;
	}

	return resultList;
}









