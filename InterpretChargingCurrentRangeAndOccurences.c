#include <stdio.h>
#include <stdlib.h>
#include "InterpretChargingCurrentRangeAndOccurences.h"

char* interpretChargingCurrentRangeAndOccurences(int chargingCurrentSamples[]){
	printf("Charging current sample first element: %d \n", chargingCurrentSamples[0]);
	int minValue=0, maxValue=0, numberOfOccurences=0;
	char *chargingCurrentRangeAndOccurences = (char*)malloc(100);

	sprintf(chargingCurrentRangeAndOccurences, "%d-%d, %d", minValue, maxValue, numberOfOccurences);
	return chargingCurrentRangeAndOccurences;
};
