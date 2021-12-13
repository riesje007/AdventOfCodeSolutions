# Lanternfish
So, we have a couple of fishies that replicate like idiots. Each fish has a timer counting down from 6 to 0 and then resets to 6 producing a new fish which starts its count down timer at 8 for just once and after reaching 0 also resets to 6 (adding just two days to the time it takes for new fish to replicate).  

I was a bit confused by the input of the example, that read: "`Initial state: 3,4,3,1,2`", hence the stupid check on the input to see if it started with the words Initial and state:.

The first version of the program is a simple approach to the problem, just adding new fish to the end of a vector containing count-down timers. It iterates over the number of days, decreasing each timer at each iteration and resetting all values of 0 to 6 and adding new 8s to the end of the vector everytime a 0 was reset to 6.  
This blows up the vector big time, but for the first part, just iterating over 80 days, it was doable.

However...

## Part 2
In part two, all that was asked is to increase the number of days to 256. This would result in huge amounts of data in the vector and processing times that would probably have kept me waiting for days.  
So another approach was required. Since thenumber of possible count-down timer values is only a small set of numbers, one could also just keep track of the number of timers set to 0, the number of timers set to 1, and so on, till the number of timers set to 8!  
This would then result in a vector of just 9 numbers, where the position in the vector represents the count-down timer value and the value at that position the number of timers with that count-down timer value.
But because after each iteration, the number of timers with a certain count-down time has become the number of timers that had their count-down value set 1 higher in the previous iteration, it may even be more efficient to choose a container in which you can move values around.  
To have the most flexibility, I chose a `deque`, but a `stack` might also have sufficed (not sure).
So the second program creates a `deque` that keeps track of the number of timers with a certain value and the program just moves those numbers to the left, by popping the value at the front and pushing that same value (the number of fish that produce a new fish at that iteration) into the back (because this will be the number of fish which start at count-down timer value 8). At the same time the program reinserts this same value at position 6 by incrementing the existing value at position 6 with the value being inserted. Then the whole process is repeated for the number of remaining days.
