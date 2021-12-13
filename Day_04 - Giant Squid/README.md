# Giant Squid
So I have to calculate the score of the first winning board in a bingo game. The score is calculated as the sum of the remaining numbers on that board.  
Since I assumed that all numbers on a board are unique (it was not stated anywher), I created a small check function `CheckBoard` to check this is actually the case, just to be sure my assumption was correct. (Otherwise, the program might come up with both the wrong board as the first winner and a wrong score.)  

The program starts off by reading numbers from lines of input.  
First one line of input is read to get all the draws. This line of input is read by `getline`, so we can detect empty lines (`cin` doesn't detect that, it keeps asking for input in that case). Each line is wrapped in an `istringstream` object and then parsed for the numbers in the same way `cin` would do that. So first we get a number, than a comma, than a number, and so on.  
Then it starts reading the boards from the input.  
Each number is pushed back onto a boad (a `vector` of `int`s). When done with a board, signaled by the empty line, the board itself is pushed back onto a vector of boards (a `vector` of `vector`s of `int`s).  

After all inputs have been processed, the program starts iterating over the draws. For each draw, a function MarkDrawOnBoards is called, which looks for the draw on each board and if it finds it, resets its value to zero (this makes it easier later on to calculate the score on the board if it wins).
After a draw is found on a board, it checks the board immediately for a win. It does this by checking each row and column to see if all numbers in that row or column have been set to zero. Also this is simple thanks to resetting marked values to zero, because now we can simply sum a row or column. Only if that row's or column's sum is zero, it is completely marked.  

---
<sub>

>**_A small note on checking the board_**:  
The board is a `vector<int>` object, which is not much more than just an array (or list) of numbers. By keeping the width of a row (which was retrieved from the length of the first line of input for a board), we can use it as a matrix. Finding numbers in a row is just incrementing an iterator by one until the width is reached. Finding numbers in a column is done by incrementing the iterator by the width everytime.

</sub>

---

If no winning board is found at a draw, the function just returns -1 as score and the program continues iterating over the draws. Otherwise it sums up the remaining numbers on the board (which is just the sum over the entire board) and returns that as the score.

## Part 2
Part two is a little different. I decided to create a struct named `player` which contains the player's score, the player's board, whether that player is a winner and at what draw the player won.  
The `MarkDrawOnBoards` function is adjusted to iterate over players instead of boards and to update each player object whenever a number is hit and when that player wins.  
Now the iteration over the draws includes a small nested iteration over all players to see how many players are left who have not won yet. As soon as this number becomes zero, we know this is the last player to win the game and that we should stop iterating over the draws. An extra check on whether the number of players who haven't won yet is added to the conditions of the `for` loop over the draws to do that.  
At that point, the last retrieved score is the score of the last winner and we also know at which draw that was.

This could be done more efficient for sure. I did not have to track the score of each winner and at which draw that happened. Also I could have made the `numNoWin` a global variable that is updated as soon as a player wins (from the `MarkDrawOnBoards` function). That way, the nested loop over all players to see how many still haven't won becomes entirely obsolete, dramatically improving the performance.
