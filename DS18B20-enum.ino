// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 14 on the Arduino
#define ONE_WIRE_BUS 14
// DAC precision
#define TEMPERATURE_PRECISION 9

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

DeviceAddress thermometer;
int deviceNumber;

void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();

  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  deviceNumber=sensors.getDeviceCount();
  Serial.print(deviceNumber, DEC);
  Serial.println(" devices.");

  // report parasite power requirements
  Serial.print("Parasite power is: ");
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");
  if (deviceNumber>0){
    for (int i=0; i<deviceNumber; i++) {
      sensors.getAddress(thermometer, i);
      Serial.printf("Device %d Address: ",i);
      printAddress(thermometer);
      Serial.println();
      sensors.setResolution(thermometer, TEMPERATURE_PRECISION);
      Serial.printf("Device %d Resolution: ",i);
      Serial.print(sensors.getResolution(thermometer), DEC);
      Serial.println();
    }
  } else {
    Serial.println("ERROR No sensor connected");  
  }
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Temp °C: ");
  Serial.print(tempC);
}

// function to print a device's resolution
void printResolution(DeviceAddress deviceAddress)
{
  Serial.print("Resolution: ");
  Serial.print(sensors.getResolution(deviceAddress));
  Serial.println();
}

// main function to print information about a device
void printData(DeviceAddress deviceAddress)
{
  Serial.print("Device Address: ");
  printAddress(deviceAddress);
  Serial.print(" ");
  printTemperature(deviceAddress);
  Serial.println();
}

/*
   Main function, calls the temperatures in a loop.
*/
void loop(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures();
  Serial.println("DONE");
  if (deviceNumber>0){
    for (int i=0; i<deviceNumber; i++) {
      sensors.getAddress(thermometer, i);
      printData(thermometer);
    }
  } else {
    Serial.println("ERROR: Nothing to mesure!");
  } 
  delay (5000);
}
