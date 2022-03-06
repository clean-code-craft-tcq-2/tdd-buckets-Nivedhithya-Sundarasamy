#include <stdio.h>
#include <stdlib.h>
#include "InterpretChargingCurrentRangeAndOccurences.h"

char* interpretChargingCurrentRangeAndOccurences(int* chargingCurrentSamples){
	char *chargingCurrentRangeAndOccurences = (char*)malloc(100);
	int minValue, maxValue;
	size_t numberOfOccurences;
	numberOfOccurences = sizeof(chargingCurrentSamples) / sizeof(chargingCurrentSamples[0]);
	minValue = 100; // Initalizing to a high value
	maxValue = chargingCurrentSamples[0];
	
	for (int i=0; i<2; i++) {
		if(chargingCurrentSamples[i] > maxValue){
			maxValue = chargingCurrentSamples[i];
		}
		if(chargingCurrentSamples[i] < minValue){
			minValue = chargingCurrentSamples[i];
		}
	}
	
	sprintf(chargingCurrentRangeAndOccurences, "%d-%d, %lu", minValue, maxValue, numberOfOccurences);
	printf("%s\n", chargingCurrentRangeAndOccurences);
	return chargingCurrentRangeAndOccurences;
};
