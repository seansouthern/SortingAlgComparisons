#include <string>
#include <stdlib.h>

class Algorithms
{
private:
	std::string * 	swapStrings	(std::string * wordArray, int firstIndex, int secondIndex);
	std::string * 	merge(std::string * left, std::string * right, int leftLength, int rightLength);
	int 			partition(std::string * unsortedWords, int startIndex, int endIndex);
	int pivot;

public:
	void		  printReport	(int algUsed, int percent);
	std::string * insertionSort	( std::string * unsortedWords, int LengthArray);
	std::string * selectionSort	( std::string * unsortedWords, int lengthArray);
	std::string * mergeSort		( std::string * unsortedWords, int lengthArray);
	std::string * quickSort		( std::string * unsortedWords, int startIndex, int endIndex);
	int comparisonCounter;
	int swapCounter;
	static double staticCompCounter;
	static double staticSwapCounter;
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
	std::cout << comparisonCounter << " comparisons made for a " << percentUsed <<  "% " << alg << " sort" << std::endl;
	std::cout << swapCounter << " array element swaps made for a " << percentUsed << "% " << alg << " sort" << std::endl;
	break;
	case 1: alg= "selection";
	std::cout << comparisonCounter << " comparisons made for a " << percentUsed <<  "% " << alg << " sort" << std::endl;
	std::cout << swapCounter << " array element swaps made for a " << percentUsed << "% " << alg << " sort" << std::endl;
	break;
	case 2: alg = "merge";
	std::cout << staticCompCounter << " comparisons made for a " << percentUsed <<  "% " << alg << " sort" << std::endl;
	std::cout << staticSwapCounter << " array element swaps made for a " << percentUsed << "% " << alg << " sort" << std::endl;
	break;
	case 3: alg = "quick";
	std::cout << staticCompCounter << " comparisons made for a " << percentUsed <<  "% " << alg << " sort" << std::endl;
	std::cout << staticSwapCounter << " array element swaps made for a " << percentUsed << "% " << alg << " sort" << std::endl;
	break;
	}
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
	return unsortedWords;
}


std::string * Algorithms::mergeSort(std::string * unsortedWords, int lengthArray)
{
	if(lengthArray <= 1)
	{
		return unsortedWords;
	}

	int leftLength = lengthArray/2;
	std::string * left = new std::string[leftLength];

	int rightLength = lengthArray - leftLength;
	std::string * right = new std::string[rightLength];

	int middle = leftLength;
	for(int i = 0; i < middle; i++)
	{
		left[i] = unsortedWords[i];
	}

	for(int j = middle; j < lengthArray; j++)
	{
		right[j - middle] = unsortedWords[j];
	}

	// Delete, because we don't need it anymore
	delete [] unsortedWords;

	left = mergeSort(left, middle);
	right = mergeSort(right, lengthArray - middle);

	return merge(left, right, leftLength, rightLength);
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
		staticCompCounter++;
		staticSwapCounter++;
	}

	while(l < leftLength)
	{
		resultList[l+r] = left[l];
		l++;
		staticSwapCounter++;
	}
	while(r < rightLength)
	{
		resultList[l+r] = right[r];
		r++;
		staticSwapCounter++;
	}

	return resultList;
}

std::string * Algorithms::quickSort(std::string * unsortedWords, int startIndex, int endIndex)
{

	if(startIndex < endIndex)
	{
		pivot = partition(unsortedWords, startIndex, endIndex);
		quickSort(unsortedWords, startIndex, pivot - 1);
		quickSort(unsortedWords, pivot + 1, endIndex);
	}
	return unsortedWords;
}

int Algorithms::partition(std::string * unsortedWords, int startIndex, int endIndex)
{
	// Halfway between startIndex and endIndex assuming binary splitting
	int pivotIndex = (endIndex+startIndex)/2;
	// Remember the string at the pivot we chose
	std::string pivotValue = unsortedWords[pivotIndex];

	// Swap the pivot with the end string
	swapStrings(unsortedWords, pivotIndex, endIndex);
	staticSwapCounter++;

	int storeIndex = startIndex;
	for(int i = startIndex; i < endIndex - 1; i++)
	{
		if(unsortedWords[i] < pivotValue)
		{
			swapStrings(unsortedWords, i, storeIndex);
			storeIndex++;
			staticSwapCounter++;
		}
		staticCompCounter++;
	}
	swapStrings(unsortedWords, storeIndex, endIndex);
	staticSwapCounter++;
	return storeIndex;
}








