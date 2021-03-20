#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
const char* ssid = "GMQnG";
const char* password = "GMQnG";
int Gas_analog = A0;
int buzz = 12;
ESP8266WebServer server(80);
/*
int ledgreen = 14 ;
int ledyellow = 5;
int ledyellow2 = 4;
int ledred = 0;
int ledred2 = 2;
ppm  of CH4 at home

5 > x : green 
5 < x < 20 :yellow 1
20 < x < 75 :yellow 2
75 < x < 150 :red
150 < x < 1000 :red2
1000 < x : buzz 
*/
void webpage(){
  int gassensorAnalog = analogRead(Gas_analog);
  //Serial.println(gassensorAnalog);
  float gasProportion= ((gassensorAnalog*100)/1024)*100; //in 200 ppm to 10 000
  String webhtml ="<!DOCTYPE html><html><body><h1>GMQnG</h1><h2>GAS mq Not is <a href='https://jero98772.pythonanywhere.com/proyects/gasinfo.html'>GAS(GAS FROM GASTAR)</a> </h2><h3> get gas mesure of metano (CH4) </h3><p>is very helpful for detect gas leaks , and avoid exploitation or a penalty</p><br><h3>";
  webhtml +=gasProportion;
  webhtml +="%</h3> <br> <h3>analog value</h3>"; 
  webhtml +=gassensorAnalog; 
  webhtml +="%</h3></body></html>"; 
  server.send(200, "text/html", webhtml);
  }
void setup() {
  Serial.begin(115200);
  pinMode(buzz,OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("IP:");
  Serial.println(myIP);
  server.on("/", webpage);
  server.begin();            
  Serial.println("HTTP server started");
  /*
  pinMode(ledgreen,OUTPUT);
  pinMode(ledyellow,OUTPUT);
  pinMode(ledyellow2,OUTPUT);
  pinMode(ledred,OUTPUT);
  pinMode(ledred2,OUTPUT);
  */

}
void loop() {
 /*
  putOn(gassensorAnalog<5,ledgreen) ;
  putOn(5<gassensorAnalog<20,ledyellow);
  putOn(20<gassensorAnalog<75,ledyellow2);
  putOn(75<gassensorAnalog<150,ledred);
  putOn(150<gassensorAnalog< 1000,ledred2);
  putOn(1000<gassensorAnalog,buzz);
  */
  int gassensorAnalog = analogRead(Gas_analog);
  Serial.println(gassensorAnalog);
  putOn(1000<gassensorAnalog,buzz);
  server.handleClient();
  delay(100);
}

void putOn(bool booleanOperation ,int pin) {
  if (booleanOperation){
      digitalWrite(pin, HIGH);
  }
}
