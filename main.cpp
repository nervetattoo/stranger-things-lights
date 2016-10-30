/*
 * This is a RGB+W NeoPixel example, see extra-examples.cpp for a version
 * with more explantory documentation, example routines, how to
 * hook up your pixels and all of the pixel types that are supported.
 *
 */

/* ======================= includes ================================= */

#include "application.h"

#include <algorithm>
#include <iterator>
#include <list>

#include "neopixel.h"

/* ======================= prototypes =============================== */

/* ======================= rgbw-strandtest.cpp ====================== */

SYSTEM_MODE(AUTOMATIC);

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D2
#define PIXEL_COUNT 60
#define PIXEL_TYPE WS2812B
#define BRIGHTNESS 100 // 0 - 255

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

std::list<int> leds;
int queue = 0;
uint32_t blank = strip.Color(0,0,0, 0);
int wait = 1000;

int color() {
  int r = rand() % 255;
  int g = rand() % 255;
  int b = rand() % 255;
  return strip.Color(r, g, b, 255);
}

int indexForChar(char c) {
  String s = (String) c;

  if (strcmp(s, "a") == 0) {
    return 0;
  } else if (strcmp(s, "b") == 0) {
    return 1;
  } else if (strcmp(s, "c") == 0) {
    return 2;
  } else if (strcmp(s, "d") == 0) {
    return 3;
  } else if (strcmp(s, "e") == 0) {
    return 4;
  } else if (strcmp(s, "f") == 0) {
    return 5;
  } else if (strcmp(s, "g") == 0) {
    return 6;
  } else if (strcmp(s, "h") == 0) {
    return 7;
  } else if (strcmp(s, "i") == 0) {
    return 8;
  } else if (strcmp(s, "j") == 0) {
    return 18;
  } else if (strcmp(s, "k") == 0) {
    return 17;
  } else if (strcmp(s, "l") == 0) {
    return 16;
  } else if (strcmp(s, "m") == 0) {
    return 15;
  } else if (strcmp(s, "n") == 0) {
    return 14;
  } else if (strcmp(s, "o") == 0) {
    return 13;
  } else if (strcmp(s, "p") == 0) {
    return 12;
  } else if (strcmp(s, "q") == 0) {
    return 11;
  } else if (strcmp(s, "r") == 0) {
    return 10;
  } else if (strcmp(s, "s") == 0) {
    return 9;
  } else if (strcmp(s, "t") == 0) {
    return 19;
  } else if (strcmp(s, "u") == 0) {
    return 20;
  } else if (strcmp(s, "v") == 0) {
    return 21;
  } else if (strcmp(s, "w") == 0) {
    return 22;
  } else if (strcmp(s, "x") == 0) {
    return 23;
  } else if (strcmp(s, "y") == 0) {
    return 24;
  } else if (strcmp(s, "z") == 0) {
    return 25;
  }

  return -1;
}

int pushCharCodes(String codes) {
  codes.trim();
  codes.toLowerCase();
  int len = codes.length();

  leds.push_back(-1);
  for (int i = 0; i<len; i++) {
    char c = codes.charAt(i);
    int pos = indexForChar(c);
    leds.push_back(pos);
  }
  leds.push_back(-1);

  queue = leds.size();

  return 1;
}


void setup() {
  Particle.function("display", pushCharCodes);

  leds.push_back(9);

  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show();
}

int current;
void loop() {
  // Print current letter
  queue = leds.size();
  if (!leds.empty()) {
    current = leds.front();
    leds.pop_front();
    for(int i=0; i<strip.numPixels(); i++) {
      if (i == current) {
        strip.setPixelColor(i, color());
      } else {
        strip.setPixelColor(i, blank);
      }
    }
  } else {
    for(int i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, blank);
    }
  }

  strip.show();
  delay(wait);
}
