# Problem D
Notice that on the i-th day, we can do jobs that has A <= M - i. We will find which job we can do at day M (whose A <= 0), M - 1 (whose A <= 1), M - 2 (whose A <= 2), ..., 0 (in that order). At a particular day, it is better to choose the job that has largest B. We can use priority queue for this.

# Problem E
Notice that we can change the edge of the graph into C - P, which means how much we coin we gain if we traverse it. If we change the edge into -(C - P), then the problem becomes finding shortest path in graph. This is true because we want to maximize sum of (C - P), hence minimize sum of -(C - P). Use Bellman-Ford algorithm, since there might be cycle with negative weight. For final check, we will iterate over all the edges u-v and check if edge u-v is involved in negative cycle and check if u is reachable from 1 and N is reachable from v. If there exist negative cycle, that means we can achieve infinite score.
