#include<bits/stdc++.h>
using namespace std;
#define MAXLG 20

struct Node {
    int counter;
    Node* children[2];
    Node() {
        counter = 0;
        children[0] = children[1] = NULL;
    }
};

void insert(Node* root, int number) {
    Node* current = root;
    for (int i = MAXLG; i >= 0; i--) {
        int bit = (number & (1 << i)) > 0 ? 1 : 0;

        if (current->children[bit] == NULL) {
            Node* newNode = new Node;
            current->children[bit] = newNode;
        }

        current = current->children[bit];
        current->counter += 1;
    }
}

/*
Count how many numbers whose XOR with number is less than threshold.
*/
int query(Node* root, int number, int threshold) {
    Node* current = root;
    int result = 0;

    for (int i = MAXLG; i >= 0; i--) {
        if (current == NULL)
            break;

        int numberBit = (number & (1 << i)) > 0 ? 1 : 0;
        int thresholdBit = (threshold & (1 << i)) > 0 ? 1 : 0;

        if (numberBit == 1 && thresholdBit == 1) {
            result += (current->children[1] != NULL ? current->children[1]->counter : 0);
            current = current->children[0];
        }

        if (numberBit == 1 && thresholdBit == 0) {
            current = current->children[1];
        }

        if (numberBit == 0 && thresholdBit == 1) {
            result += (current->children[0] != NULL ? current->children[0]->counter : 0);
            current = current->children[1];
        }

        if (numberBit == 0 && thresholdBit == 0) {
            current = current->children[0];
        }
    }

    return result;
}

int main() {
    int T, N, K, currentXOR;
    long long int answer;

    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%d%d", &N, &K);

        Node* root = new Node;

        currentXOR = 0;
        answer = 0;

        insert(root, currentXOR);
        for (int i = 1; i <= N; i++) {
            int number;
            scanf("%d", &number);

            currentXOR ^= number;
            answer += query(root, currentXOR, K);

            insert(root, currentXOR);
        }

        printf("%lld\n", answer);
    }
}
