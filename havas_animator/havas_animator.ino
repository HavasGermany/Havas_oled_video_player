/*
   Havas Dūsseldorf // havas animator
   https://de.havas.com/
     Arnaud Atchimon 2019
   this sketch will help you get started with creating and running your own Oled animations
   please download the U8G2 LIBRARY from Oli Kraus >> https://github.com/olikraus/u8g2

  WEMOS PINOUT
  --Oled
  GND   >     GND
  VCC   >     5V
  SCL   >     20 //D1
  SDA   >     19 //D2
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

//animation configs
// havas logo animation
#include "havas_intro.h"

//comment this line if you run out of space,
//do not forget to then comment out the "[void myEmotions(boolean dir...." ] function block starting at line 242
//comment out the
//#include "havas_emotions.h"

//your movieAnimation comes here
#include "myMovie.h"

#define btn D5
//ESP32 BTN
//#define btnEsp 34

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

//all parameters
int currentMovie = 0;
int movieSpeed = 10;
int measurement = 0;
static int frameRate = -1;
int counter = 0;
int currentFrame;
int tripMagnet = 20;
int demoMode = 0;
char *names[] = {"blink", "normal", "what", "bigblink", "bigblink2", "think", "mean", "weirdblink", "weirdtalk", "cubethink2", "mean2", "sad", "meantalk", "what", "wrong", "bar", "bigsquare", "squaretalk",};

void setup() {
  Serial.begin(115200);
  u8g2.begin();
  u8g2.setDrawColor(0);
  u8g2.setBitmapMode(0);
  delay(300);
  pinMode(btn, INPUT_PULLUP);
  //  pinMode(btnEsp, INPUT_PULLUP); //esp32 btn

  while (1) {
    int btnMenu = digitalRead(btn);
    //    int btnMenu = digitalRead(btnEsp); //esp32
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
}

void frameCounter()
{
  u8g2.setFont(u8g2_font_logisoso16_tf);
  u8g2.setCursor(4, 24);
  u8g2.setDrawColor(0);
  u8g2.print(frameRate);
}

/*EMOTIONBITS FRAME SECTION
  //
  0 ,30
  31,61
  62,123
  124,154
  155,185
  186,216
  217,247
  248,278
  279,309
  310,341
  342,371
  372,464
  465,495
  496,526
  527, 556
  557,587

*/
//void esp32Control() {
//using the Hall sensor from the ESP32 instead of button to trigger the animations
//  if using esp32 with magnet instead of button
//  measurement = hallRead();
//  Serial.println(measurement);
//  if (measurement <= tripMagnet) {
//    currentMovie++;
//  }
//int btnMenu = digitalRead(btnEsp);
//  if (btnMenu == LOW) {
//    delay(250);
//    currentMovie++;
//    Serial.println("GO");
//    frameRate = 0;
//  }
//}

void wemosControl() {
  int btnMenu = digitalRead(btn);
  if (btnMenu == LOW) {
    delay(250);
    currentMovie++;
    Serial.println("GO");
    frameRate = 0;
  }
}


void loop() {
  //Input Controls
  // esp32Control();
  wemosControl();

  //Movie parameters are here
  // Robot emotion control block
  // void MovieControl(boolean playmode, boolean dir, int Xface, int Yface, int Xsize, int Ysize, int frameStart, int frameStop) {
  //  myEmotionBlock();

  //your movie control goes below,
  // void MovieControl(boolean playmode, boolean dir, int Xface, int Yface, int Xsize, int Ysize, int frameStart, int frameStop) {
  //  yourMovie(0, 0, 0, 128, 64, 0, myMoviebits_frames);
  //  forward_play
  yourMovie(0, 0, 0, 128, 64, 0, myMoviebits_frames);
  //  backward_play
  //  yourMovie(1, 0, 0, 128, 64, myMoviebits_frames, 0);
}


