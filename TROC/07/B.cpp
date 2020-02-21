#include<bits/stdc++.h>
using namespace std;

int result[5], number[5];

int main() {
    for (int i = 0; i < 5; i++)
        cin >> result[i];

    for (int i = 1; i <= 8; i++) {
        number[0] = i;

        bool valid = true;

        for (int j = 0; j < 4; j++) {
            number[j + 1] = result[j]/number[j];

            if (number[j + 1] == 0 || number[j + 1] > 8) {
                valid = false;
                break;
            }
        }

        for (int j = 0; j < 5; j++) {
            if (result[j] != number[j] * number[(j + 1)%5])
                valid = false;
        }

        if (valid)
            break;
    }

    for (int i = 0; i < 5; i++) {
        if (i > 0)
            cout << " ";

        cout << number[i];
    }
    cout << endl;
}
