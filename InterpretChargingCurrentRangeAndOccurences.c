#include <stdio.h>
#include <stdlib.h>
#include "InterpretChargingCurrentRangeAndOccurences.h"


void allocateCharJaggedArray(char* p[], int arraySize){
	for (int i=0; i < arraySize; i++) {
		p[i] = (char*)malloc(10);
	}
}

void allocateIntJaggedArray(int* p[], int arraySize) {
	for (int i=0; i < arraySize; i++) {
		p[i] = (int*)malloc(10);
	}
}

void printOutputInCSV(char* chargingCurrentRangeAndOccurences[], int numberOfRanges) {
	printf("Range, Readings \n");
	for (int i=0; i<numberOfRanges; i++) {
		printf("%s\n", chargingCurrentRangeAndOccurences[i]);
	}
}

void freeMemoryForCharJaggedArray(char* pChar[], int arraySize) {
	for (int i=0; i < arraySize; i++) {
		free(pChar[i]);
	}
}

void freeMemoryForIntJaggedArray(int* pInt[], int arraySize) {
	for (int i=0; i < arraySize; i++) {
		free(pInt[i]);
	}
}

void formatOutputInCSV(RangeAndOccurences rangeAndOccurences[], int numberOfRanges, int* availableRanges[], char* chargingCurrentRangeAndOccurences[]){
	allocateCharJaggedArray(chargingCurrentRangeAndOccurences, numberOfRanges);
	for (int i=0; i < numberOfRanges; i++) {	
		rangeAndOccurences[i].minValue = availableRanges[i][0]; //As arrays are sorted, first index is the min value
		int maxValueIndex = (rangeAndOccurences[i].Occurences) -1; // As index starts with 0, max vale index is one less than number of occurences
		rangeAndOccurences[i].maxValue = availableRanges[i][maxValueIndex];
		sprintf(chargingCurrentRangeAndOccurences[i], "%d-%d, %d", rangeAndOccurences[i].minValue, rangeAndOccurences[i].maxValue, rangeAndOccurences[i].Occurences);
	}
	printOutputInCSV(chargingCurrentRangeAndOccurences, numberOfRanges);
}

void interpretChargingCurrentRangeAndOccurences(int chargingCurrentSamples[], char* chargingCurrentRangeAndOccurences[], int &numberOfRanges, size_t numberOfSamples){
	int* availableRanges[NUMBER_OF_RANGES_SUPPORTED];
	int validityStatus;
	RangeAndOccurences rangeAndOccurences[NUMBER_OF_RANGES_SUPPORTED];
	int* sortedChargingCurrentSamples;

	allocateIntJaggedArray(availableRanges, NUMBER_OF_RANGES_SUPPORTED);
	validityStatus = checkForValidityOfSamples(chargingCurrentSamples, numberOfSamples);
	if(validityStatus)
		sortedChargingCurrentSamples = checkForConsecutiveSamples(chargingCurrentSamples, numberOfSamples);
	else{
		sprintf(chargingCurrentRangeAndOccurences[0], "Invalid Samples");
		numberOfRanges = 1; //Number of range defaults to 1 for samples with invalied element
		printOutputInCSV(chargingCurrentRangeAndOccurences, 1);
		return;
	}
	checkForAvailableRanges(sortedChargingCurrentSamples, &numberOfRanges, numberOfSamples, availableRanges, rangeAndOccurences);
	formatOutputInCSV(rangeAndOccurences, numberOfRanges, availableRanges, chargingCurrentRangeAndOccurences);
	freeMemoryForIntJaggedArray(availableRanges, NUMBER_OF_RANGES_SUPPORTED);
}

bool checkValidityStatus(int validElementCount, int numberOfSamples) {
	return (validElementCount == numberOfSamples) ? 1 : 0;
}

int checkIfElementIsValid(int* chargingCurrentSamples, int index, int currentValidElementCount) {
	int validElementCount=currentValidElementCount;
	if((chargingCurrentSamples[index] != '\0') && (chargingCurrentSamples[index] > 0))
		validElementCount++;
	return validElementCount;
}
	
