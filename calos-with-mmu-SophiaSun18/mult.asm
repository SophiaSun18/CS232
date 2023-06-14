# Multiply two numbers, found in locations 10 and 11, leaving the result in location 12.
# Assumes this code is loaded at location 20.
# update: the two numbers are now found in location 32 and 33, result in location 34.
# update: all locations are modified to 0-based - values are at 12 and 13, result at 14.

__main: 0
mov 0 14
mov *12 reg2
jez reg2 11
mov *13 reg1
jez reg1 11
mov reg2 reg0
sub 1 reg1
jez reg1 10
add reg0 reg2
jmp 6
mov reg2 14
end
__data: 3