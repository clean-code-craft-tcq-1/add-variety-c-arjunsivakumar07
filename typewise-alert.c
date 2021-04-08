#include "typewise-alert.h"
#include <stdio.h>

CoolingInfoType CoolingInfo[3] = {{0,35,PASSIVE_COOLING},{0,45,HI_ACTIVE_COOLING},{0,40,MED_ACTIVE_COOLING}};
void (*TargetType[])(BreachType) = {sendToController,sendToEmail};
void (*Email[])(const char*) ={NormalMessage,TooLowmessage,Toohighmessage};

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

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  (*TargetType[alertTarget])(breachType);
}
  
void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void TooLowmessage (const char* recepient)
{
	printf("To: %s\n", recepient);
    printf("!! ALERT !! temperature is too low\n");
}

void Toohighmessage (const char* recepient)
{
	printf("To: %s\n", recepient);
    printf("!! ALERT !! temperature is too high\n");
}

void NormalMessage (const char* recepient)
{
	printf("To: %s\n", recepient);
    printf(" ! OKAY ! temperature is normal\n");
}
	

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  (*Email[breachType])(recepient);
}
