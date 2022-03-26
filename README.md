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

## Test Extension Specification
------------------------------

1) Add a new method 'interpretTheCurrentValue' for sensing the current with inputs from the current sensor.

2) This method takes array of integers with 'n' bit resolution as input based on the A2D convertor resolution within the current sensor.
e.g 
For 12 bit A2D, integer value can be of 12 bit resolution i.e: 0-4095
For 10 bit A2D, integer value can be of 10 bit resolution i.e: 0-1023

3) This method also takes current measurement range as another parameter
e.g
Current Measurement Range can be,
0 A to 10 A
-15 A to 15 A

4) This method linearly interprets the current value based on the resolution and measurement range.
e.g
For 12bit resolution current sensor with '0-10A' measurement range, integer value '0' corresponds to 0A and the value '4094' corresponds to the 10A.
For 10bit resolution current sensor with '-15 to 15 A' measurement range, integer value '0' corresponds to -15A , value '1022' correspnds to 15A and the value '511' corresponds to 0A.

5) This method should handle to ignore the error readings based on the resolution.
eg:
For 10 bit A2D, integer value '1023' is reported as an error.
For 12 bit A2D, integer value '4095' is reported as an error.

6) This method should convert the interpreted current values to an absolute value.
e.g:
If the current value is interpreted as 2.799 A, it should be rounded off to the nearest integer. i.e 3 A.
If the current value is interpreted as -12A, it should be converted to it's magnitude. i.e 12A

7) This method returns for an n array of calculated/interpreted current values for given integer array of 'n' bit resolution and for a given measurement range.

8) The output of this method (i.e array of current range) would be given as an input to the already existing method 'interpretChargingCurrentRangeAndOccurences'.
