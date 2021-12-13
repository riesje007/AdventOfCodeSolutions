# The Treachery of Whales
From a number of positions, determine the shortest amount of moves (fuel) required to make those positions coincide (in a one-dimensional way), using 1 fuel per step.
Then, in part 2, calculate the minimum amount of fuel required when every next step costs one extra fuel.  
This means, that going from position 1 to 5 may cost 4 fuel in part 1 of the problem, but it costs 10 fuel in part 2.

The program addresses only part 2 here (part 1 should be rather simple).  
From the input positions it determines the minimum and maximum position value present in the collection. Then iterating over all possible positions starting from the minimum position value and ending at the maximum position value, it determines the distance to travel for each point in the collection (using a sum of sums function called `fuel`) and determines the minimum value of these results.