bool checkForValidityOfSamples(int* chargingCurrentSamples,  size_t numberOfSamples){
	int validElementCount = 0;
	for (size_t i=0; i<numberOfSamples; i++) {
		validElementCount = checkIfElementIsValid(chargingCurrentSamples, i, validElementCount);
	}
	return checkValidityStatus(validElementCount, numberOfSamples);
}

int* checkIfSortRequired(int* chargingCurrentSamples, size_t consecutiveElementCount, size_t numberOfSamples) {
	return (consecutiveElementCount == (numberOfSamples-1)) ? chargingCurrentSamples: sortSamples(chargingCurrentSamples, numberOfSamples);
}

int checkIfElementsAreCosnecutive(int gapBetweenConsecutiveElements) {
	static size_t consecutiveElementCount=0;
	if((gapBetweenConsecutiveElements == 1) || (gapBetweenConsecutiveElements == 0))
		consecutiveElementCount++;
	return consecutiveElementCount;
}	

int* checkForConsecutiveSamples(int* chargingCurrentSamples, size_t numberOfSamples){
	int gapBetweenConsecutiveElements;
	size_t consecutiveElementCount;
	for (size_t i=0; i<numberOfSamples; i++) {
		gapBetweenConsecutiveElements = chargingCurrentSamples[i+1] - chargingCurrentSamples[i];
		consecutiveElementCount = checkIfElementsAreCosnecutive(gapBetweenConsecutiveElements);
	}
	return checkIfSortRequired(chargingCurrentSamples, consecutiveElementCount, numberOfSamples);

}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int* sortSamples(int* chargingCurrentSamples, size_t numberOfSamples){
	qsort(chargingCurrentSamples, numberOfSamples, sizeof(int), cmpfunc);
	return chargingCurrentSamples;	
}

int getGapBetweenConsecutiveElements(int* sortedChargingCurrentSamples,  size_t numberOfSamples, size_t index) {
	//For the last element, there won't be next consecutive element so gap is considered as 0.
	return (index == (numberOfSamples - 1)) ? 0 : (sortedChargingCurrentSamples[index+1] - sortedChargingCurrentSamples[index]);
}

void splitSamplesBasedOnRange(int* sortedChargingCurrentSamples, size_t index, int *subsetOfChargingCurrentSamples[],
			RangeAndOccurences rangeAndOccurences[], int* rowIndexValue, int* columnIndexValue, int currentRowIndex, int currentColumnIndex, int gapBetweenConsecutiveElements) {
		int rowIndex = currentRowIndex;
		int columnIndex = currentColumnIndex;
		if((gapBetweenConsecutiveElements == 1) || (gapBetweenConsecutiveElements == 0)){
			subsetOfChargingCurrentSamples[rowIndex][columnIndex] = sortedChargingCurrentSamples[index];
			columnIndex++;
		} else {
			subsetOfChargingCurrentSamples[rowIndex][columnIndex] = sortedChargingCurrentSamples[index];
			rangeAndOccurences[rowIndex].Occurences = columnIndex+1;
			rowIndex++;
			columnIndex=0;
		}
	*rowIndexValue = rowIndex;
	*columnIndexValue = columnIndex;
}
	
void checkForAvailableRanges(int* sortedChargingCurrentSamples, int *numberOfRanges, size_t numberOfSamples,
		int *subsetOfChargingCurrentSamples[], RangeAndOccurences rangeAndOccurences[]){
	
	int gapBetweenConsecutiveElements, rowIndex = 0, columnIndex = 0;
	for (size_t i = 0; i < numberOfSamples; i++) {
		gapBetweenConsecutiveElements = getGapBetweenConsecutiveElements(sortedChargingCurrentSamples, numberOfSamples, i);
		splitSamplesBasedOnRange(sortedChargingCurrentSamples, i, subsetOfChargingCurrentSamples, rangeAndOccurences, &rowIndex, &columnIndex,
			rowIndex, columnIndex, gapBetweenConsecutiveElements);
	}
	rangeAndOccurences[rowIndex].Occurences = columnIndex;
	*numberOfRanges = rowIndex+1;
}
