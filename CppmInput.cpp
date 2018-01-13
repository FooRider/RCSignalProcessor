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

#include "CppmInput.h"

static int CppmInput::interruptCounter = 0;
static CppmInput *CppmInput::interruptListeners[2] { NULL, NULL };

/*
static CppmInput *CppmInput::interruptListener1 = NULL;
static CppmInput *CppmInput::interruptListener2 = NULL;
static CppmInput *CppmInput::interruptListener3 = NULL;
static CppmInput *CppmInput::interruptListener4 = NULL;
static CppmInput *CppmInput::interruptListener5 = NULL;
static CppmInput *CppmInput::interruptListener6 = NULL;
static CppmInput *CppmInput::interruptListener7 = NULL;
static CppmInput *CppmInput::interruptListener8 = NULL;
static CppmInput *CppmInput::interruptListener9 = NULL;
static CppmInput *CppmInput::interruptListener10 = NULL;
static CppmInput *CppmInput::interruptListener11 = NULL;
static CppmInput *CppmInput::interruptListener12 = NULL;
static CppmInput *CppmInput::interruptListener13 = NULL;
static CppmInput *CppmInput::interruptListener14 = NULL;
static CppmInput *CppmInput::interruptListener15 = NULL;
static CppmInput *CppmInput::interruptListener16 = NULL;
static CppmInput *CppmInput::interruptListener17 = NULL;
static CppmInput *CppmInput::interruptListener18 = NULL;
static CppmInput *CppmInput::interruptListener19 = NULL;
static CppmInput *CppmInput::interruptListener20 = NULL;*/


void CppmInput::initialize(int pin) {
  this->inputPin = pin;
  pinMode(pin, INPUT_PULLUP);

  // interrupt to non-static member hack follows
  CppmInput::interruptListeners[CppmInput::interruptCounter++] = this;
  
  /*
  switch (pin) {
    case 1: CppmInput::interruptListener1 = this; attachInterrupt(digitalPinToInterrupt(pin), CppmInput::interrupt1, CHANGE); break;
    case 2: CppmInput::interruptListener2 = this; attachInterrupt(digitalPinToInterrupt(pin), CppmInput::interrupt2, CHANGE); break;
    case 3: CppmInput::interruptListener3 = this; attachInterrupt(digitalPinToInterrupt(pin), CppmInput::interrupt3, CHANGE); break;
    case 4: CppmInput::interruptListener4 = this; attachInterrupt(digitalPinToInterrupt(pin), CppmInput::interrupt4, CHANGE); break;
    case 5: CppmInput::interruptListener5 = this; attachInterrupt(digitalPinToInterrupt(pin), CppmInput::interrupt5, CHANGE); break;
    case 6: CppmInput::interruptListener6 = this; attachInterrupt(digitalPinToInterrupt(pin), CppmInput::interrupt6, CHANGE); break;
    case 7: CppmInput::interruptListener7 = this; attachInterrupt(digitalPinToInterrupt(pin), CppmInput::interrupt7, CHANGE); break;
    case 8: CppmInput::interruptListener8 = this; attachInterrupt(digitalPinToInterrupt(pin), CppmInput::interrupt8, CHANGE); break;
    case 9: CppmInput::interruptListener9 = this; attachInterrupt(digitalPinToInterrupt(pin), CppmInput::interrupt9, CHANGE); break;
    case 10: CppmInput::interruptListener10 = this; attachInterrupt(digitalPinToInterrupt(pin), CppmInput::interrupt10, CHANGE); break;
    case 11: CppmInput::interruptListener11 = this; attachInterrupt(digitalPinToInterrupt(pin), CppmInput::interrupt11, CHANGE); break;
    case 12: CppmInput::interruptListener12 = this; attachInterrupt(digitalPinToInterrupt(pin), CppmInput::interrupt12, CHANGE); break;
    case 13: CppmInput::interruptListener13 = this; attachInterrupt(digitalPinToInterrupt(pin), CppmInput::interrupt13, CHANGE); break;
    case 14: CppmInput::interruptListener14 = this; attachInterrupt(digitalPinToInterrupt(pin), CppmInput::interrupt14, CHANGE); break;
    case 15: CppmInput::interruptListener15 = this; attachInterrupt(digitalPinToInterrupt(pin), CppmInput::interrupt15, CHANGE); break;
    case 16: CppmInput::interruptListener16 = this; attachInterrupt(digitalPinToInterrupt(pin), CppmInput::interrupt16, CHANGE); break;
    case 17: CppmInput::interruptListener17 = this; attachInterrupt(digitalPinToInterrupt(pin), CppmInput::interrupt17, CHANGE); break;
    case 18: CppmInput::interruptListener18 = this; attachInterrupt(digitalPinToInterrupt(pin), CppmInput::interrupt18, CHANGE); break;
    case 19: CppmInput::interruptListener19 = this; attachInterrupt(digitalPinToInterrupt(pin), CppmInput::interrupt19, CHANGE); break;
    case 20: CppmInput::interruptListener20 = this; attachInterrupt(digitalPinToInterrupt(pin), CppmInput::interrupt20, CHANGE); break;
  }*/
};

