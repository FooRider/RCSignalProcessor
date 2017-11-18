# RCSignalProcessor
Mini project for processing standard RC signals on an arduino board, meant to extend functionality of RC models.

# Usage
INPUT_CPPM reads CPPM input from INPUT_PIN which needs to support interrupts. 
  Values are saved into values[] array.
  
INPUT_PWM1 can be defined only when INPUT_CPPM is not defined. It reads a single
  RC PWM value on INPUT_PIN which needs to support interrupts and saves it into 
  values[0].
  
INPUT_PWM2 can be defined when INPUT_CPPM is not defined. It reads a single
  RC PWM value on INPUT_PIN2 which needs to support interrupts and saves it into
  values[1].

Since inputs are handled in using interrupts, the main loop is unaffected and
can do almost anything with no regard to timing. You're free to modify the main
loop to fit your needs. (You're also free to modify the signal reading part of 
the program, but at that point you're probabbly better off just starting from
scratch.)

However, there are some useful functions predefined:

## ledOnOff()
  Calling ledOnOff(LED1, GER_IDX); in the main loop ensures basic On-Off 
  functionality on output LED1 (pin 11) controlled from receiver channel 5 (index 4) 
  which to my knowledge corresponds to GEAR channel on Spektrum compatible receivers.
  
## ledPwm()
  Calling ledPwm(LED2, AX1_IDX, DEFAULT_MIN + 100, DEFAULT_MAX - 100) in the main
  loop enables proportional PWM output on output LED2 (pin 9) controlled from
  receiver channel 6 (index 5). Limits DEFAULT_MIN + 100 and DEFAULT_MAX - 100 are
  chosen so that there's some dead space on each end of the input values spectrum
  and the user may reliably turn the channel off or on.

# Licensing
This project is distributed under MIT License

# MIT License

Copyright (c) 2017 Peter Pokojný

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
