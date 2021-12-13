# Binary Diagnostic
Binary numbers are always fun to play with from a programmers perspective.  
When you see binary numbers and you know they want a decimal answer, you can be almost certain you will need a function to convert binaries to integers. And luckily they did not take negative numbers into account, resulting in less complexity when dealing with binary numbers.

### What do we need to do?
Well, the input is a bunch of binary numbers (`0`s and `1`s). Don't be tempted to read your input as integers, as it will discard all leading zeros. So we read our input as strings (and using the word "stop" as input to signal the program we're done inputting the binaries).
Each binary number is stored just as a string in a vector.  
Then we create a vector of integers to store the count of each digit and iterate over the different strings incrementing the digit count for every `1` we encounter for each position. We initialize each value in the vector to zero.  
Because `0` doesn't increment the value, we can see afterwards from the sum whether `1` or `0` occurred the most (most significant bit), so there is no need to count both zeros and ones. If the total is greater than or equal to half the number of binaries, ones will be most significant, zeros otherwise.
So by determining the most significant bit this way and creating a new binary as provided in their example, we get a new binary number that represents our `gamma rate`.

The function for converting this binary to a decimal number is named `BinaryToNumber` in the program. The magic is done by appending a digit to a number that was initialized to zero. By doing an `OR` we get a 1 if the digit is a one, a zero otherwise. Then we shift the resulting number to the left making room for the next digit.

You could expect that finding the least significant bit the same way we did for the most significant one should be our next step.  
But hold on. Because it is a binary, the result of finding the least significant bits will just lead to the inverse of the previous result. So we could do this a lot shorter by just inverting the `gamma rate` to find the `epsilon rate`. This can simply be done by the tilde character in C++.
This creates another problem though: the size of the number we are working with is at least 1 byte (8 bits), but our range of bits is shorter. Therefore, under the hood the number is padded to the left with zeros, which will all become ones when inverted. Somehow we have to cancel out the leading ones. This can be done by creating a number that is all ones for just the length of our string with bits. This is done by the `ones` function. Then performing an `AND` operation between this number and our inverted result (this should only keep the ones that occur at exactly the same position in both numbers).
Then we finally have our `epsilon rate`.

The procedure for part 2 is comparable, so the program was only changed at a few points and two new functions were introduced for iterating over a vector to keep or discard the ones containing the most significant bit at an indicated position.