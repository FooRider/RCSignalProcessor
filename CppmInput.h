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

#ifndef CPPMINPUT_H
#define CPPMINPUT_H

#include "Input.h"

class CppmInput : public Input {
private:
  volatile int channelIndex = 0;
  volatile int maxChannels = 16;
  volatile unsigned long values[16] {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
  volatile unsigned long lastRiseTime = 0;

  int inputPin;

  void inputPinChanged();

public:
  // interrupt to non-static member hack follows
  static int interruptCounter;
  static CppmInput *interruptListeners[];

  static void interrupt0();
  static void interrupt1();
  
  /*static CppmInput *interruptListener1;
  static CppmInput *interruptListener2;
  static CppmInput *interruptListener3;
  static CppmInput *interruptListener4;
  static CppmInput *interruptListener5;
  static CppmInput *interruptListener6;
  static CppmInput *interruptListener7;
  static CppmInput *interruptListener8;
  static CppmInput *interruptListener9;
  static CppmInput *interruptListener10;
  static CppmInput *interruptListener11;
  static CppmInput *interruptListener12;
  static CppmInput *interruptListener13;
  static CppmInput *interruptListener14;
  static CppmInput *interruptListener15;
  static CppmInput *interruptListener16;
  static CppmInput *interruptListener17;
  static CppmInput *interruptListener18;
  static CppmInput *interruptListener19;
  static CppmInput *interruptListener20;
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
  static void interrupt20();*/
  
public:
  virtual void initialize(int pin);
  virtual long getRawValue(int idx);
  virtual float getValue(int idx);
};



#endif
