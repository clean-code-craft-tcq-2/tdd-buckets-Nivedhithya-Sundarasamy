void interpretChargingCurrentValue(int ADC_ConvertorValues[], size_t numberOfSamples, int ADC_Resolution,
		int minCurrentValue, int maxCurrentValue, int* chargingCurrentValues);
float convertInputIntegerToCurrentValue(float conversionFactor, float scalingFactor, int minCurrentValue, int maxCurrentValue);
int roundOffCurrentValue(float currentValue);
int convertChargingCurrentValueToAbsoluteValue(int chargingCurrentValue);
int checkIfValueIsAbsoluteAndConvert(int *chargingCurrentValue);
int calculateMaxIntegerValue(int ADC_Resolution);
int calculateTotalCurrentRange(int maxCurrentValue, int minCurrentValue);
float calculateMultiplyingFactor(int x, int y);
void getValidInputValues(int* ADC_Values, int ADC_Resolution, size_t numberOfSamples, size_t *numberOfValidSamples, int *ValidADC_Values);
extern void getValidInputValuesAndInterpretChargingCurrentValue(int* ADC_ConverterValues, int ADC_Resolution,
	size_t numberOfSamples, int minCurrentValue, int maxCurrentValue, size_t *numberOfValidSamples, int *ValidADC_Values, int *chargingCurrentValues);
