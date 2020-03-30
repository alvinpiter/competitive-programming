# Problem D
Define ans[u] -> total sum that affects node u. After reading every query, ans[p] += x. After reading all query, run DFS from root to "propagate" the sum to the children.

# Problem E
Define pos[i] as an array of positions of character i in s.
Now we iterate the character in t starting from the first one. Assume we are now in character t[i]. We find the position of t[i] in s which is larger than the last position we take. There will be two cases:
* The position exist: Update the last position we take to be the position of t[i]
* The postion does not exist: Create another copy of S (figuratively), and then update the last position we take to be pos[t[i]][0].
