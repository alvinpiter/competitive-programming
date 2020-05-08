# Problem A
Just output the first k alphabet until the length of the string is n.

# Problem B
Sort the skills increasingly and check each neighboring elements. If it is not the same, update the answer.

# Problem C
Tkae the 2 string with length n - 1, let's say their name A and B. The original string is either A + (last character of B) or B + (last character of A). Knowing the original string, we should validate it with the given 2 * n - 2 prefixes and suffixes.

# Problem D1
Notice that vertical block doesn't change the parity of the height, while horizontal block changes the parity.
We can categorize heights into two categories, the one whose parity is changeable and the one whose parity is not changeable. Height's parity is changeable if there is another height to the left or right of it that has the same parity. If we want to make all heights the same, the parity of all heights who are not-changeable must be the same.

# Problem D2

# Problem E

# Problem F
Root the tree at 1 and then use tree re-root technique or calculate the cost down and cost up.
