#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN    6   
#define LED_COUNT 30   
#define AUDIO_PIN A0   

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

unsigned long sampleWindow = 40; //placa citeste sunetul timp de 40ms pt a isi da seama de cat de puternic este
unsigned int sample;


void setup() {
  strip.begin();
  strip.show();            
  Serial.begin(9600); 
}

void loop() { 
  unsigned long startMillis = millis(); //timpul exact al fiecarei bucle
  unsigned int peakToPeak = 0; //diferenta dintre min si max din cele 40 ms
  unsigned int signalMax = 0;
  unsigned int signalMin = 1023;

  while (millis() - startMillis < sampleWindow) {
    sample = analogRead(AUDIO_PIN); //citeste sunetul de la microfon
    if (sample < 1023) { //verific daca sunetu e valid
      if (sample > signalMax) { //verific daca exista sunet mai puternic in secventa de 40 ms
        signalMax = sample; 
      } 
      else if (sample < signalMin) { //apoi daca gasesc mai slab
        signalMin = sample;
      }
    }
  }
  
  peakToPeak = signalMax - signalMin; //amplitutdinea sunetului

Serial.print("Putere zgomot: ");//afisez in serial monitor
 Serial.println(peakToPeak);


  int ledLevel = map(peakToPeak, 3, 15, 0, LED_COUNT);//praguri. un zgomot nivel 3 aprinde 0 led, unul nivel 15 pe toate
  
  ledLevel = constrain(ledLevel, 0, LED_COUNT); ///previne in cazul unui sunet mult prea tare aprinderea in afara razei impusa

  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    if (i < ledLevel) {
      if (i < LED_COUNT / 3) {
        strip.setPixelColor(i, strip.Color(0, 255, 0));//led urile 0-9 -> verde
      } else if (i < (LED_COUNT * 2) / 3) {
        strip.setPixelColor(i, strip.Color(255, 150, 0)); //led urile 10-19 -> portocaliu-galben
      } else {
        strip.setPixelColor(i, strip.Color(255, 0, 0)); //led urile ramase -> rosu
      }
    } else {
      strip.setPixelColor(i, strip.Color(0, 0, 0)); //sunetul a scazut -> led uri superioare stinse
    }
  }

  strip.show(); //s a calculat ce culoare are fiecare led, se trimite semnalul fizic catre bansa, apoi loop() o ia de la capat
}