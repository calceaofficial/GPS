#include <SoftwareSerial.h>

#include <TinyGPS++.h>

SoftwareSerial Serial1(8, 9);                                                             // RX, TX

char data;                                                                               // données Brutes
   
double latitude;                                                                        //double nombre à virgule d'une certaine taille
double longitude;  
double alt;                                                                             //altitude
double vitesse;
unsigned long nbre_sat;
 
TinyGPSPlus gps;
 
void setup() {
  //Initialize serial and wait for port to open:
  Serial1.begin(9600);
  Serial.begin(9600);
  
}
 
void loop() {
  while (Serial1.available()) {                                                       //tant que le signal est disponible
    data = Serial1.read();
    //  Serial.print(data);
    gps.encode(data);
    if (gps.location.isUpdated())                                                     // si la localisation GPS s'actualise
    {
      latitude = gps.location.lat();                                                  // commandes disponibles grâce à la librairie TinyGPS++
      longitude = gps.location.lng();
      alt = gps.altitude.meters();
      vitesse = gps.speed.kmph();
      nbre_sat = gps.satellites.value();
 
      Serial.println("-------- FIX GPS ------------");                                // rendu moniteur série
      Serial.print("LATITUDE="); Serial.println(latitude);
      Serial.print("LONGITUDE="); Serial.println(longitude);
      Serial.print("ALTITUDE (m) ="); Serial.println(alt);
      Serial.print("VITESSE (km/h)="); Serial.println(vitesse);
      Serial.print("NOMBRE SATTELLITES="); Serial.println(nbre_sat);
    }
  }
}
