registers 99
#registers 100
#An initial copying of values for the repeated adding
copyloop: decjz r0 haltloop         
inc r1       
inc r2
decjz r4 copyloop
#Use r1 to measure how many times we need to add r0 to itself
haltloop: decjz r1 endsquare 
loop: decjz r2 copy
#Increment r0 by 1x it's initial value
inc r0
inc r3
decjz r4 loop
#Copy r3 back to r2 so we can do the adding again
copy: decjz r3 endcopy
inc r2
decjz r4 copy
endcopy: decjz r4 haltloop
endsquare: decjz r4 HALT