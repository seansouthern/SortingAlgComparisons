#include <iomanip>


void printArrayLine(int * intArray, int lengthArray)
{
	for(int i = 0; i <lengthArray; i++)
	{
		std::cout << std::setw(15)<< intArray[i];
	}
	std::cout << std::endl;
}


void printArray(std::string * wordArray, int lengthArray)
{
	for(int i = 0; i < lengthArray; i++)
	{

		std::cout << i << " : " <<  wordArray[i] << std::endl;
	}
}

std::string * copyArray(std::string * wordArray, int lengthArray)
{
	// We allocate the copied array on heap because we may not have enough room
	//  in this stack frame.
	std::string * copyOfArray = new std::string[lengthArray];
	//Straight copy from original array to the next
	for(int x = 0; x < lengthArray; x++)
	{
		copyOfArray[x] = wordArray[x];
	}
	return copyOfArray;
}

std::string * generate75pcSortedLists(std::string * unsortedArray, int lengthArray)
{
	Algorithms algs;
	std::string * semisorted75pcWords = copyArray(unsortedArray, lengthArray);
	semisorted75pcWords = algs.insertionSort(unsortedArray, (lengthArray * .75));
	return semisorted75pcWords;
}

std::string * generate50pcSortedLists(std::string * unsortedArray, int lengthArray)
{
	Algorithms algs;
	std::string * semisorted50pcWords = copyArray(unsortedArray, lengthArray);
	semisorted50pcWords = algs.insertionSort(unsortedArray, (lengthArray * .50));
	return semisorted50pcWords;
}

std::string * generate25pcSortedLists(std::string * unsortedArray, int lengthArray)
{
	Algorithms algs;
	std::string * semisorted25pcWords = copyArray(unsortedArray, lengthArray);
	semisorted25pcWords = algs.insertionSort(semisorted25pcWords, (lengthArray * .25));
	return semisorted25pcWords;

}

int * runAllAlgs(std::string * inputArray, int lengthArray)
{

	std::string * newArray = copyArray(inputArray, lengthArray);

	Algorithms algs;
	int * counterValues = new int[8];

	algs.staticCompCounter = 0;
	algs.staticSwapCounter = 0;
	algs.comparisonCounter = 0;
	algs.swapCounter = 0;

	algs.insertionSort(newArray, lengthArray);
	counterValues[0] = algs.comparisonCounter;
	counterValues[1] = algs.swapCounter;

	algs.comparisonCounter = 0;
	algs.swapCounter = 0;

	algs.selectionSort(newArray, lengthArray);
	counterValues[2] = algs.comparisonCounter;
	counterValues[3] = algs.swapCounter;

	algs.comparisonCounter = 0;
	algs.swapCounter = 0;


	algs.staticCompCounter = 0;
	algs.staticSwapCounter = 0;

	algs.mergeSort(newArray, lengthArray);
	counterValues[4] = algs.staticCompCounter;
	counterValues[5] = algs.staticSwapCounter;


	algs.staticCompCounter = 0;
	algs.staticSwapCounter = 0;
	//std::cout << algs.staticCompCounter <<std::endl;
	//std::cout << algs.staticSwapCounter <<std::endl;

	algs.staticCompCounter = 0;
	algs.staticSwapCounter = 0;

	algs.quickSort(newArray, 0, (lengthArray -1));
	counterValues[6] = algs.staticCompCounter;
	counterValues[7] = algs.staticSwapCounter;
//	std::cout << algs.staticCompCounter <<std::endl;
	//std::cout << algs.staticSwapCounter <<std::endl;


	delete[] newArray;

	return counterValues;
}
