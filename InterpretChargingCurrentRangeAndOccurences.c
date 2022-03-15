#include <stdio.h>
#include <stdlib.h>
#include "InterpretChargingCurrentRangeAndOccurences.h"

// Based on the supported ranges array size will be allocated 
#define NUMBER_OF_RANGES_SUPPORTED 10

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

void interpretChargingCurrentRangeAndOccurences(int chargingCurrentSamples[], char* chargingCurrentRangeAndOccurences[], size_t numberOfSamples){
	int* availableRanges[NUMBER_OF_RANGES_SUPPORTED];
	int numberOfRanges, validityStatus;
	RangeAndOccurences rangeAndOccurences[NUMBER_OF_RANGES_SUPPORTED];
	int* sortedChargingCurrentSamples;
	

	allocateIntJaggedArray(availableRanges, NUMBER_OF_RANGES_SUPPORTED);
	validityStatus = checkForValidityOfSamples(chargingCurrentSamples, numberOfSamples);
	if(validityStatus)
		sortedChargingCurrentSamples = checkForConsecutiveSamples(chargingCurrentSamples, numberOfSamples);
	else{
		printf("Charging current sample is having invalid element \n");
		return;
	}
	checkForAvailableRanges(sortedChargingCurrentSamples, &numberOfRanges, numberOfSamples, availableRanges, rangeAndOccurences);
	formatOutputInCSV(rangeAndOccurences, numberOfRanges, availableRanges, chargingCurrentRangeAndOccurences);
}

bool checkValidityStatus(int validElementCount, int numberOfSamples) {
	return (validElementCount == numberOfSamples) ? 1 : 0;
}

int checkIfElementIsValid(int* chargingCurrentSamples, int index) {
	static int validElementCount=0;
	if((chargingCurrentSamples[index] != '\0') && (chargingCurrentSamples[index] > 0))
		validElementCount++;
	return validElementCount;
}
	
bool checkForValidityOfSamples(int* chargingCurrentSamples,  size_t numberOfSamples){
	int validElementCount=0;
	
	for (size_t i=0; i<numberOfSamples; i++) {
		validElementCount = checkIfElementIsValid(chargingCurrentSamples, i);
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
	size_t i, consecutiveElementCount;
	for (i=0; i<numberOfSamples; i++) {
		gapBetweenConsecutiveElements = chargingCurrentSamples[i+1] - chargingCurrentSamples[i];
		consecutiveElementCount = checkIfElementsAreCosnecutive(gapBetweenConsecutiveElements);
	}
	return checkIfSortRequired(chargingCurrentSamples, consecutiveElementCount, numberOfSamples);

}

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void checkIfValuesIsMin(int* chargingCurrentSamples, int* minValueIndex, size_t index){
	if (chargingCurrentSamples[index] < chargingCurrentSamples[*minValueIndex]){
		*minValueIndex = index;
	}
}
	

int* sortSamples(int* chargingCurrentSamples, size_t numberOfSamples){
	int minValueIndex;

	for (size_t i = 0; i < numberOfSamples - 1; i++) {
        	minValueIndex = i;
	        for (size_t j = i + 1; j < numberOfSamples; j++){
			checkIfValuesIsMin(chargingCurrentSamples, &minValueIndex, j);
    		}
		swap(&chargingCurrentSamples[minValueIndex], &chargingCurrentSamples[i]);
	}
	return chargingCurrentSamples;	
}

int getGapBetweenConsecutiveElements(int* sortedChargingCurrentSamples,  size_t numberOfSamples, size_t index) {
	//For the last element, there won't be next consecutive element so gap is considered as 0.
	return (index == (numberOfSamples - 1)) ? 0 : (sortedChargingCurrentSamples[index+1] - sortedChargingCurrentSamples[index]);
}

void splitSamplesBasedOnRange(int* sortedChargingCurrentSamples, size_t index, int *subsetOfChargingCurrentSamples[],
			RangeAndOccurences rangeAndOccurences[], int* rowIndexValue, int* columnIndexValue, int gapBetweenConsecutiveElements) {
		static int rowIndex = 0, columnIndex = 0;
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
		splitSamplesBasedOnRange(sortedChargingCurrentSamples, i, subsetOfChargingCurrentSamples, rangeAndOccurences, &rowIndex, &columnIndex, gapBetweenConsecutiveElements);
	}
	rangeAndOccurences[rowIndex].Occurences = columnIndex;
	*numberOfRanges = rowIndex+1;
}
