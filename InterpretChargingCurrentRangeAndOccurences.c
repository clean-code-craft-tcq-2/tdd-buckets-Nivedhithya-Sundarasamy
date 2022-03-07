#include <stdio.h>
#include <stdlib.h>
#include "InterpretChargingCurrentRangeAndOccurences.h"

char* interpretChargingCurrentRangeAndOccurences(int* chargingCurrentSamples){
	char *chargingCurrentRangeAndOccurences = (char*)malloc(100);
	int maxValue, minValue;
	size_t numberOfSamples, numberOfOccurences;

	numberOfSamples = findNumberOfSamples(chargingCurrentSamples);
	numberOfOccurences = numberOfSamples; // Since input is conidered as a single range
	maxValue = chargingCurrentSamples[0]; // Initializing to first element
	for (size_t i=0; i<numberOfSamples; i++) {
		if(chargingCurrentSamples[i] > maxValue){
			maxValue = chargingCurrentSamples[i];
		}
	}
	minValue = findMinValueOfChargingCurrentRange(chargingCurrentSamples, numberOfSamples);
	sprintf(chargingCurrentRangeAndOccurences, "%d-%d, %lu", minValue, maxValue, numberOfOccurences);
	printf("%s\n", chargingCurrentRangeAndOccurences);
	return chargingCurrentRangeAndOccurences;
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
