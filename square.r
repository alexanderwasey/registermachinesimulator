#First line comment - just because
registers 10
#An initial copying of values for the repeated adding
copyloop: decjz r0 haltloop
inc r1
inc r2
decjz r4 copyloop
haltloop: decjz r1 endsquare 
loop: decjz r2 copy
inc r0
inc r3
decjz r4 loop
copy: decjz r3 endcopy
inc r2
decjz r4 copy
endcopy: decjz r4 haltloop
endsquare: decjz r4 HALT