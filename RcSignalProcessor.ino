#include <SoftwareSerial.h>

#define INPUT_PIN 2

volatile int channelIndex = 0;
volatile int maxChannels = 16;
volatile unsigned long values[] = {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0};
volatile unsigned long _lastRiseTime = 0;

void setup() {
  pinMode(INPUT_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(INPUT_PIN), inputPinChanged, CHANGE);

  Serial.begin(57600);
  while (!Serial) { ; }
  Serial.println("Hello world!");
}

void inputPinChanged()
{
  unsigned long time = micros();
  int val = digitalRead(INPUT_PIN);
  if (val == HIGH)
  {
    if (time - _lastRiseTime > 5000) 
    {
      for (int i = channelIndex; i < maxChannels; i++)
        values[i] = 0;
      channelIndex = 0;
    }
    _lastRiseTime = time;
  }
  else
  {
    if (channelIndex >= maxChannels)
      return;
    
    unsigned long highTime = time - _lastRiseTime;

    if (highTime > 3000)
      return;
    
    values[channelIndex] = highTime;
    channelIndex++;
  }
}

void loop() {
  for (int i = 0; i < maxChannels; i++) 
  {
    if (values[i] == 0)
      break;
    Serial.print(values[i]);
    Serial.print("\t");
  }
  Serial.println();
  
  delay(100);
}
