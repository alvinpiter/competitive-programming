# Problem A
Sort the number. If the minimum and maximum value is the same, there is no way to divide it into two sets with equal sum. Otherwise it is always possible, for example n smallest number goes to first set and n largest number goes to second set.

# Problem B
If the parity of all the numbers are the same, nothing we can do, just output the original array. Otherwise we can always sort it in non-decreasing order.

# Problem C
Sieve. Assume there are k primes between 2 and n (inclusive). Then the maximal "a" would be k. To construct solution: label the first prime and all its multiple with 1, label the second prime and all its multiple with 2, so on. If there is a number that has more than 1 prime factor, label it with any number is fine.

# Problem D
Consider the prefix XOR of the array. It is obvious that the values should range between 0 to 2^n - 1.

Observation: There is no 2 prefix XOR has the same value.
Proof: If there is, then some subsegment will have XOR equals to 0.

Observation: There is be no two prefix XOR whose XOR is x.
Proof: If there is, then some subsegment will have XOR equals to x.

When two prefix XOR values XOR to x, then we must choose one of them. Also notice that if a XOR b = x, then a will not have another pair c such that a XOR c = x and c != b. To construct the array, just output prefixXOR[i] ^ prefixXOR[i - 1].

# Problem E
