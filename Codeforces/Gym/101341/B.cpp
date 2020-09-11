#include<bits/stdc++.h>
using namespace std;

//Returns indices i such that a pattern "happiness" happens at index i
vector<int> countHappiness(string s) {
    string pattern = "happiness";

    vector<int> indices;
    for (int i = 0; i + pattern.length() - 1 < s.length(); i++) {
        bool match = true;
        for (int j = 0; j < pattern.length(); j++) {
            if (s[i + j] != pattern[j]) {
                match = false;
                break;
            }
        }

        if (match) {
            indices.push_back(i);
        }
    }

    return indices;
}

int main() {
    string s;

    cin >> s;

    vector<int> indices = countHappiness(s);

    if (indices.size() == 0) {
        //try swap first and second character
        swap(s[0], s[1]);

        indices = countHappiness(s);
        if (indices.size() == 0) {
            cout << "YES\n";
            cout << 1 << " " << 2 << endl;
        } else {
            cout << "YES\n";
            cout << 1 << " " << 3 << endl;
        }
    } else if (indices.size() == 1) {
        cout << "YES\n";
        cout << indices[0] + 1 << " " << indices[0] + 2 << endl;
    } else if (indices.size() == 2) {
        cout << "YES\n";
        cout << indices[0] + 1 << " " << indices[1] + 2 << endl;
    } else {
        cout << "NO\n";
    }
}
