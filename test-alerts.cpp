#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
}

TEST_CASE("Classify temperature") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 30) == NORMAL);
}

TEST_CASE("check and alert") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = HI_ACTIVE_COOLING;
  REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, 50) == PASS);
}

TEST_CASE("check and alert2") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = MED_ACTIVE_COOLING;
  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, -1) == PASS);
}
TEST_CASE("check and alert3") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = PASSIVE_COOLING;
  REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, -1)==PASS);
}
TEST_CASE("check and alert4") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = MED_ACTIVE_COOLING;
  REQUIRE(checkAndAlert(TO_CONSOLE, batteryChar, 30 ) == PASS);
}

TEST_CASE("check and alert5") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = MED_ACTIVE_COOLING;
  REQUIRE(sendToConsole(TOO_LOW) == PASS);
  REQUIRE(sendToEmail(TOO_LOW) == PASS);
}
TEST_CASE("Check and alert6")
{
  REQUIRE(sendToConsole(TOO_HIGH) == PASS);	
  REQUIRE(sendToEmail(TOO_HIGH) == PASS);
}
