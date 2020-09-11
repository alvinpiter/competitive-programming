# Problem A
For each rank, count how many times it occurs. Then we try value for v starting from the biggest one (200) and count how many ranks between 1 and v that we don't have yet. If this count is <= x, then v is our answer.

# Problem B
Assume the maximum number in array a is mx. That means either the prefix or the suffix must be a permutation of numbers from 1 to mx. Just check these two cases.

# Problem C
Algorithm:
* First put all the strips back to back. If still can't cover all cells, then answer is -1.
* Now the total length of our strips is larger than or equal to x. We can compress this total length by merging 2 adjacent strips. Assume strip i and i + 1. We can merge it and decrease the total length by l[i] - 1.
* Finally, check if there is a strip that is out of range.

# Problem D
Notice that there must be no two a's with the same most significant bit. Because if there is, the prefix XOR might be decreasing. Define f[i] as number of numbers whose most significant bit is at bit i. The answer is (f[0] + 1)*(f[1] + 1)*..*(f[i] + 1) - 1. Minus 1 because we want to exclude empty set. Be careful when calculating f[i], need to consider the bound d.

# Problem E
Observation: Whenever we call function f on index i, it will replace value on this index with largest value under subtree i (other than i itself).

Observation: Due to previous observation, it is optimal if we call f on element whose value is the largest first.

Observation: We shouldn't call f on index i if it will cause the tree to become invalid. Invalid here means that the tree can't be a complete binary tree with height g. To check if the resulting tree will be invalid can be done in O(h) time.
