struct RangeAndOccurences {
	int minValue;
	int maxValue;
	int Occurences;
};
void allocateCharJaggedArray(char* p[], int arraySize);
void allocateIntJaggedArray(int* p[], int arraySize);
void printOutputInCSV(char* chargingCurrentRangeAndOccurences[], int numberOfRanges);
void formatOutputInCSV(RangeAndOccurences rangeAndOccurences[], int numberOfRanges,
	int* availableRanges[], char* chargingCurrentRangeAndOccurences[]);
void interpretChargingCurrentRangeAndOccurences(int chargingCurrentSamples[],
	char* chargingCurrentRangeAndOccurences[], int &numberOfRanges, size_t numberOfSamples);
bool checkValidityStatus(int validElementCount, int numberOfSamples);
int checkIfElementIsValid(int* chargingCurrentSamples, int index, int currentValidElementCount);
bool checkForValidityOfSamples(int* chargingCurrentSamples,  size_t numberOfSamples);
int* checkIfSortRequired(int* chargingCurrentSamples, size_t index, size_t numberOfSamples);
int* checkForConsecutiveSamples(int* chargingCurrentSamples, size_t numberOfSamples);
void swap(int* xp, int* yp);
void checkIfValuesIsMin(int* chargingCurrentSamples, int* minValueIndex, size_t index);
int* sortSamples(int* chargingCurrentSamples, size_t numberOfSamples);
int getGapBetweenConsecutiveElements(int* sortedChargingCurrentSamples,  size_t numberOfSamples, size_t index);
void checkForAvailableRanges(int* sortedChargingCurrentSamples, int *numberOfRanges,
	size_t numberOfSamples, int *subsetOfChargingCurrentSamples[], RangeAndOccurences rangeAndOccurences[]);

