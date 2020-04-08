# Problem D
Derive the formula and find the roots using linear looping.

# Problem E
Define f(root, mask) as number of ways to construct tree using set of nodes in mask and rooted at root and obey all the rules.
In order to transition to a new state, we will take subset of mask and construct another subtree. The formula would be f(root, mask) += f(newRoot, newMask) * f(root, mask^newMask)

When creating a new subtree, we need to check if we still obey all the rules:
* Edge check -> If two node in different component, make sure the the edge is root and newRoot
* LCA check -> If two node in different component, make sure the lca is root.

To avoid double counting, only process newMask which fulfills the condition lsb(newMask) == lsb(mask).

Be careful with the lca rule with pattern a a b. In case we encounter one, just output 0.
