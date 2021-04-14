#pragma once

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL,
  TO_CONSOLE
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

typedef enum{
	FAIL,
	PASS
} InfoType;

typedef struct
{
	
	int LowerLimit;
	int UpperLimit;
	CoolingType coolingType;
}CoolingInfoType;

InfoType checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

InfoType sendToController(BreachType breachType);
InfoType sendToEmail(BreachType breachType);
InfoType TooLowmessage (const char* recepient);
InfoType Toohighmessage (const char* recepient);
InfoType NormalMessage (const char* recepient);
InfoType sendToConsole(BreachType breachType);
