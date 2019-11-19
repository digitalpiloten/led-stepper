#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <BlynkSimpleEsp8266_SSL.h> // USE SSL VERSION OF BLYNK
#include <ESP8266WiFi.h>
#include <Stepper.h>

#define PIN D2
#define NUMPIXELS 60
#define BLYNK_PRINT Serial

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";


int motorSpeed; 
int motorDirection; 

const int stepsPerRevolution = 4096; 

BlynkTimer timer; 
Stepper myStepper(stepsPerRevolution, 14, 12, 13, 15); 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void stepperControl() {
  if (motorSpeed > 0) {
    if (motorDirection == 0) {  // Rotate Clockwise
      myStepper.step(stepsPerRevolution / 50);
    } else {  // Rotate CounterClockwise
      myStepper.step(-stepsPerRevolution / 50);
    }
  }
}

void setup()
{
  Serial.begin(9600);
  timer.setInterval(1, stepperControl);
  Blynk.begin(auth, ssid, pass);
  pixels.begin();
  pixels.setBrightness(55);
}

void loop()
{
  Blynk.run();
  timer.run();
}



BLYNK_WRITE(V0)
{
  motorSpeed = param.asInt();
  myStepper.setSpeed(motorSpeed);
}


BLYNK_WRITE(V2)
{

  int R = param[0].asInt();
  int G = param[1].asInt();
  int B = param[2].asInt();
  Serial.println(R);
  Serial.println(G);
  Serial.println(B);
  for (int i = 0; i < NUMPIXELS; i++) {

    pixels.setPixelColor(i, pixels.Color(R, G, B));

    pixels.show();
  }
}
