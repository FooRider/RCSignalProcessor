#define DEBUG 1

#include <Servo.h>

#if DEBUG
#include <SoftwareSerial.h>
#endif

#define INPUT_PIN 2
#define LED1 11
#define LED2 9
#define SERVO1 3
#define SERVO2 5
#define SERVO3 6

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
volatile unsigned long _lastRiseTime = 0;

Servo servo1;
Servo servo2;
Servo servo3;

void setup() {
  pinMode(INPUT_PIN, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  servo1.attach(SERVO1, RUD_MIN, RUD_MAX);
  servo2.attach(SERVO2, THR_MIN, THR_MAX);
  servo3.attach(SERVO3, THR_MIN, THR_MAX);

  attachInterrupt(digitalPinToInterrupt(INPUT_PIN), inputPinChanged, CHANGE);

#if DEBUG
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

  
  
#if DEBUG
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
#if DEBUG
  for (int i = 0; i < maxChannels; i++) {
    if (values[i] == 0)
      break;
    Serial.print(values[i]);
    Serial.print("\t");
  }
  Serial.println();
#endif
}

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
