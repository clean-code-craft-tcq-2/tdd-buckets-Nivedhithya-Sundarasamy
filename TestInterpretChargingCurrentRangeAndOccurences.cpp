#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test-framework/catch.hpp"
#include "InterpretChargingCurrentRangeAndOccurences.h"

TEST_CASE("Checks the charging current range and its occurences") {
	int chargingCurrentSamples[] = {4,5,8,9,10};
	char* rangeAndOccurences[2];
	size_t numberOfSamples;
	numberOfSamples = sizeof(chargingCurrentSamples) / sizeof(chargingCurrentSamples[0]);
	interpretChargingCurrentRangeAndOccurences(chargingCurrentSamples, rangeAndOccurences, numberOfSamples);
	REQUIRE(strcmp(rangeAndOccurences[0], "4-5, 2") == 0);
	REQUIRE(strcmp(rangeAndOccurences[1], "8-10, 3") == 0);
}

TEST_CASE("Check the size of given charging current samples") {
	int chargingCurrentSamples[] = {4,5};
	size_t expectedSize = 2;
	size_t numberOfSamples = findNumberOfSamples(chargingCurrentSamples);
	REQUIRE(numberOfSamples == expectedSize);
}

TEST_CASE("Checks the minimum value in a given charging current range") {
	int chargingCurrentSamples[] = {4,5};
	int expectedMinValue = 4;
	size_t numberOfSamples = findNumberOfSamples(chargingCurrentSamples);
	int minValueForChargingCurrentRange = findMinValueOfChargingCurrentRange(chargingCurrentSamples, numberOfSamples);
	REQUIRE(minValueForChargingCurrentRange == expectedMinValue);
}

TEST_CASE("Checks the maximum value in a given charging current range") {
	int chargingCurrentSamples[] = {4,5};
	int expectedMaxValue = 5;
	size_t numberOfSamples = findNumberOfSamples(chargingCurrentSamples);
	int maxValueForChargingCurrentRange = findMaxValueOfChargingCurrentRange(chargingCurrentSamples, numberOfSamples);
	REQUIRE(maxValueForChargingCurrentRange == expectedMaxValue);
}
