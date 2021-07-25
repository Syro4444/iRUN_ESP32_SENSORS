#include "DHT.h"
#include <Adafruit_NeoPixel.h>

#define LEDPIN 16
#define NUMPIXELS 9
#define PULSEPIN 15

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);


#define DHTPIN 4     
 

#define DHTTYPE DHT11   // DHT 11
int lightPin = 0;
int isOn = 0;

DHT dht(DHTPIN, DHTTYPE);


int averageTreshold = 0 ;


void setup() {
  strip.begin();
  strip.show();
  Serial.begin(115200);
  Serial.println("PLOPPPPPPP");
  dht.begin();

  int l = analogRead(lightPin);
  for(int i=0;i<5;i++){
    averageTreshold = averageTreshold + l;
    delay(200);
  }
  averageTreshold /= 5;
}

void loop() {
  delay(500);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  int l = analogRead(lightPin);
  int p = analogRead(PULSEPIN);
  
  int lightTreshold = 400 ;
  
  Serial.print(F("Humidity: "));
  Serial.println(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
  Serial.print(F("Luminosite: "));
  Serial.print(l);
  Serial.print(F("lightTreshold: "));
  Serial.println(lightTreshold);
   Serial.print(F("Pulse: "));
  Serial.println(p); 
  Serial.print(F("isOn: "));
  Serial.println(isOn); 
  
  delay(500);

    
    
//    if(isOn==1){
//      lightTreshold += 130;
//    }

    if(l<lightTreshold){
    //if(l<lightTreshold){
        for(int i=0;i<NUMPIXELS;i++){
        strip.setPixelColor(i, 50, 50, 50);
        strip.show();
        delay(15);
        }
        isOn = 1;
    }
    else{
        for(int i=0;i<NUMPIXELS;i++){
        strip.setPixelColor(i, 0, 0, 0);
        strip.show();
        delay(15);
        }
        isOn = 0;
    }
    
    
  
}
