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
#include "CppmInput.h"

static int CppmInput::interruptCounter = 0;
static CppmInput *CppmInput::interruptListeners[2] { NULL, NULL };

void CppmInput::initialize(int pin) {
  this->inputPin = pin;
  pinMode(pin, INPUT_PULLUP);

  // interrupt to non-static member hack follows
  CppmInput::interruptListeners[CppmInput::interruptCounter] = this;
  switch (CppmInput::interruptCounter) {
    case 0: attachInterrupt(digitalPinToInterrupt(pin), CppmInput::interrupt0, CHANGE); break;
    case 1: attachInterrupt(digitalPinToInterrupt(pin), CppmInput::interrupt1, CHANGE); break;
  }
  CppmInput::interruptCounter++;
};

long CppmInput::getValue(int idx) {
  return this->values[idx];
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
