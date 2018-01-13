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

#include <Arduino.h>
#include "PwmInput.h"

PwmInput *PwmInput::interruptListener1 = NULL;
PwmInput *PwmInput::interruptListener2 = NULL;
PwmInput *PwmInput::interruptListener3 = NULL;
PwmInput *PwmInput::interruptListener4 = NULL;
PwmInput *PwmInput::interruptListener5 = NULL;
PwmInput *PwmInput::interruptListener6 = NULL;
PwmInput *PwmInput::interruptListener7 = NULL;
PwmInput *PwmInput::interruptListener8 = NULL;
PwmInput *PwmInput::interruptListener9 = NULL;
PwmInput *PwmInput::interruptListener10 = NULL;
PwmInput *PwmInput::interruptListener11 = NULL;
PwmInput *PwmInput::interruptListener12 = NULL;
PwmInput *PwmInput::interruptListener13 = NULL;
PwmInput *PwmInput::interruptListener14 = NULL;
PwmInput *PwmInput::interruptListener15 = NULL;
PwmInput *PwmInput::interruptListener16 = NULL;
PwmInput *PwmInput::interruptListener17 = NULL;
PwmInput *PwmInput::interruptListener18 = NULL;
PwmInput *PwmInput::interruptListener19 = NULL;
PwmInput *PwmInput::interruptListener20 = NULL;

void PwmInput::initialize(int pin) {
  this->inputPin = pin;
  pinMode(pin, INPUT_PULLUP);

  // interrupt to non-static member hack follows
  switch (pin) {
    case 1: interruptListener1 = this; attachInterrupt(digitalPinToInterrupt(pin), PwmInput::interrupt1, CHANGE); break;
    case 2: interruptListener2 = this; attachInterrupt(digitalPinToInterrupt(pin), PwmInput::interrupt2, CHANGE); break;
    case 3: interruptListener3 = this; attachInterrupt(digitalPinToInterrupt(pin), PwmInput::interrupt3, CHANGE); break;
    case 4: interruptListener4 = this; attachInterrupt(digitalPinToInterrupt(pin), PwmInput::interrupt4, CHANGE); break;
    case 5: interruptListener5 = this; attachInterrupt(digitalPinToInterrupt(pin), PwmInput::interrupt5, CHANGE); break;
    case 6: interruptListener6 = this; attachInterrupt(digitalPinToInterrupt(pin), PwmInput::interrupt6, CHANGE); break;
    case 7: interruptListener7 = this; attachInterrupt(digitalPinToInterrupt(pin), PwmInput::interrupt7, CHANGE); break;
    case 8: interruptListener8 = this; attachInterrupt(digitalPinToInterrupt(pin), PwmInput::interrupt8, CHANGE); break;
    case 9: interruptListener9 = this; attachInterrupt(digitalPinToInterrupt(pin), PwmInput::interrupt9, CHANGE); break;
    case 10: interruptListener10 = this; attachInterrupt(digitalPinToInterrupt(pin), PwmInput::interrupt10, CHANGE); break;
    case 11: interruptListener11 = this; attachInterrupt(digitalPinToInterrupt(pin), PwmInput::interrupt11, CHANGE); break;
    case 12: interruptListener12 = this; attachInterrupt(digitalPinToInterrupt(pin), PwmInput::interrupt12, CHANGE); break;
    case 13: interruptListener13 = this; attachInterrupt(digitalPinToInterrupt(pin), PwmInput::interrupt13, CHANGE); break;
    case 14: interruptListener14 = this; attachInterrupt(digitalPinToInterrupt(pin), PwmInput::interrupt14, CHANGE); break;
    case 15: interruptListener15 = this; attachInterrupt(digitalPinToInterrupt(pin), PwmInput::interrupt15, CHANGE); break;
    case 16: interruptListener16 = this; attachInterrupt(digitalPinToInterrupt(pin), PwmInput::interrupt16, CHANGE); break;
    case 17: interruptListener17 = this; attachInterrupt(digitalPinToInterrupt(pin), PwmInput::interrupt17, CHANGE); break;
    case 18: interruptListener18 = this; attachInterrupt(digitalPinToInterrupt(pin), PwmInput::interrupt18, CHANGE); break;
    case 19: interruptListener19 = this; attachInterrupt(digitalPinToInterrupt(pin), PwmInput::interrupt19, CHANGE); break;
    case 20: interruptListener20 = this; attachInterrupt(digitalPinToInterrupt(pin), PwmInput::interrupt20, CHANGE); break;
  }
};

long PwmInput::getRawValue(int idx) {
  return this->value;
};

float PwmInput::getValue(int idx) {
  return this->value;
};

void PwmInput::inputPinChanged() {
  unsigned long time = micros(); // save current time
  int val = digitalRead(this->inputPin);
  if (val == HIGH)
    this->lastRiseTime = time;
  else
    this->value = time - this->lastRiseTime;
};

void PwmInput::interrupt1() { interruptListener1->inputPinChanged(); };
void PwmInput::interrupt2() { interruptListener2->inputPinChanged(); };
void PwmInput::interrupt3() { interruptListener3->inputPinChanged(); };
void PwmInput::interrupt4() { interruptListener4->inputPinChanged(); };
void PwmInput::interrupt5() { interruptListener5->inputPinChanged(); };
void PwmInput::interrupt6() { interruptListener6->inputPinChanged(); };
void PwmInput::interrupt7() { interruptListener7->inputPinChanged(); };
void PwmInput::interrupt8() { interruptListener8->inputPinChanged(); };
void PwmInput::interrupt9() { interruptListener9->inputPinChanged(); };
void PwmInput::interrupt10() { interruptListener10->inputPinChanged(); };
void PwmInput::interrupt11() { interruptListener11->inputPinChanged(); };
void PwmInput::interrupt12() { interruptListener12->inputPinChanged(); };
void PwmInput::interrupt13() { interruptListener13->inputPinChanged(); };
void PwmInput::interrupt14() { interruptListener14->inputPinChanged(); };
void PwmInput::interrupt15() { interruptListener15->inputPinChanged(); };
void PwmInput::interrupt16() { interruptListener16->inputPinChanged(); };
void PwmInput::interrupt17() { interruptListener17->inputPinChanged(); };
void PwmInput::interrupt18() { interruptListener18->inputPinChanged(); };
void PwmInput::interrupt19() { interruptListener19->inputPinChanged(); };
void PwmInput::interrupt20() { interruptListener20->inputPinChanged(); };
