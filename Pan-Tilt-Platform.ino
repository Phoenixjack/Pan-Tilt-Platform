/*
Arduino code for controlling dual 28BYJ-48 stepper motors with a Wemos D1 Mini using a browser on a device in local network.

ORIGINAL CODE BY: KushagraK7: https://www.instructables.com/member/KushagraK7/

Quick References:
https://developer.mozilla.org/en-US/docs/Web/HTML/Element/input/button
https://developer.mozilla.org/en-US/docs/Web/API/WebSockets_API/Writing_WebSocket_client_applications
*/

#include <ESP8266WiFi.h>       // https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/WiFiAccessPoint/WiFiAccessPoint.ino
#include <ESP8266WebServer.h>  // https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer
#include <Stepper.h>           // http://www.arduino.cc/en/Reference/Stepper
#include "PageIndex.h"         // Include the contents of the User Interface Web page, stored in the same folder as the .ino file

#define LEDonBoard 12                           //--> Defining an On Board LED, used for indicators when the process of connecting to a wifi router
#define STEPS 100                               // change to stepper
#define defMyOwnAP 0                            // do I start my own AP or join someone else's?
Stepper objAzimuth(STEPS, 16, 17, 18, 19);      // https://randomnerdtutorials.com/esp32-pinout-reference-gpios/  GPIO16-33
Stepper objInclination(STEPS, 20, 21, 22, 23);  // https://forum.arduino.cc/t/28byj-48-steps-per-revolution/876716  32 steps/revolution at typical 64:1 gearing = ~4096
const char *ssid = "Triton";                    //
const char *password = "az52p7fvnc";            //

int intCurrAz = 0;               // start out zeroed
int intTargetAz = 0;             //
int intCurrInc = 0;              //
int intTargetInc = 0;            //
int intHorDirection = 0;         // -1 for CCW, 0 for stop, 1 for CW
int intMaxSpeed = 13;            //
int intSpeed = intMaxSpeed / 3;  //
int intCommand = 0;              // set to do nothing by default


String strValue;
String strCommand;
String strSendData;

ESP8266WebServer server(80);

