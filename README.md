# Basic register machine simulator

#### Very quickly put together for some coursework

## Compilation Instructions

Requires c++11

Compiles with the following 

$ g++ -std=c++11 rmsim.cpp -o rmsim

## To run
square.reg can be run with

`cat square.reg | ./rmsim`

Input file through stdin

-t flag to give a trace of registers

## Explanation of input contents

First line contains the original contents of the registers

### Instruction types & explanations

inc - increments a register 

decjz - If register=0 then jump to a label, else decrement the register 

foo: - Label with name foo at start of a line

Jump to HALT to halt the program

square.reg contains an example of a program.  
