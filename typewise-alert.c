#include "typewise-alert.h"
#include <stdio.h>

CoolingInfoType CoolingInfo[3] = {{0,35,PASSIVE_COOLING},{0,45,HI_ACTIVE_COOLING},{0,40,MED_ACTIVE_COOLING}};
InfoType (*TargetType[])(BreachType) = {sendToController,sendToEmail,sendToConsole};
InfoType (*Email[])(const char*) ={NormalMessage,TooLowmessage,Toohighmessage};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) 
{	
  return inferBreach(temperatureInC, CoolingInfo[coolingType].LowerLimit, CoolingInfo[coolingType].UpperLimit);
}

InfoType checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
	InfoType Value = FAIL;
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
	Value = (*TargetType[alertTarget])(breachType);
	return Value;
}
  
InfoType sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
  return PASS;
}

InfoType TooLowmessage (const char* recepient)
{
	printf("To: %s\n", recepient);
    printf("!! ALERT !! temperature is too low\n");
	return PASS;
}

InfoType Toohighmessage (const char* recepient)
{
	printf("To: %s\n", recepient);
    printf("!! ALERT !! temperature is too high\n");
	return PASS;
}

InfoType NormalMessage (const char* recepient)
{
	printf("To: %s\n", recepient);
    printf(" ! OKAY ! temperature is normal\n");
	return PASS;
}
	

InfoType sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  (*Email[breachType])(recepient);
  return PASS;
}