void handleRoot() {                  //
  String s = MAIN_page;              // Read HTML contents
  server.send(200, "text/html", s);  // Send web page
}
void setInclination() {             // setINC?val="+pos
  intCommand = 3;                   // cause main loop to execute move
  strValue = server.arg("val");     //
  intTargetInc = strValue.toInt();  //
  reportgood();                     //
}
void setAzimuth() {                // setAZ?val="+pos
  intCommand = 3;                  // cause main loop to execute move
  strValue = server.arg("val");    //
  intTargetAz = strValue.toInt();  //
  reportgood();                    //
}
void setSpeed() {                     // setSP?val="+pos
  intCommand = 2;                     // cause main loop to execute move AND report current status
  strValue = server.arg("val");       //
  intSpeed = strValue.toInt();        // TODO:... map our 0-100 value to 0-intMaxSpeed
  objAzimuth.setSpeed(intSpeed);      //
  objInclination.setSpeed(intSpeed);  //
  reportgood();                       //
}
void exec_command() {                 // command?val="+pos
  strCommand = server.arg("val");     // 0=stop 1=set zero 2=reportposition 3=move
  if (strCommand == "2") {            // if we're told to report position,
    reportposition();                 // just do it now, but don't disrupt mainloop's switch case
  } else {                            // otherwise, we need to interpret the command for mainloop
    intCommand = strCommand.toInt();  // convert strCommand to integer. Enables case switching in main loop
  }                                   //
  reportgood();                       //
}
void reportposition() {                         // report our current position one at a time
  strSendData = "Az=" + String(intCurrAz);      // append currAz to label
  server.send(200, "text/plain", strSendData);  // and send to client
  strSendData = "Az=" + String(intCurrInc);     // append currInc to label
  server.send(200, "text/plain", strSendData);  // and send to client
}
void reportgood() {                    // send blank http 200 response to acknowledge successful processing
  server.send(200, "text/plain", "");  //
}
void setup() {                                     //
  Serial.begin(115200);                            //
  pinMode(LEDonBoard, OUTPUT);                     //--> On Board LED as output
    Serial.print(F("\n"
                 "Sketch: " __FILE__ "\n"
                 "Compiled: " __DATE__ " " __TIME__ "\n"
                 "Code by: Chris McCreary\n"));
  delay(1000);                                     //
  Serial.println("BOOTED!");                 //
  if (defMyOwnAP) {                                // do we setup our own AP or join?
    Serial.print("Configuring access point...");   //
    digitalWrite(LEDonBoard, LOW);                 // TODO: switch this to WiFiManager library
    WiFi.softAP(ssid, password);                   // You can remove the password parameter if you want the AP to be open.
    IPAddress myIP = WiFi.softAPIP();              //
    Serial.print("AP IP address: ");               //
    Serial.println(myIP);                          //
  } else {                                         //
    WiFi.begin(ssid, password);                    //--> Connect to your WiFi router
    Serial.println("");                            //
    digitalWrite(LEDonBoard, HIGH);                //--> Turn off Led On Board
    Serial.print("Connecting");                    //
    while (WiFi.status() != WL_CONNECTED) {        //
      Serial.print(".");                           //
      digitalWrite(LEDonBoard, LOW);               //
      delay(500);                                  //
      digitalWrite(LEDonBoard, HIGH);              //
      delay(500);                                  //
    }                                              //
    Serial.println("");                            //
    Serial.print("Successfully connected to : ");  //
    Serial.println(ssid);                          //
    Serial.print("IP address: ");                  //
    Serial.println(WiFi.localIP());                //
  }                                                //
  digitalWrite(LEDonBoard, HIGH);                  //--> Turn off the On Board LED when WiFi is established
  server.on("/", handleRoot);                      //--> Routine to handle at root location. This is to display web page.
  server.on("/setINC", setInclination);            //--> Sets servo position from Web request
  server.on("/setAZ", setAzimuth);                 // setINC?val="+pos  setAZ?val="+pos   command?val="+pos  setSP?val="+pos
  server.on("/setSP", setSpeed);                   //
  server.on("/command", exec_command);             //
  server.begin();                                  //
  Serial.println("HTTP server started");           //
  objAzimuth.setSpeed(intSpeed);                   // defined by RPM
  objInclination.setSpeed(intSpeed);               //
}

void loop() {
  server.handleClient();
  switch (intCommand) {                                              // intCommand 0=stop 1=set zero 2=report pos 3=move
    case 0:                                                          // skip all move commands to servos
      break;                                                         // do nothing
    case 1:                                                          // set zero. VERY DANGEROUS! Watch your cables!
      intCurrAz = 0;                                                 // sets our current azimuth as zero
      intCurrInc = 0;                                                // sets our current inclination as zero
      intCommand = 0;                                                // set command to do nothing in future loops
      break;                                                         //
    case 2:                                                          // report pos
      reportposition();                                              // technically, this should never execute, but just in case
      intCommand = 0;                                                // we've done what we were told, so don't do anything afterwards
      break;                                                         //
    case 3:                                                          // move (if necessary)
      if (intCurrAz == intTargetAz && intCurrInc == intTargetInc) {  // check if our current position is at our target
        intCommand = 0;                                              // we've met our target, so clear command
      } else {                                                       //
        executemove();                                               // move your body
      }                                                              //
      break;                                                         //
  }                                                                  //
}

void executemove() {  // i like to move it move it
  if (intCurrAz > intTargetAz) {}
  if (intCurrAz < intTargetAz) {}
  if (intCurrInc > intTargetInc) {}
  if (intCurrInc < intTargetInc) {}
}
void moveincline(int intIncDir) {
  // objInclination.step(numSteps)
}
void moveazimuth(int intAzDir) {
  // objAzimuth.step(numSteps)
}