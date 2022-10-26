/*
Follow the comments to understand the solution.

Time complexity: N^2 log(N)
Number of queries: N + N log(N)
*/

#include "cave.h"
#include<bits/stdc++.h>
using namespace std;
#define MAXN 5000

void exploreCave(int N) {
  int doorForSwitch[MAXN + 3], correctStateForSwitch[MAXN + 3];
  int combinationToTry[N];

  memset(doorForSwitch, -1, sizeof(doorForSwitch));
  memset(correctStateForSwitch, -1, sizeof(correctStateForSwitch));

  for (int i = 0; i < N; i++) {
    /*
    Find the correct state for the i-th door's switch.
    We call tryCombination with all 0 and some correct switch state we've known so far.
    If the first locked door is > i, then the correct state for the i-th door's switch is 0.
    Otherwise, the correct state is 1.
    */
    for (int i = 0; i < N; i++) {
      combinationToTry[i] = 0;
    }

    for (int i = 0; i < N; i++) {
      if (correctStateForSwitch[i] != -1) {
        combinationToTry[i] = correctStateForSwitch[i];
      }
    }

    int firstLockedDoor = tryCombination(combinationToTry);
    int currentDoorSwitchState = (firstLockedDoor == -1 || firstLockedDoor > i ? 0 : 1);

    /*
    Find the index of the switch for the i-th door.

    We apply divide an conquer algorithm here.
    Set the first half of the switches to be currentDoorSwitchState.
    Set the second half of the switches to be not(currentDoorSwitchState).
    Also, we need to put some correct switch state we've known so far.

    If the first locked door is > i, then the switch we are looking for is
    in the first half. Otherwise, it is in the second half.
    */
    int lo = 0, hi = N - 1, mid;
    while (hi > lo) {
      mid = (lo + hi)/2;

      for (int i = 0; i <= mid; i++) combinationToTry[i] = currentDoorSwitchState;
      for (int i = mid + 1; i < N; i++) combinationToTry[i] = 1 - currentDoorSwitchState;
      for (int i = 0; i < N; i++) {
        if (correctStateForSwitch[i] != -1) {
          combinationToTry[i] = correctStateForSwitch[i];
        }
      }

      firstLockedDoor = tryCombination(combinationToTry);
      if (firstLockedDoor == -1 || firstLockedDoor > i) {
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }

    doorForSwitch[lo] = i;
    correctStateForSwitch[lo] = currentDoorSwitchState;
  }

  answer(correctStateForSwitch, doorForSwitch);
}
