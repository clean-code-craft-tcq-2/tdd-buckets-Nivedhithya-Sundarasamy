#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test-framework/catch.hpp"
#include "InterpretChargingCurrentRangeAndOccurences.h"
#include "InterpretChargingCurrentValues.h"
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

TEST_CASE("Checks for the current values for given 'n' bit resolution array and measurement range") {
	
	// Input Samples
	int ADC_ConverterValues_12bit_0[] = {100, 3096, 2056, 4078};
	int ADC_ConverterValues_12bit_1[] = {375, 1895, 4093};
	int *ADC_ConverterValues[] = {ADC_ConverterValues_12bit_0, ADC_ConverterValues_12bit_1};
 
	// Size of input samples
	size_t numberOfSamples_12bit_0 = sizeof(ADC_ConverterValues_12bit_0) / sizeof(ADC_ConverterValues_12bit_0[0]);
	size_t numberOfSamples_12bit_1 = sizeof(ADC_ConverterValues_12bit_1) / sizeof(ADC_ConverterValues_12bit_1[0]);
	size_t numberOfSamples[] = {numberOfSamples_12bit_0, numberOfSamples_12bit_1};

	// Expected Output
	int expectedChargingCurrentValues_0[] = {0, 8, 5, 10};
	int expectedChargingCurrentValues_1[] = {1, 5, 10};
	int* expectedChargingCurrentValues[] = {expectedChargingCurrentValues_0, expectedChargingCurrentValues_1};
	
	// ADC Resolution
	int ADC_Resolution = 12;
	
	// Range of Measurement
	signed int minCurrentValue = 0;
	signed int maxCurrentValue = 10;
	
	
	for(size_t i=0; i<2; i++) {
		int chargingCurrentValues[numberOfSamples[i]];
		interpretChargingCurrentValue(ADC_ConverterValues[i], numberOfSamples[i], ADC_Resolution, minCurrentValue, maxCurrentValue, chargingCurrentValues);
		for(size_t j=0; j<numberOfSamples[i]; j++) {
			REQUIRE(chargingCurrentValues[j] == expectedChargingCurrentValues[i][j]);
		}
	}
}


TEST_CASE("Checks for the raw current value for given integer of 'n' bit resolution and measurement range") {
	float rawCurrentValue, scalingFactor, conversionFactor;
	int totalCurrentRange, maxIntegerValue;
	signed int minCurrentValue = 0;
	signed int maxCurrentValue = 10;
	
	totalCurrentRange = calculateTotalCurrentRange(maxCurrentValue, minCurrentValue);
	scalingFactor = calculateMultiplyingFactor(totalCurrentRange, maxCurrentValue);
	
	SECTION("This section runs for each inputValue given in the table") {
		int ADC_Resolution = 12;
        	int inputValue;
       		float expectedRawCurrentValue;
        	std::tie(inputValue, expectedRawCurrentValue) =
            	GENERATE( table<int, float>(
                	{ 
	                  std::make_tuple( 267, 0.65217 ),
        	          std::make_tuple( 3456, 8.44162 ),
                	  std::make_tuple( 1287, 3.14362 ) } ) );
		maxIntegerValue = calculateMaxIntegerValue(ADC_Resolution);
		conversionFactor = calculateMultiplyingFactor(inputValue, maxIntegerValue);
		rawCurrentValue = convertInputIntegerToCurrentValue(conversionFactor, scalingFactor, minCurrentValue, maxCurrentValue);
		REQUIRE(rawCurrentValue == Approx(expectedRawCurrentValue));
	}
}

	
TEST_CASE("Checks for the rounded off current value for given current value") {
	
	SECTION("This section runs for each inputValue given in the table") {
        float inputValue;
        int expectedRoundedOffCurrentValue, roundedOffCurrentValue;
        std::tie(inputValue, expectedRoundedOffCurrentValue) =
            GENERATE( table<float, int>(
                { 
                  std::make_tuple( 0.65217, 1 ),
                  std::make_tuple( 8.44162, 8 ),
                  std::make_tuple( 3.14362, 3 ) } ) );
	roundedOffCurrentValue = roundOffCurrentValue(inputValue);
	REQUIRE(roundedOffCurrentValue == expectedRoundedOffCurrentValue);
	}
}

TEST_CASE("Checks for the absolute value of the given charging current") {
	
	SECTION("This section runs for each inputValue given in the table") {
        int inputValue;
        int expectedAbsoluteCurrentValue, absoluteCurrentValue;
        std::tie(inputValue, expectedAbsoluteCurrentValue) =
            GENERATE( table<int, int>(
                { 
                  std::make_tuple( -1, 1 ),
                  std::make_tuple( -8, 8 ),
                  std::make_tuple( 3, 3 ) } ) );
	absoluteCurrentValue = checkIfValueIsAbsoluteAndConvert(&inputValue);
	REQUIRE(absoluteCurrentValue == expectedAbsoluteCurrentValue);
	}
}


