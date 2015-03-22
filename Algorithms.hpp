#include <stdlib.h>
#include <string>

class Algorithms
{
private:
	std::string * 	swapStrings	(std::string * wordArray, int firstIndex, int secondIndex);
	void			printReport	(int algUsed, int percent);

public:
	void insertionSort	( std::string * unsortedWords, int LengthArray);
	void selectionSort	( std::string * unsortedWords, int lengthArray);
	void mergeSort		( std::string * unsortedWords, int lengthArray);
	void quickSort		( std::string * unsortedWords, int lengthArray);
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


void Algorithms::insertionSort ( std::string * unsortedWords, int lengthArray)
{

	comparisonCounter = 0;
	swapCounter = 0;

	int j;
	for(int i = 1; i < lengthArray - 1; i++)
	{
		j = i;
		while( j > 0 && unsortedWords[ j - 1 ] > unsortedWords[j])
		{
			comparisonCounter+=2;
			swapStrings(unsortedWords, j, j-1);
			swapCounter++;
			j--;
		}
	}
	printReport(0, 100);
}



void Algorithms::selectionSort(std::string * unsortedWords, int lengthArray)
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
				comparisonCounter++;
				jMin = j;
			}
		}
		if(jMin != j)
		{
			comparisonCounter++;
			swapStrings(unsortedWords, i, jMin);
			swapCounter++;
		}
	}
	printReport(1, 100);

}















