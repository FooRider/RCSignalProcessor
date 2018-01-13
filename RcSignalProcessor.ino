// Copyright (c) 2018 Peter Pokojný
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

//#include <SoftwareSerial.h>
#include "CppmInput.h"
#include "PwmInput.h"
#include "SimpleLight.h"

CppmInput input;
//PwmInput input;

SimpleLight landingLights;
SimpleLight navigationalLights;
SimpleLight topBeacon;
SimpleLight strobes;

void setup() {
  input.initialize(2); // read input on pin 2
  
  landingLights.initialize(11);     // landing lights on pin 11
  navigationalLights.initialize(9); // nav lights on pin 9
  strobes.initialize(6);            // strobes on pin 6
  topBeacon.initialize(5);          // top beacon on pin 5
  
  //Serial.begin(57600);  while (!Serial) { }  Serial.println("Serial initialized!");
};

void loop() {
  long val = input.getValue(4);

  long phase = millis() % 1000;

  if (val < 1000) { // low 
    landingLights.off();
    navigationalLights.on();
    strobes.set((phase >= 0 && phase < 100) || (phase >= 200 && phase < 300));
    topBeacon.set(phase >= 600 && phase < 750);
  }
  else if (val < 1400) { // mid 
    landingLights.on();
    navigationalLights.on();
    strobes.set((phase >= 0 && phase < 100) || (phase >= 200 && phase < 300));
    topBeacon.set(phase >= 400 && phase < 550);
  }
  else { // high 
    landingLights.off();
    navigationalLights.off();
    strobes.off();
    topBeacon.off();
  }

  //delay(1000); Serial.print("0  "); Serial.println(input.getValue(0));  Serial.print("1  "); Serial.println(input.getValue(1));  Serial.print("2  "); Serial.println(input.getValue(2));  Serial.print("3  "); Serial.println(input.getValue(3));  Serial.print("4  "); Serial.println(input.getValue(4));  Serial.print("5  "); Serial.println(input.getValue(5)); Serial.println();
};


