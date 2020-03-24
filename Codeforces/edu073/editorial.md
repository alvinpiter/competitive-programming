# Problem A
Pair the numbers starting from the smallest one. We can do this by counting the occurence of each number. If counter[2048] > 0, answer is YES otherwise answer is NO.

# Problem B
Imagine a chess board where each cell is either black or white. If we put a knight at cell with color black, it will attack cell with color white, and vice versa. Hence to maximise the number of attacks, we put all black knight into black cells and white knight into white cells.

# Problem C
Observation: Always using person without specialization (while possible) will yield optimal answer
Proof: By exchange argument. Let's say there is a solution where we dont use person with specialization while possible. Then there are two cases:
* There is a team with composition 2 coders + 1 mathematician or 1 coders + 2 mathematician. Then we can replace one of the those people with person with no specialization
* There is no team with composition 2 coders + 1 mathematician or 1 coders + 2 mathematician. Nothing we can do here.

Now we are left with coders and mathematician. Notice that the sum (c + m) always divisible by 3 after creating a new team. Hence we can use at most floor((c + m)/3) teams. But we have to be careful when there is not enough c or m, the corrected formula would be min(floor((c + m)/3), min(c, m)).

# Problem D
Observation: Each fence with height equal to either one of its neighbors will need to be extended at most 2 times.
Proof: Let's look at the height difference of the two neighbors. There a couple of cases:
* The difference is 0, then we can extend current fence 1 time.
* The difference is 1, then we can extend current fence 1 or 2 times.
* The difference is > 1, then we can extend current fence 1 time.
