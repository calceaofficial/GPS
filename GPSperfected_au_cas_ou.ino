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

      Serial.print("JourneyMap.RouteCoordinates.Add(new Position("); printDouble(latitude, 1000000); Serial.print(", "); printDouble(longitude, 1000000); Serial.println("));");
    }
  }
}


void printDouble( double val, unsigned int precision){
// prints val with number of decimal places determine by precision
// NOTE: precision is 1 followed by the number of zeros for the desired number of decimial places
// example: printDouble( 3.1415, 100); // prints 3.14 (two decimal places)

   Serial.print (int(val));  //prints the int part
   Serial.print("."); // print the decimal point
   unsigned int frac;
   if(val >= 0)
       frac = (val - int(val)) * precision;
   else
       frac = (int(val)- val ) * precision;
   Serial.print(frac,DEC) ;
} 
