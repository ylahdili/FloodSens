/*
   This code partly written by Youness LAHDILI is in the public domain.
*/

#include <aJSON.h>
#include "SPI.h"
#include "WiFi.h"

#include "M2XStreamClient.h"

char ssid[] = "Mydd2016"; //  your network SSID (name)
char pass[] = "mydd@2016"; // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

char deviceId[] = "6dc88b5f2abeff4c9c85f3f2920233d2"; // Feed you want to post to
char m2xKey[] = "e326cdd46ffe628f9dd66c774accd513"; // Your M2X access key
char streamName[] = "floodsensor"; // Stream you want to post to

WiFiClient client;
M2XStreamClient m2xClient(&client, m2xKey);

const int  buttonPin = PUSH2;

int pinLow = 5;
//int pinMed = P5_1;
//int pinHi = P5_0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600); // msp430g2231 must use 4800

  pinMode(pinLow, INPUT_PULLUP);
  //pinMode(pinMed, INPUT_PULLUP);
  //pinMode(pinHi, INPUT_PULLUP);
  
  // attempt to connect to Wifi network:
    Serial.print("Attempting to connect to Network named: ");
    // print the network name (SSID);
    Serial.println(ssid); 
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    WiFi.begin(ssid, pass);
    while ( WiFi.status() != WL_CONNECTED) {
      // print dots while we wait to connect
      Serial.print(".");
      delay(300);
    }
  
    Serial.println("\nYou're connected to the network");
    Serial.println("Waiting for an ip address");
  
    while (WiFi.localIP() == INADDR_NONE) {
      // print dots while we wait for an ip addresss
      Serial.print(".");
      delay(300);
    }

    Serial.println("\nIP Address obtained");
  
    // you're connected now, so print out the status  
    printWifiStatus();
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin A3:
  // read the input pins:
  int StateLow = digitalRead(pinLow);
  //int StateMed = digitalRead(pinMed);
  //int StateHi = digitalRead(pinHi);
  
  // print out the state of the pin:
  Serial.println(StateLow);
  //Serial.println(StateMed);
  //Serial.println(StateHi);
  
  int total = StateLow;
  
    // Send to M2X
    int response = m2xClient.updateStreamValue(deviceId, streamName, total);
    Serial.print("M2X client response code: ");
    Serial.println(response);
    
  delay(1); // delay in between reads for stability
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}
