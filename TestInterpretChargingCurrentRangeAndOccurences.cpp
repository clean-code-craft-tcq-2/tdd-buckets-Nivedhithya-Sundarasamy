#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test-framework/catch.hpp"

TEST_CASE("Checks the charging current range and its occurences") {
	int chargingCurrentSamples[] = {4,5};
	const char* expectedRangeAndOccurences = "4-5, 2";
	char* rangeAndOccurences;
	rangeAndOccurences = interpretChargingCurrentRangeAndOccurences(chargingCurrentSamples);
	REQUIRE(strcmp(rangeAndOccurences, expectedRangeAndOccurences) == 0);
}
