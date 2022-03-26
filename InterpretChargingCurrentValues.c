#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void interpretChargingCurrentValue(int ADC_ConvertorValues[], size_t numberOfSamples, int ADC_Resolution,
		int minCurrentValue, int maxCurrentValue, int* chargingCurrentValues) {
	int maxIntegerValue, totalCurrentValue;
	float currentValue, conversionFactor, scalingFactor;

	// Integer Value starts with zero and as per specification last integer value based on resolution is considered as an error
	maxIntegerValue = pow(2,ADC_Resolution) - 2;
	totalCurrentValue = maxCurrentValue - minCurrentValue;
	for (size_t i=0; i<numberOfSamples; i++){
		scalingFactor = float(totalCurrentValue) / float(maxCurrentValue);
		conversionFactor = float(ADC_ConvertorValues[i]) / float(maxIntegerValue);
		currentValue = minCurrentValue + (maxCurrentValue * conversionFactor * scalingFactor);
		chargingCurrentValues[i] = round(currentValue);
		if(chargingCurrentValues[i] < 0)
			chargingCurrentValues[i] = abs(chargingCurrentValues[i]);
	}	
	
}

