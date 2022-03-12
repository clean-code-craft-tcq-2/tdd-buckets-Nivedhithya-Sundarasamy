# Test Driven Ranges

The charging current varies during the process of charging.
We need to capture the range of current measurements -
what range of currents are most often encountered while charging.

> **DO NOT** jump into implementation! Read the example and the starting task below.

## Example

### Input

A set of periodic current samples from a charging session,
as an array of integers. For example:
`3, 3, 5, 4, 10, 11, 12`

### Functionality

The continuous ranges in there are: `3,4,5` and `10,11,12`.

The task is to detect the ranges and
output the number of readings in each range.

In this example,

- the `3-5` range has `4` readings
- the `10-12` range has `3` readings.

### Output

The expected output would be in comma-separated (csv format):

```
Range, Readings
3-5, 4
10-12, 3
```

## Tasks

Establish quality parameters: 

- What is the maximum complexity (CCN) per function? 3 
- How many lines of duplicate code will you tolerate? 3 
- Ensure 100% line and branch coverage at every step. Include the coverage yml in the workflows.

Adapt/adopt/extend the `yml` files from one of your previous workflow folders.

Start Test-driven approach

1. Write the smallest possible failing test: give input `4,5`. assert output to be `4-5, 2`.
1. Write the minimum amount of code that'll make it pass.
1. Refactor any assumptions, continue to pass this test. Do not add any code without a corresponding test.

## Test Specification Overview
-------------------------------
void interpretChargingCurrentRangeAndOccurences(int chargingCurrentSamples[], char* chargingCurrentRangeAndOccurences[], size_t numberOfSamples);

This method takes charging current samples from one session as input and returns the range and it's occurences in CSV format.

Input:

1) It can be an integer array with 'n' of elements, 'n' might vary for each session.
2) Valid Inputs:
	--> Value of element should be > 0
	--> Value of elememts in an array can be consecutive or non-consecutive
		--> i.e an array can be represented as a single/ multiple ranges
3) Invalid Inputs:
	--> Empty array
	--> Negative elements 

Action:

1) void interpretChargingCurrentRangeAndOccurences(int chargingCurrentSamples[], char* chargingCurrentRangeAndOccurences[], size_t numberOfSamples);
2) int* checkForValidityOfSamples(int* chargingCurrentSamples,  size_t numberOfSamples);  
3) int* checkForConsecutiveSamples(int* chargingCurrentSamples, size_t numberOfSamples);
4) int* sortSamples(int* chargingCurrentSamples, size_t numberOfSamples);
5) void checkForAvailableRanges(int* sortedChargingCurrentSamples, int *numberOfRanges, size_t numberOfSamples, int *subsetOfChargingCurrentSamples[], RangeAndOccurences rangeAndOccurences[]);
6) void formatOutputInCSV(RangeAndOccurences rangeAndOccurences[], int numberOfRanges, int* availableRanges[], char* chargingCurrentRangeAndOccurences[]);


Ouput:

Valid Input:
--> print the ranges and it's occurences in csv format
Invalid Input
--> Print as not a valid set of sample to process

--------------------------------
struct RangeAndOccurences {
         int minValue;
         int maxValue;
         size_t Occurences;
};
