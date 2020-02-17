# Basic register machine simulator

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

Jump to HALT to halt the program

square.reg contains an example of a program.  
