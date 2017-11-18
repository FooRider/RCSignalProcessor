// Copyright (c) 2017 Peter Pokojný
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

// Usage
// INPUT_CPPM reads CPPM input from INPUT_PIN which needs to support interrupts. 
//   Values are saved into values[] array.
// INPUT_PWM1 can be defined only when INPUT_CPPM is not defined. It reads a single
//   RC PWM value on INPUT_PIN which needs to support interrupts and saves it into 
//   values[0].
// INPUT_PWM2 can be defined when INPUT_CPPM is not defined. It reads a single
//   RC PWM value on INPUT_PIN2 which needs to support interrupts and saves it into
//   values[1].
//
// Since inputs are handled in using interrupts, the main loop is unaffected and
// can do almost anything with no regard to timing. You're free to modify the main
// loop to fit your needs. (You're also free to modify the signal reading part of 
// the program, but at that point you're probabbly better off just starting from
// scratch.)
// However, there are some useful functions predefined:
// ledOnOff()
//   Calling ledOnOff(LED1, GER_IDX); in the main loop ensures basic On-Off 
//   functionality on output LED1 (pin 11) controlled from receiver channel 5 (index 4) 
//   which to my knowledge corresponds to GEAR channel on Spektrum compatible receivers.
// ledPwm()
//   Calling ledPwm(LED2, AX1_IDX, DEFAULT_MIN + 100, DEFAULT_MAX - 100) in the main
//   loop enables proportional PWM output on output LED2 (pin 9) controlled from
//   receiver channel 6 (index 5). Limits DEFAULT_MIN + 100 and DEFAULT_MAX - 100 are
//   chosen so that there's some dead space on each end of the input values spectrum
//   and the user may reliably turn the channel off or on.

//#define DEBUG
#define INPUT_CPPM
//#define INPUT_PWM1
//#define INPUT_PWM2

#include <Servo.h>

#ifdef DEBUG
#include <SoftwareSerial.h>
#endif

// Current pin constants are set for Arduino Nano v3 board. Other boards may use 
// different pinouts, or you may chose another pinout for your project. You just
// need to know what you're doing. INPUT_PIN pin needs to support interrupts,
// if you use INPUT_PWM2, then INPUT_PIN2 needs to support interrupts too.
// If you use Servo outputs or LED PWM outputs, corresponding pins (from LED1, 
// LED2, SERVO1, SERVO2, SERVO3) should support PWM outputs.
#define INPUT_PIN 2
#define LED1 11
#define LED2 9
#define SERVO1 6
#define SERVO2 5
#ifndef INPUT_PWM2
#define SERVO3 3
#else
#define INPUT_PIN2 3
#endif

// Modify following constants to fit your particular transmitter and receiver channels
#define AIL_IDX 0
#define ELE_IDX 1
#define THR_IDX 2
#define RUD_IDX 3
#define GER_IDX 4
#define AX1_IDX 5

#define ONOFF_THRESHOLD 1500
#define DEFAULT_MIN 1000
#define DEFAULT_MAX 2000

#define THR_MIN DEFAULT_MIN
#define THR_MAX DEFAULT_MAX
#define RUD_MIN DEFAULT_MIN
#define RUD_MAX DEFAULT_MAX

volatile int channelIndex = 0;
volatile int maxChannels = 16;
volatile unsigned long values[] = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
#ifdef INPUT_CPPM
volatile unsigned long _lastRiseTime = 0;
#endif
#ifdef INPUT_PWM1
volatile unsigned long _lastPin1RiseTime = 0;
#endif
#ifdef INPUT_PWM2
volatile unsigned long _lastPin2RiseTime = 0;
#endif

Servo servo1;
Servo servo2;
#ifndef INPUT_PWM2
Servo servo3;
#endif

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  servo1.attach(SERVO1, RUD_MIN, RUD_MAX);
  servo2.attach(SERVO2, THR_MIN, THR_MAX);
#ifndef INPUT_PWM2
  servo3.attach(SERVO3, THR_MIN, THR_MAX);
#endif

#ifdef INPUT_CPPM
  pinMode(INPUT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INPUT_PIN), inputPinChanged, CHANGE);
#endif

#ifdef INPUT_PWM1
  pinMode(INPUT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INPUT_PIN), inputPin1Changed, CHANGE);
#endif

#ifdef INPUT_PWM2
  pinMode(INPUT_PIN2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INPUT_PIN2), inputPin2Changed, CHANGE);
#endif

#ifdef DEBUG
  Serial.begin(57600);
  while (!Serial) { }
  Serial.println("Serial initialized!");
#endif
}

void loop() {
  // gear RC channel controls output LED channel 1
  ledOnOff(LED1, GER_IDX);
  
  // aux1 RC channel controls output LED channel 2 with PWM, use 100us dead space on both ends to ensure fully OFF and fully ON states.
  ledPwm(LED2, AX1_IDX, DEFAULT_MIN + 100, DEFAULT_MAX - 100);

  
  
#ifdef DEBUG
  printInputChannels();
#endif
}

void ledOnOff(int pin, int valueIdx) {
  if (values[valueIdx] > ONOFF_THRESHOLD)
    digitalWrite(pin, HIGH);
  else
    digitalWrite(pin, LOW);
}

void ledPwm(int pin, int valueIdx, int minUs, int maxUs) {
  int pwmValue = map(values[valueIdx], minUs, maxUs, 0, 255);
  if (pwmValue < 0) pwmValue = 0;
  if (pwmValue > 255) pwmValue = 255;
  analogWrite(pin, pwmValue);
}

void printInputChannels() {
#ifdef DEBUG
  for (int i = 0; i < maxChannels; i++) {
    if (values[i] == 0)
      break;
    Serial.print(values[i]);
    Serial.print("\t");
  }
  Serial.println();
#endif
}

#ifdef INPUT_CPPM
void inputPinChanged() {
  unsigned long time = micros(); // save current time
  int val = digitalRead(INPUT_PIN); // determine whether slope is rising or falling
  if (val == HIGH) {
    if (time - _lastRiseTime > 5000) { // if high time was longer than 5ms, we're reading next iteration of values
      for (int i = channelIndex; i < maxChannels; i++)
        values[i] = 0;
      channelIndex = 0;
    }
    _lastRiseTime = time;
  }
  else {
    if (channelIndex >= maxChannels)
      return;
    
    unsigned long highTime = time - _lastRiseTime;

    if (highTime > 3000)
      return;
    
    values[channelIndex] = highTime;
    channelIndex++;
  }
}
#endif

#ifdef INPUT_PWM1
void inputPin1Changed() {
  unsigned long time = micros(); // save current time
  int val = digitalRead(INPUT_PIN); // determine whether slope is rising or falling
  if (val == HIGH)
    _lastPin1RiseTime = time;
  else
    values[0] = time - _lastPin1RiseTime;
}
#endif

#ifdef INPUT_PWM2
void inputPin2Changed() {
  unsigned long time = micros(); // save current time
  int val = digitalRead(INPUT_PIN2); // determine whether slope is rising or falling
  if (val == HIGH)
    _lastPin2RiseTime = time;
  else
    values[1] = time - _lastPin2RiseTime;
}
#endif
