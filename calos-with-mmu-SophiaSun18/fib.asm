# Generate the fibonacci sequence.
# At location 50: number of iterations
# Output starts at 500.
# Assume code is loaded at location 100.
# Temp storage starts at 150.
# update: all locations are modified to 0-based.

__main: 0
# fib1 and fib2 values stored in locations 150, 151
# They start with values 1 and 1.
# update: fib1 and fib2 values are now stored in location 25 and 26.
mov 1 25
mov 1 26

# Output first two fib #s at 500 and 501. Assumes # of iterations > 2.
# update: output now starts at 29, first two fib #s are at 29 and 30.
mov 1 29
mov 1 30
# Store output location in temp storage at 152.
# update: output location is now stored in location 27.
mov 31 27
# Number of iterations left stored in 153, minus 2
# because we hard-code the first 2 numbers.
# update: the number of iterations is now stored at location 28.
mov *50 reg0
sub 2 reg0
mov reg0 28


# LOOP: location 8
mov *28 reg0
# jump to the end
jez reg0 24

mov *25 reg0
mov *26 reg1
# copy 2nd number to reg2
mov reg1 reg2
# add first number
add reg0 reg2
# store 2nd number in first number temp memory
mov reg1 25
# store new number in 2nd number temp memory
mov reg2 26
# load output location into reg0
mov *27 reg0
# write new fib # to output
mov reg2 *reg0
# increment output location
add 1 reg0
mov reg0 27

# Decrement # of iterations left
mov *28 reg2
sub 1 reg2
mov reg2 28
jmp 8 
# END: location 24
end
__data: 100