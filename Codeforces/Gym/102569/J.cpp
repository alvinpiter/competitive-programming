#include<bits/stdc++.h>
using namespace std;

void find() {
    for (int a = 1; a <= 10; a++) {
        for (int b = 1; b <= 10; b++) {
            for (int c = 1; c <= 10; c++) {
                for (int d = 1; d <= 10; d++) {
                    for (int e = 1; e <= 10; e++) {
                        for (int f = 1; f <= 10; f++) {
                            vector<int> first;
                            first.push_back(a);
                            first.push_back(b);
                            first.push_back(c);

                            vector<int> second;
                            second.push_back(d);
                            second.push_back(e);
                            second.push_back(f);

                            int numWin1 = 0;
                            int numWays1 = 9;
                            for (int i = 0; i < first.size(); i++) {
                                for (int j = 0; j < second.size(); j++) {
                                    if (first[i] > second[j])
                                        numWin1 += 1;
                                }
                            }

                            int numWin2 = 0;
                            int numWays2 = 9;
                            for (int i = 0; i < first.size(); i++) {
                                for (int j = i + 1; j < first.size(); j++) {
                                    for (int k = 0; k < second.size(); k++) {
                                        for (int l = k + 1; l < second.size(); l++) {
                                            if (first[i] + first[j] < second[k] + second[l])
                                                numWin2 += 1;
                                        }
                                    }
                                }
                            }

                            int numWin3 = (first[0] + first[1] + first[2] > second[0] + second[1] + second[2] ? 1 : 0);
                            int numWays3 = 1;

                            if (2 * numWin1 > numWays1 && 2 * numWin3 > numWays3 && 2 * numWin2 > numWays2) {
                                cout << a << " " << b << " " << c << " " << d << " " << e << " " << f << endl;
                            }
                        }
                    }
                }
            }
        }
    }
}

int main() {
    // find();

    cout << 3 << endl;
    cout << "4 4 3\n";
    cout << 3 << endl;
    cout << "1 1 8\n";
}
