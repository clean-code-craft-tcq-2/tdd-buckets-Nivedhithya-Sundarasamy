#include <stdio.h>
#include <stdlib.h>
#include "InterpretChargingCurrentRangeAndOccurences.h"

void formatOutput(RangeAndOccurences rangeAndOccurences[], int numberOfRanges, int* availableRanges[], char* chargingCurrentRangeAndOccurences[]){
	chargingCurrentRangeAndOccurences[0] = (char*)malloc(10);
	chargingCurrentRangeAndOccurences[1] = (char*)malloc(10);
	chargingCurrentRangeAndOccurences[2] = (char*)malloc(10);
	chargingCurrentRangeAndOccurences[3] = (char*)malloc(10);
	for (int i=0; i < numberOfRanges; i++) {	
		rangeAndOccurences[i].minValue = availableRanges[i][0];
		int maxValueIndex = (rangeAndOccurences[i].Occurences) -1;
		rangeAndOccurences[i].maxValue = availableRanges[i][maxValueIndex];
		sprintf(chargingCurrentRangeAndOccurences[i], "%d-%d, %d", rangeAndOccurences[i].minValue, rangeAndOccurences[i].maxValue, rangeAndOccurences[i].Occurences);
	}
	printf("Range, Readings \n");
	printf("%s\n", chargingCurrentRangeAndOccurences[0]);
	printf("%s\n", chargingCurrentRangeAndOccurences[1]);
}

void interpretChargingCurrentRangeAndOccurences(int chargingCurrentSamples[], char* chargingCurrentRangeAndOccurences[], size_t numberOfSamples){
	int* availableRanges[5];
	availableRanges[0] = (int*)malloc(10);
	availableRanges[1] = (int*)malloc(10);
	availableRanges[2] = (int*)malloc(10);
	availableRanges[3] = (int*)malloc(10);
	availableRanges[4] = (int*)malloc(10);
	int numberOfRanges;
	RangeAndOccurences rangeAndOccurences[10];
	int* sortedChargingCurrentSamples = checkForValidityOfSamples(chargingCurrentSamples, numberOfSamples);
	checkForAvailableRanges(sortedChargingCurrentSamples, &numberOfRanges, numberOfSamples, availableRanges, rangeAndOccurences);
	formatOutput(rangeAndOccurences, numberOfRanges, availableRanges, chargingCurrentRangeAndOccurences);
}

int* checkForValidityOfSamples(int* chargingCurrentSamples,  size_t numberOfSamples){
	size_t validElementCount=0;
	int* sortedChargingCurrentSamples;

	for (size_t i=0; i<numberOfSamples; i++) {
		if((chargingCurrentSamples[i] != '\0') && (chargingCurrentSamples[i] > 0))
			validElementCount++;
	}
	if(validElementCount == numberOfSamples)
		sortedChargingCurrentSamples = checkForConsecutiveSamples(chargingCurrentSamples, numberOfSamples);
	else
		printf("Charging current sample is having invalid element \n");
	return sortedChargingCurrentSamples;
}

int* checkForConsecutiveSamples(int* chargingCurrentSamples, size_t numberOfSamples){
	int gapBetweenElements;
	size_t i;
	for (i=0; i<numberOfSamples; i++) {
		gapBetweenElements = chargingCurrentSamples[i+1] - chargingCurrentSamples[i];
		if((gapBetweenElements == 1) || (gapBetweenElements == 0))
			continue;
		else
			break;
	}

	if(i == (numberOfSamples-1)){
		return chargingCurrentSamples;
	}
	else{
		return sortSamples(chargingCurrentSamples, numberOfSamples);
	}
}

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int* sortSamples(int* chargingCurrentSamples, size_t numberOfSamples){
	int minValueIndex;

	for (size_t i = 0; i < numberOfSamples - 1; i++) {
        	minValueIndex = i;
	        for (size_t j = i + 1; j < numberOfSamples; j++){
        	    if (chargingCurrentSamples[j] < chargingCurrentSamples[minValueIndex]){
                	minValueIndex = j;
			}
    		}
		swap(&chargingCurrentSamples[minValueIndex], &chargingCurrentSamples[i]);
	}
	return chargingCurrentSamples;	
}

size_t findNumberOfSamples(int* chargingCurrentSamples) {
	size_t numberOfSamples;
	numberOfSamples = sizeof(chargingCurrentSamples) / sizeof(chargingCurrentSamples[0]);
	return numberOfSamples;
}

void checkForAvailableRanges(int* sortedChargingCurrentSamples, int *numberOfRanges, size_t numberOfSamples,
		int *subsetOfChargingCurrentSamples[], RangeAndOccurences rangeAndOccurences[]){
	int gapBetweenElements;
	int j=0,k=0;
	for (size_t i = 0; i < numberOfSamples; i++) {
		if( i == (numberOfSamples - 1))
			gapBetweenElements = 0;
		else
			gapBetweenElements = sortedChargingCurrentSamples[i+1] - sortedChargingCurrentSamples[i];
		if((gapBetweenElements == 1) || (gapBetweenElements == 0)){
			subsetOfChargingCurrentSamples[j][k] = sortedChargingCurrentSamples[i];
			k++;
			continue;
		} else {
			subsetOfChargingCurrentSamples[j][k] = sortedChargingCurrentSamples[i];
			rangeAndOccurences[j].Occurences = k+1;
			j++;
			k=0;
		}
	}
	rangeAndOccurences[j].Occurences = k;
	*numberOfRanges = j+1;
}
			
int findMinValueOfChargingCurrentRange(int* chargingCurrentSamples, size_t numberOfSamples){
	int minValue;
	minValue = chargingCurrentSamples[numberOfSamples-1]; //Initializing to last element  
	for (size_t i=0; i<numberOfSamples; i++) {
		if(chargingCurrentSamples[i] < minValue){
			minValue = chargingCurrentSamples[i];
		}
	}
	return minValue;
}

int findMaxValueOfChargingCurrentRange(int* chargingCurrentSamples, size_t numberOfSamples){
	int maxValue;
	maxValue = chargingCurrentSamples[0]; // Initializing to first element
	for (size_t i=0; i<numberOfSamples; i++) {
		if(chargingCurrentSamples[i] > maxValue){
			maxValue = chargingCurrentSamples[i];
		}
	}
	return maxValue;
}
