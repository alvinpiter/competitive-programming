# Problem D
Let's calculate the number of ways to arrange the balls such that we need exactly i moves to collect them all. If it takes i moves, it means that there are i bucket of blue balls. Let's first divide K blue balls into i bucket where each bucket contain at least 1 ball, the number of ways to do this is C(K - 1, i - 1). We need to allocate 1 red ball to separate each bucket of blue balls, so our left over red balls would be N - K - (i - 1). Now we will divide the left over red balls to i + 1 bucket, the number of ways to do this is C(N - K + 1, i). So the total number of ways would be C(K - 1, i - 1) * C(N - K + 1, i).

# Problem E
Construct a new graph that consists of 3 * N nodes. Create 3 nodes from each of the original node. Let's say the original node is u, then we will create 3 new node called (u, 0), (u, 1) and (u, 2). (u, i) means that we reach node u where number of hop is equivalent to i modulo 3. Now perform BFS on the new graph to find the shortest path from (S, 0) and (T, 0).

# Problem F
