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

static int PwmInput::interruptCounter = 0;
static PwmInput *PwmInput::interruptListeners[2] { NULL, NULL };

void PwmInput::initialize(int pin) {
  this->inputPin = pin;
  pinMode(pin, INPUT_PULLUP);

  // interrupt to non-static member hack follows
  PwmInput::interruptListeners[PwmInput::interruptCounter] = this;
  switch (PwmInput::interruptCounter)
  {
    case 0: attachInterrupt(digitalPinToInterrupt(pin), PwmInput::interrupt0, CHANGE); break;
    case 1: attachInterrupt(digitalPinToInterrupt(pin), PwmInput::interrupt1, CHANGE); break;
  }
  PwmInput::interruptCounter++;
};

long PwmInput::getValue(int idx) {
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

void PwmInput::interrupt0() { PwmInput::interruptListeners[0]->inputPinChanged(); };
void PwmInput::interrupt1() { PwmInput::interruptListeners[1]->inputPinChanged(); };
