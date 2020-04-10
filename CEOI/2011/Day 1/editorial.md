# Balloons
Observation: If there are two ballons (x1, r1) and (x2, r2) where x1 < x2 and r1 <= r2 then first balloon won't be touched if second balloon haven't been touched. Which means that we are not interested in first balloon.

With that observation, we can maintain a stack of balloons with decreasing radius.