long CppmInput::getRawValue(int idx) {
  return 0;
};

float CppmInput::getValue(int idx) {
  return 0;
};

void CppmInput::inputPinChanged() {
  unsigned long time = micros(); // save current time
  int val = digitalRead(inputPin);
  if (val == HIGH) {
    if (time - this->lastRiseTime > 5000) { // if high time was longer than 5ms, we're reading next iteration of values
      for (int i = this->channelIndex; i < this->maxChannels; i++)
        this->values[i] = 0;
      this->channelIndex = 0;
    }
    this->lastRiseTime = time;
  }
  else {
    if (this->channelIndex >= this->maxChannels)
      return;

    unsigned long highTime = time - this->lastRiseTime;

    if (highTime > 3000)
      return;

    this->values[this->channelIndex] = highTime;
    this->channelIndex++;
  }
};

// interrupt to non-static member hack follows
void CppmInput::interrupt0() { interruptListeners[0]->inputPinChanged(); };
void CppmInput::interrupt1() { interruptListeners[1]->inputPinChanged(); };

/*
void CppmInput::interrupt1() { interruptListener1->inputPinChanged(); };
void CppmInput::interrupt2() { interruptListener2->inputPinChanged(); };
void CppmInput::interrupt3() { interruptListener3->inputPinChanged(); };
void CppmInput::interrupt4() { interruptListener4->inputPinChanged(); };
void CppmInput::interrupt5() { interruptListener5->inputPinChanged(); };
void CppmInput::interrupt6() { interruptListener6->inputPinChanged(); };
void CppmInput::interrupt7() { interruptListener7->inputPinChanged(); };
void CppmInput::interrupt8() { interruptListener8->inputPinChanged(); };
void CppmInput::interrupt9() { interruptListener9->inputPinChanged(); };
void CppmInput::interrupt10() { interruptListener10->inputPinChanged(); };
void CppmInput::interrupt11() { interruptListener11->inputPinChanged(); };
void CppmInput::interrupt12() { interruptListener12->inputPinChanged(); };
void CppmInput::interrupt13() { interruptListener13->inputPinChanged(); };
void CppmInput::interrupt14() { interruptListener14->inputPinChanged(); };
void CppmInput::interrupt15() { interruptListener15->inputPinChanged(); };
void CppmInput::interrupt16() { interruptListener16->inputPinChanged(); };
void CppmInput::interrupt17() { interruptListener17->inputPinChanged(); };
void CppmInput::interrupt18() { interruptListener18->inputPinChanged(); };
void CppmInput::interrupt19() { interruptListener19->inputPinChanged(); };
void CppmInput::interrupt20() { interruptListener20->inputPinChanged(); };*/
