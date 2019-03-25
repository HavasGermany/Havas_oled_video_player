/*
 * Havas Dūsseldorf // UltraCM ruler,
 * Arnaud Atchimon 2019
 * https://de.havas.com/
 * this project was made to show you how to integrate the vcideo codes into your own projects
 * please download the U8G2 LIBRARY from Oli Kraus >> https://github.com/olikraus/u8g2
 * 
 * 
  WEMOS PINOUT
  --Oled
  GND   >     GND
  VCC   >     5V
  SCL   >     20 //D1
  SDA   >     19 //D2
  --Ultrasonic
  GND   >     GND
  VCC   >     5V
  TRIG  >     13 //D7
  ECHO  >     12 //D6
  --button
  BTN   >     14 //D5
*/
#include <Arduino.h>
#include <U8g2lib.h>
//
#ifdef U8X8_HAVE_HW_SPI
#include<SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include<Wire.h>
#endif
#include "myMovie.h"

#define btn D5

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// defines pins numbers
const int trigPin = 13;  //D7
const int echoPin = 12;  //D6

// defines variables
long duration;
int distance;
//all parameters
int currentMovie = 0;
int movieSpeed = 10;
int measurement = 0;
static int frameRate = -1;
int counter = 0;
int currentFrame;


void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(btn, INPUT_PULLUP);
  //
  u8g2.begin();
  u8g2.setDrawColor(0);
  while (1) {
    int btnMenu = digitalRead(btn);
    // havas intro here, comment this line if you want to test your own animation
    //    havas_intro(0, 32, 0, 64, 64, 0, havasbits_frames);
    // your animation comes here
    yourMovie(0, 0, 0, 128, 64, 0, myMoviebits_frames);

    if (btnMenu == LOW) {
      delay(250);
      // currentMovie++;
      Serial.println("GO");
      frameRate = 0;
      break;
    }
  }
  //  u8g2.setBitmapMode(0);
  delay(300);
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  u8g2.firstPage();
  do {
    if (distance > 4 && distance < 1500 ) {
      u8g2.setFont(u8g2_font_7Segments_26x42_mn);
      u8g2.setCursor(10, 56);
      u8g2.print(distance);
      u8g2.setFont(u8g2_font_freedoomr10_tu);
      u8g2.setCursor(10, 12);
      u8g2.print("CM");
    } else {
      u8g2.setFont(u8g2_font_7Segments_26x42_mn);
      u8g2.setCursor(10, 56);
      u8g2.print(":0:  ");
      u8g2.setFont(u8g2_font_freedoomr10_tu);
      u8g2.setCursor(10, 12);
      u8g2.print("CM");
    }
    if (distance > 400 ) {
      u8g2.setFont(u8g2_font_7Segments_26x42_mn);
      u8g2.setCursor(10, 56);
      u8g2.print("0:0 ");
      u8g2.setFont(u8g2_font_freedoomr10_tu);
      u8g2.setCursor(10, 12);
      u8g2.print("CM");
    }
  } while ( u8g2.nextPage() );

  delay(500);
}




void yourMovie(boolean dir, int Xface, int Yface, int Xsize, int Ysize, int frameStart, int frameStop) {
  static int ms;
  uint32_t frames = millis();
  static int frameRate = frameStart;

  //play movie
  while (dir == 0) {
    if (++frameRate > frameStop) {
      frameRate = frameStart;
      Serial.println(frameRate);
      delay(100);
      ms = 0;
    }
    u8g2.firstPage();
    do {
      u8g2.setDrawColor(0);
      u8g2.drawXBMP( Xface, Yface, Xsize, Ysize, myMovie[frameRate]);
      u8g2.setFont(u8g2_font_logisoso24_tf);
      u8g2.setDrawColor(1);
      u8g2.setCursor(4, 44);
      u8g2.print("Ultra CM");
    } while ( u8g2.nextPage() );
    break;
  }

  //Change the direction of the movie
  while (dir == 1) {
    if (--frameRate < frameStop) {

      frameRate = frameStart;
      //Serial.println(ms);
      delay(100);
      ms = 0;
    }
    u8g2.firstPage();
    do {
      u8g2.setDrawColor(0);
      u8g2.drawXBMP( Xface, Yface, Xsize, Ysize, myMovie[frameRate]);
      u8g2.setDrawColor(1);
      u8g2.setFont(u8g2_font_logisoso24_tf);
      u8g2.setCursor(4, 44);
      u8g2.print("Ultra CM");
    } while ( u8g2.nextPage() );
    break;
  }


  ms += millis() - frames;
  delay(movieSpeed);
}



