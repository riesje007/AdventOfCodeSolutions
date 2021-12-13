# Seven Segment Search
A digital number display showing bogus values, because the connections have been mixed up.
This was a neat problem to solve.  

The first part was rather simple: just find the number of appearances of strings with a length of 2, 3, 4, or 7 in a bunch of strings as input. 
Only the input was a bit more complex than in previous problems, as can be seen from the while loop that processes input, which occupies most of the lines of the program.


## Part 2
In part two the challenge is twofold: first you have to figure out how to determine which letter corresponds to which segments and convert letter sequences to digits, **then** you need to figure out how to make a program do that.  
I did not go for the shortest code, but instead created some helpers to get from wrong letter sequences to correct digits.  
First I created a `vector` containing values per letter such that when you sum up these letter values from a sequence of letters belonging to a digit, you would get a unique new value.  
For example, consider the following digits being represented by the indicated letter sequence (this sequence indicates the segments involved for displaying the digit):  
- Digit 0: `abcefg`
- Digit 1: `cf`
- Digit 2: `acdeg`
- Digit 3: `acdfg`
- Digit 4: `bcdf`
- Digit 5: `abdfg`
- Digit 6: `abdefg`
- Digit 7: `acf`
- Digit 8: `abcdefg`
- Digit 9: `abcdfg`

By assigning a value to each letter, e.g. a = 1, b = 2, and so on, but instead of assigning 5 as value to e assign a really different value, such as e = 11. This way sums will result in unique values per digit (shown in brackets):  
- Digit 0: `abcefg` (30)
- Digit 1: `cf` (9)
- Digit 2: `acdeg` (26)
- Digit 3: `acdfg` (21)
- Digit 4: `bcdf` (15)
- Digit 5: `abdfg` (20)
- Digit 6: `abdefg` (31)
- Digit 7: `acf` (10)
- Digit 8: `abcdefg` (34)
- Digit 9: `abcdfg` (23)

Then I created a map that maps these values right onto their corresponding digits (called `Digits`).
Then, per input line, the program determines a character decoding map (resulting in a filled `CharDecodingMap`) that maps wrong letters to the correct counterparts. From this `CharDecodingMap` it can convert the wrong letters from the "output digits" part of the input (the part behind the pipe character) to the correct sequence of letters and then finally convert this new character sequence to the correct digit using the `Digits` map.
