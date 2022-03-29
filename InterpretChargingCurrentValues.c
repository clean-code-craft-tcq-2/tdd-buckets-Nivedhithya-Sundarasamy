#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float convertInputIntegerToCurrentValue(float conversionFactor, float scalingFactor, int minCurrentValue, int maxCurrentValue){
	float currentValue;	
	currentValue = minCurrentValue + (maxCurrentValue * conversionFactor * scalingFactor);
	return currentValue;
}

int roundOffCurrentValue(float currentValue){
	int roundedChargingCurrentValue;
	roundedChargingCurrentValue = round(currentValue);
	return roundedChargingCurrentValue;
}

int convertChargingCurrentValueToAbsoluteValue(int chargingCurrentValue){
	chargingCurrentValue = abs(chargingCurrentValue);
	return chargingCurrentValue;
}

int checkIfValueIsAbsoluteAndConvert(int *chargingCurrentValue) {
	return (*chargingCurrentValue < 0) ? convertChargingCurrentValueToAbsoluteValue(*chargingCurrentValue) : *chargingCurrentValue;
}

int calculateMaxIntegerValue(int ADC_Resolution) {
	int maxIntegerValue;
	// Integer Value starts with zero and as per specification last integer value based on resolution is considered as an error
	maxIntegerValue = pow(2,ADC_Resolution) - 2;
	return maxIntegerValue;
}

int calculateTotalCurrentRange(int maxCurrentValue, int minCurrentValue) {
	int totalCurrentRange;
	totalCurrentRange = maxCurrentValue - minCurrentValue;
	return totalCurrentRange;
}

float calculateMultiplyingFactor(int x, int y) {
	float multiplyingFactor;
	multiplyingFactor = float(x) / float(y);
	return multiplyingFactor;
}

void interpretChargingCurrentValue(int ADC_ConvertorValues[], size_t numberOfSamples, int ADC_Resolution,
		int minCurrentValue, int maxCurrentValue, int* chargingCurrentValues) {
	int maxIntegerValue, totalCurrentRange;
	float currentValue, conversionFactor, scalingFactor;

	maxIntegerValue = calculateMaxIntegerValue(ADC_Resolution);
	totalCurrentRange = calculateTotalCurrentRange(maxCurrentValue, minCurrentValue);
	for (size_t i=0; i<numberOfSamples; i++){
		scalingFactor = calculateMultiplyingFactor(totalCurrentRange, maxCurrentValue);
		conversionFactor = calculateMultiplyingFactor(ADC_ConvertorValues[i], maxIntegerValue);
		currentValue = convertInputIntegerToCurrentValue(conversionFactor, scalingFactor, minCurrentValue, maxCurrentValue);
		chargingCurrentValues[i] = roundOffCurrentValue(currentValue);
		checkIfValueIsAbsoluteAndConvert(&chargingCurrentValues[i]);
	}	
}

void getValidInputValues(int* ADC_Values, int ADC_Resolution, size_t numberOfSamples, size_t *numberOfValidSamples, int *ValidADC_Values) {
	int errorValue;
	size_t j=0;
	
	errorValue = pow(2,ADC_Resolution) - 1;
	
	for(size_t i=0; i<numberOfSamples; i++){
		if(ADC_Values[i] != errorValue){
			ValidADC_Values[j] = ADC_Values[i];
			j++;
		}
	}
	*numberOfValidSamples = j;		
}

