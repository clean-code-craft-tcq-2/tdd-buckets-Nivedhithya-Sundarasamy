#include <stdio.h>
#include <stdlib.h>
#include "InterpretChargingCurrentRangeAndOccurences.h"

void interpretChargingCurrentRangeAndOccurences(int chargingCurrentSamples[], char* chargingCurrentRangeAndOccurences[], size_t numberOfSamples){
	int maxValue, minValue;
	size_t numberOfOccurences;

	numberOfSamples = findNumberOfSamples(chargingCurrentSamples);
	minValue = findMinValueOfChargingCurrentRange(chargingCurrentSamples, numberOfSamples);
	maxValue = findMaxValueOfChargingCurrentRange(chargingCurrentSamples, numberOfSamples);
	numberOfOccurences = numberOfSamples; // Since input is conidered as a single range
	sprintf(chargingCurrentRangeAndOccurences[0], "%d-%d, %lu", minValue, maxValue, numberOfOccurences);
	printf("Range, Readings \n");
	printf("%s\n", chargingCurrentRangeAndOccurences);
}

size_t findNumberOfSamples(int* chargingCurrentSamples) {
	size_t numberOfSamples;
	numberOfSamples = sizeof(chargingCurrentSamples) / sizeof(chargingCurrentSamples[0]);
	return numberOfSamples;
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
