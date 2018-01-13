# RCSignalProcessor
Mini project for processing standard RC signals on an arduino board, meant to extend functionality of RC models.

# Usage

Main value of this program is in its CppmInput and PwmInput classes, which
read CPPM or PWM inputs from interrupt pins (pins 2 or 3 on Arduino Nano).
This is implemented using interrupts, thus leaving main program loop free to
manage outputs.

To use this program, I suggest that you first uncomment serial debug messages 
and make sure that the program can read input from RC receiver and also to 
make note of values read.

Afterwards, you can comment out the debug messages and  modify main loop to 
your needs. A simple light pattern is pre-programmed.

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
