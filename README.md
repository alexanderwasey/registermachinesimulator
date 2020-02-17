Basic register machine simulator

Requires c++11
Compilesc with the following 

$ g++ -std=c++11 rmsim.cpp -o rmsim

square.r can be run with
$ cat square.r | ./rmsim

inc - increments a register 

decjz - If register=0 then jump, else decrement the register 

Jump to HALT to halt the program

square.r contains an example of a program.  
