# ADAPET
If the desired K is 1, the answer is the length of the string itself. If the desired K = 2, we want to add as little characters as possible to the end of the string. How to do it? Look at the border of the string (proper prefix that is also proper suffix), assume it's length is B, then we add |S| - B characters to our initial string. These |S| - B characters are the remaining characters that we need to form S from the border. If K > 2, just repeat this procedure. For example: S = "ada" and K = 3, the length of the border is 1 ("a"), so we will repeatedly add 3 - 1 = 2 characters to the end of S. The final string would be "adadada" ("ada" + "da" + "da").

# EC_P
Finding bridge in graph.

# SUBMERGE
Finding articulation point in graph.