void havas_intro(boolean dir, int Xface, int Yface, int Xsize, int Ysize, int frameStart, int frameStop) {
  static int ms;
  uint32_t frames = millis();
  static int frameRate = frameStart;

  //play movie
  while (dir == 0) {
    if (++frameRate > frameStop) {
      frameRate = frameStart;
      //Serial.println(ms);
      delay(100);
      ms = 0;
    }
    u8g2.firstPage();
    do {
      u8g2.drawXBMP( Xface, Yface, Xsize, Ysize, havasbits[frameRate]);
      u8g2.setFont(u8g2_font_logisoso16_tf);
      u8g2.setCursor(4, 54);
      u8g2.setDrawColor(0);
      u8g2.print(frameRate);
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
      u8g2.drawXBMP( Xface, Yface, Xsize, Ysize, havasbits[frameRate]);
      u8g2.setFont(u8g2_font_logisoso16_tf);
      u8g2.setCursor(4, 54);
      u8g2.setDrawColor(0);
      u8g2.print(frameRate);
    } while ( u8g2.nextPage() );
    break;
  }


  ms += millis() - frames;
  delay(movieSpeed);
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
      u8g2.drawXBMP( Xface, Yface, Xsize, Ysize, myMovie[frameRate]);
      u8g2.setFont(u8g2_font_logisoso16_tf);
      u8g2.setCursor(4, 54);
      u8g2.setDrawColor(0);
      u8g2.print(frameRate);
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
      u8g2.drawXBMP( Xface, Yface, Xsize, Ysize, myMovie[frameRate]);
      u8g2.setFont(u8g2_font_logisoso16_tf);
      u8g2.setCursor(4, 54);
      u8g2.setDrawColor(0);
      u8g2.print(frameRate);
    } while ( u8g2.nextPage() );
    break;
  }


  ms += millis() - frames;
  delay(movieSpeed);
}



