#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test-framework/catch.hpp"
#include "InterpretChargingCurrentRangeAndOccurences.h"
#include <string>

TEST_CASE("Checks the charging current range and its occurences for different input samples") {

	// Input Samples
	int chargingCurrentSamples_0[] = {8,9,10,11};
	int chargingCurrentSamples_1[] = {4,5,8,9,13};
	int chargingCurrentSamples_2[] = {3,4,5,9,3,3,5};
	int chargingCurrentSamples_3[] = {3,4,-5,'\0',-3,5,3}; 

	int *chargingCurrentSamples[] = { chargingCurrentSamples_0, chargingCurrentSamples_1, chargingCurrentSamples_2, chargingCurrentSamples_3};

	// Size of Input Samples
	size_t numberOfSamples_0 = sizeof(chargingCurrentSamples_0) / sizeof(chargingCurrentSamples_0[0]);
	size_t numberOfSamples_1 = sizeof(chargingCurrentSamples_1) / sizeof(chargingCurrentSamples_1[0]);
	size_t numberOfSamples_2 = sizeof(chargingCurrentSamples_2) / sizeof(chargingCurrentSamples_2[0]);
	size_t numberOfSamples_3 = sizeof(chargingCurrentSamples_3) / sizeof(chargingCurrentSamples_3[0]);

	// Expected Output
	const char *expectedOutput[5][4] = { {"8-11, 4"}, {"4-5, 2", "8-9, 2", "13-13, 1"}, {"3-5, 6", "9-9, 1"}, {"Invalid Samples"}};
	
	char* rangeAndOccurences[3];
	int numberOfRanges;
	size_t numberOfSamples[] = { numberOfSamples_0, numberOfSamples_1, numberOfSamples_2, numberOfSamples_3};
	for(size_t i=0; i<4; i++) {
		interpretChargingCurrentRangeAndOccurences(chargingCurrentSamples[i], rangeAndOccurences, numberOfRanges, numberOfSamples[i]);
		for(int j=0; j < numberOfRanges; j++) {
			REQUIRE(strcmp(rangeAndOccurences[j], expectedOutput[i][j]) == 0);
		}
	}
	freeMemoryForCharJaggedArray(rangeAndOccurences, numberOfRanges);
}


