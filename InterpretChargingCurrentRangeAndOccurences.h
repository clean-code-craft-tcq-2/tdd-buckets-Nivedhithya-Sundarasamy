struct RangeAndOccurences {
	int minValue;
	int maxValue;
	size_t Occurences;
};
void interpretChargingCurrentRangeAndOccurences(int chargingCurrentSamples[], char* chargingCurrentRangeAndOccurences[], size_t numberOfSamples);
size_t findNumberOfSamples(int* chargingCurrentSamples);
int findMinValueOfChargingCurrentRange(int* chargingCurrentSamples, size_t numberOfSamples);
int findMaxValueOfChargingCurrentRange(int* chargingCurrentSamples, size_t numberOfSamples);
void checkForAvailableRanges(int* sortedChargingCurrentSamples, int *numberOfRanges, size_t numberOfSamples,
		int *subsetOfChargingCurrentSamples[], RangeAndOccurences rangeAndOccurences[]);
int* sortSamples(int* chargingCurrentSamples, size_t numberOfSamples);
void swap(int* xp, int* yp);
int* checkForConsecutiveSamples(int* chargingCurrentSamples, size_t numberOfSamples);
int* checkForValidityOfSamples(int* chargingCurrentSamples,  size_t numberOfSamples);

