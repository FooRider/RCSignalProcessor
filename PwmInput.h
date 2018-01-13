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

#include "Input.h"

#ifndef PWMINPUT_H
#define PWMINPUT_H

class PwmInput : public Input {
private:
  int inputPin;

  volatile unsigned long value;
  volatile unsigned long lastRiseTime;

  void inputPinChanged();

public:
  // interrupt to non-static member hack follows
  static PwmInput *interruptListener1;
  static PwmInput *interruptListener2;
  static PwmInput *interruptListener3;
  static PwmInput *interruptListener4;
  static PwmInput *interruptListener5;
  static PwmInput *interruptListener6;
  static PwmInput *interruptListener7;
  static PwmInput *interruptListener8;
  static PwmInput *interruptListener9;
  static PwmInput *interruptListener10;
  static PwmInput *interruptListener11;
  static PwmInput *interruptListener12;
  static PwmInput *interruptListener13;
  static PwmInput *interruptListener14;
  static PwmInput *interruptListener15;
  static PwmInput *interruptListener16;
  static PwmInput *interruptListener17;
  static PwmInput *interruptListener18;
  static PwmInput *interruptListener19;
  static PwmInput *interruptListener20;
  static void interrupt1();
  static void interrupt2();
  static void interrupt3();
  static void interrupt4();
  static void interrupt5();
  static void interrupt6();
  static void interrupt7();
  static void interrupt8();
  static void interrupt9();
  static void interrupt10();
  static void interrupt11();
  static void interrupt12();
  static void interrupt13();
  static void interrupt14();
  static void interrupt15();
  static void interrupt16();
  static void interrupt17();
  static void interrupt18();
  static void interrupt19();
  static void interrupt20();
  
public:
  virtual void initialize(int pin);
  virtual long getRawValue(int idx);
  virtual float getValue(int idx);
};

#endif