TEST_CASE("Checks for the max supported integer value for given ADC resolution") {
	
	SECTION("This section runs for each inputValue given in the table") {
        int inputValue;
        int expectedMaxIntegerValue, maxIntegerValue;
        std::tie(inputValue, expectedMaxIntegerValue) =
            GENERATE( table<int, int>(
                { 
                  std::make_tuple( 12, 4094 ),
                  std::make_tuple( 10, 1022) } ) );
	maxIntegerValue = calculateMaxIntegerValue(inputValue);
	REQUIRE(maxIntegerValue == expectedMaxIntegerValue);
	}
}

TEST_CASE("Checks for the total current range for current value interpretation") {

        int totalCurrentRange;
	int minCurrentValue[] = {0, -10};
	int maxCurrentValue[] = {10, 10};
	int expectedTotalCurrentRange[] = {10, 20};

	size_t numberOfSamples = sizeof(minCurrentValue)/sizeof(minCurrentValue[0]);
	for(size_t i=0; i<numberOfSamples; i++) {
		totalCurrentRange = calculateTotalCurrentRange(maxCurrentValue[i], minCurrentValue[i]);
		REQUIRE(totalCurrentRange == expectedTotalCurrentRange[i]);
	}
}

TEST_CASE("Check for ignoring of the error reading in given input array") {

	int ADC_Values[] = {2387, 4095, 4094};
	int expectedValidADC_Values[] = {2387, 4094};
	size_t numberOfValidSamples;
	int ADC_Resolution = 12;
	
	size_t numberOfSamples = sizeof(ADC_Values)/sizeof(ADC_Values[0]);
	int ValidADC_Values[numberOfSamples];
	getValidInputValues(ADC_Values, ADC_Resolution, numberOfSamples, &numberOfValidSamples, ValidADC_Values);
	for(size_t i=0; i<numberOfValidSamples; i++){
		REQUIRE(ValidADC_Values[i] == expectedValidADC_Values[i]);
	}
}

TEST_CASE("Ignores the error value and checks for the current values for given 'n' bit resolution array and measurement range") {

// Input Samples
         int ADC_ConverterValues_12bit_0[] = {100, 3096, 2056, 4095};
         int ADC_ConverterValues_12bit_1[] = {375, 4095, 4093};
         int *ADC_ConverterValues[] = {ADC_ConverterValues_12bit_0, ADC_ConverterValues_12bit_1};

         // Size of input samples
         size_t numberOfSamples_12bit_0 = sizeof(ADC_ConverterValues_12bit_0) / sizeof(ADC_ConverterValues_12bit_0[0]);
         size_t numberOfSamples_12bit_1 = sizeof(ADC_ConverterValues_12bit_1) / sizeof(ADC_ConverterValues_12bit_1[0]);
         size_t numberOfSamples[] = {numberOfSamples_12bit_0, numberOfSamples_12bit_1};

        // Expected Output
         int expectedChargingCurrentValues_0[] = {0, 8, 5};
         int expectedChargingCurrentValues_1[] = {1, 10};
         int* expectedChargingCurrentValues[] = {expectedChargingCurrentValues_0, expectedChargingCurrentValues_1};

         // ADC Resolution
         int ADC_Resolution = 12;

         // Range of Measurement
         signed int minCurrentValue = 0;
         signed int maxCurrentValue = 10;

         size_t numberOfValidSamples;

         for(size_t i=0; i<2; i++) {
                 int chargingCurrentValues[numberOfSamples[i]];
                 int ValidADC_Values[numberOfSamples[i]];
                 getValidInputValuesAndInterpretChargingCurrentValue(ADC_ConverterValues[i], ADC_Resolution, numberOfSamples[i],
                         minCurrentValue, maxCurrentValue, &numberOfValidSamples, ValidADC_Values, chargingCurrentValues);
                 for(size_t j=0; j<numberOfValidSamples; j++) {
                         REQUIRE(chargingCurrentValues[j] == expectedChargingCurrentValues[i][j]);
                 }
         }
}

TEST_CASE("Checks for the current range and occurences for given ADC values") {

	 // Input Samples
         int ADC_ConverterValues_12bit_0[] = {700, 400, 3096, 2056, 4095, 3200};

         // Size of input samples
         size_t numberOfSamples_12bit_0 = sizeof(ADC_ConverterValues_12bit_0) / sizeof(ADC_ConverterValues_12bit_0[0]);

        // Expected Output
	 const char *expectedOutput[4] = {"1-2, 2", "5-5, 1", "8-8, 2"};

         // ADC Resolution
         int ADC_Resolution = 12;

         // Range of Measurement
         signed int minCurrentValue = 0;
         signed int maxCurrentValue = 10;

	char* rangeAndOccurences[3];
	int numberOfRanges=0;
	interpretChargingCurrentRangeAndOccurencesFromADC(ADC_ConverterValues_12bit_0, ADC_Resolution, numberOfSamples_12bit_0,
	minCurrentValue, maxCurrentValue, rangeAndOccurences, numberOfRanges);
	for(int j=0; j < numberOfRanges; j++) {
		REQUIRE(strcmp(rangeAndOccurences[j], expectedOutput[j]) == 0);
	}
}
