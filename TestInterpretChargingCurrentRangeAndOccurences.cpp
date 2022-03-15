#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test-framework/catch.hpp"
#include "InterpretChargingCurrentRangeAndOccurences.h"

TEST_CASE("Checks the charging current range and its occurences") {
	int chargingCurrentSamples[] = {4,5,8,17,10,15,9};
	char* rangeAndOccurences[2];
	size_t numberOfSamples;
	numberOfSamples = sizeof(chargingCurrentSamples) / sizeof(chargingCurrentSamples[0]);
	interpretChargingCurrentRangeAndOccurences(chargingCurrentSamples, rangeAndOccurences, numberOfSamples);
	REQUIRE(strcmp(rangeAndOccurences[0], "4-5, 2") == 0);
	REQUIRE(strcmp(rangeAndOccurences[1], "8-10, 3") == 0);
	REQUIRE(strcmp(rangeAndOccurences[2], "15-15, 1") == 0);
	REQUIRE(strcmp(rangeAndOccurences[3], "17-17, 1") == 0);
}


