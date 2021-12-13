# Hydrothermal Venture
This assignment was all about reading x,y coordinates as starting and ending positions of straight lines and making these lines show up as ones in a matrix and increasing that number at positions where lines crossed / overlapped.  

To tackle this problem, I created a class `point` with some helper methods to determine whether a line was horizontal or vertical (the `isStraight` and `typeOfStraightLine` methods), to determine the minimum and maximum x and y values of two points (to determine the dimensions of the imaginary `matrix` as represented by the `vector` containing all the points).  

The resulting matrix is iterated over to determine at how many points there are overlapping lines (where the value is greater than or equal to 2).

## Part 2
The second program also takes diagonal lines into account. This makes checking overlap a little harder, as can be seen from the code from lines 136 till 152.  
Also a preprocessor statement was added, just to print matrices formed while debugging.