// OUT ALL THE LINES BELOW IF YOU WANT TO RUN THE EMOTION ANIMATION, COMMENT IT IF RUN OUT OF SPACE ON YOUR DEVICE,
//void myEmotions(boolean playmode, boolean dir, int Xface, int Yface, int Xsize, int Ysize, int frameStart, int frameStop) {
//  static int ms;
//  uint32_t frames = millis();
//  static int frameRate = frameStart;
//
//  //forward play
//  while (dir == 0) {
//    if (++frameRate > frameStop) {
//      frameRate = frameStart;
//      //Serial.println(ms);
//      delay(100);
//      ms = 0;
//    }
//    u8g2.firstPage();
//    do {
//      u8g2.setDrawColor(0);
//      u8g2.drawXBMP( Xface, Yface, Xsize, Ysize, emotions[frameRate]);
//      if (playmode == 1) {
//        u8g2.setFont(u8g2_font_logisoso16_tf);
//        u8g2.setDrawColor(1);
//        u8g2.setCursor(4, 24);
//        u8g2.print(frameRate);
//        u8g2.setCursor(4, 64);
//        u8g2.print(names[currentFrame]);
//        if (playmode == 1 && frameRate == frameStop) {
//          currentFrame = frameStop;
//        }
//      }
//    } while ( u8g2.nextPage() );
//    break;
//  }
//
//  //backward play
//  while (dir == 1) {
//    if (--frameRate < frameStop) {
//
//      frameRate = frameStart;
//      //Serial.println(ms);
//      delay(100);
//      ms = 0;
//    }
//    u8g2.firstPage();
//    do {
//      u8g2.setDrawColor(0);
//      u8g2.drawXBMP( Xface, Yface, Xsize, Ysize, emotions[frameRate]);
//      if (playmode == 1) {
//        //      break;
//        u8g2.setFont(u8g2_font_logisoso16_tf);
//        u8g2.setDrawColor(1);
//        u8g2.setCursor(4, 24);
//        u8g2.print(frameRate);
//        u8g2.setCursor(4, 64);
//        u8g2.print(names[currentFrame]);
//        if (playmode == 1 && frameRate == frameStop) {
//          currentFrame = frameStop;
//        }
//      }
//    } while ( u8g2.nextPage() );
//    break;
//  }
//
//
//  ms += millis() - frames;
//  delay(movieSpeed);
//}
//
//void myEmotionBlock() {
//  if (currentMovie == 0) {
//    //    havas_intro(1, 32, 0, 64, 64, havasbits_frames, 0);
//    myEmotions(0, 0, 0, 0, 128, 64, 0, 30);
//    currentFrame = currentMovie;
//    //    Serial.println(names[currentFrame]);
//  }
//  if (currentMovie == 1) {
//    myEmotions(0, 0, 0, 0, 128, 64, 31, 58);
//    currentFrame = currentMovie;
//    Serial.println(names[currentFrame]);
//  }
//  if (currentMovie == 2) {
//    myEmotions(0, 0, 0, 0, 128, 64, 61, 122);
//    Serial.println(names[currentFrame]);
//    currentFrame = currentMovie;
//  }
//  if (currentMovie == 3) {
//    myEmotions(0, 0, 0, 0, 128, 64, 123, 153);
//    Serial.println(names[currentFrame]);
//    currentFrame = currentMovie;
//  }
//  if (currentMovie == 4) {
//    myEmotions(0, 0, 0, 0, 128, 64, 154, 184);
//    Serial.println(names[currentFrame]);
//    currentFrame = currentMovie;
//  }
//  if (currentMovie == 5) {
//    myEmotions(0, 0, 0, 0, 128, 64, 185, 215);
//    //movie_bit(32, 0, 174, 213);
//    Serial.println(names[currentFrame]);
//    currentFrame = currentMovie;
//  }
//  if (currentMovie == 6) {
//    myEmotions(0, 0, 0, 0, 128, 64, 216, 246);
//    Serial.println(names[currentFrame]);
//    currentFrame = currentMovie;
//  }
//  if (currentMovie == 7) {
//    myEmotions(0, 0, 0, 0, 128, 64, 247, 277);
//    Serial.println(names[currentFrame]);
//    currentFrame = currentMovie;
//  }
//  if (currentMovie == 8) {
//    myEmotions(0, 0, 0, 0, 128, 64, 278, 308);
//    Serial.println(names[currentFrame]);
//    currentFrame = currentMovie;
//  }
//  if (currentMovie == 9) {
//    myEmotions(0, 0, 0, 0, 128, 64, 309, 339);
//    Serial.println(names[currentFrame]);
//    currentFrame = currentMovie;
//  }
//  if (currentMovie == 10) {
//    myEmotions(0, 0, 0, 0, 128, 64, 340, 370);
//    Serial.println(names[currentFrame]);
//    currentFrame = currentMovie;
//  }
//  if (currentMovie == 11) {
//    myEmotions(0, 0, 0, 0, 128, 64, 371, 401);
//    Serial.println(names[currentFrame]);
//    currentFrame = currentMovie;
//    //   movie_10();
//  }
//  if (currentMovie == 12) {
//    myEmotions(0, 0, 0, 0, 128, 64, 402, 432);
//    Serial.println(names[currentFrame]);
//    currentFrame = currentMovie;
//  }
//  if (currentMovie == 13) {
//    myEmotions(0, 0, 0, 0, 128, 64, 433, 463);
//    Serial.println(names[currentFrame]);
//    currentFrame = currentMovie;
//  }
//  if (currentMovie == 14) {
//    myEmotions(0, 0, 0, 0, 128, 64, 464, 494);
//    Serial.println(names[currentFrame]);
//    currentFrame = currentMovie;
//  }
//  if (currentMovie == 15) {
//    myEmotions(0, 0, 0, 0, 128, 64, 495, 525);
//    Serial.println(names[currentFrame]);
//    currentFrame = currentMovie;
//  }
//  if (currentMovie == 16) {
//    myEmotions(0, 0, 0, 0, 128, 64, 526, 556);
//    Serial.println(names[currentFrame]);
//    currentFrame = currentMovie;
//  }
//  if (currentMovie == 17) {
//    myEmotions(0, 0, 0, 0, 128, 64, 557, 586);
//    Serial.println(names[currentFrame]);
//    currentFrame = currentMovie;
//  }
//  if (currentMovie == 18) {
//    myEmotions(0, 0, 0, 0, 128, 64, 0, 586);
//    Serial.println(names[currentFrame]);
//    currentFrame = currentMovie;
//  }
//
//  if (currentMovie == 19) {
//    myEmotions(0, 0, 0, 0, 128, 64, 0, 586);
//    Serial.println(names[currentFrame]);
//    currentFrame = currentMovie;
//  }
//  if (currentMovie == 20) {
//    currentMovie = 0;
//    Serial.println("Reset");
//  }
//
//}
