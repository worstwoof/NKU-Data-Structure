#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    int height;
};

int getHeight(Node* tree) {
    if (tree == NULL) return 0;
    return tree->height;
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

Node* insert(Node* tree, int val) {
    if (tree == NULL) {
        Node* node = new Node;
        node->val = val;
        node->left = NULL;
        node->right = NULL;
        node->height = 1;
        return node;
    }

    if (val < tree->val) {
        tree->left = insert(tree->left, val);

        if (getHeight(tree->left) - getHeight(tree->right) == 2) {
            if (val < tree->left->val) {
                tree = rotateRight(tree);
            }
            else {
                tree->left = rotateLeft(tree->left);
                tree = rotateRight(tree);
            }
        }
    }
    else {

        tree->right = insert(tree->right, val);

        if (getHeight(tree->right) - getHeight(tree->left) == 2) {
            if (val > tree->right->val) {
                tree = rotateLeft(tree);
            }
            else {
                tree->right = rotateRight(tree->right);
                tree = rotateLeft(tree);
            }
        }
    }

    tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;
    return tree;
}

void checkAndPrint(Node* root) {
    if (root == NULL) return;
    queue<Node*> q;
    q.push(root);
    bool seenEmpty = false;
    bool isComplete = true;
    bool firstPrint = true;

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();


        if (firstPrint) {
            cout << current->val;
            firstPrint = false;
        }
        else {
            cout << " " << current->val;
        }

        if (current->left != NULL) {
            if (seenEmpty) isComplete = false; 
            q.push(current->left);
        }
        else {
            seenEmpty = true; 
        }

        if (current->right != NULL) {
            if (seenEmpty) isComplete = false; 
            q.push(current->right);
        }
        else {
            seenEmpty = true; 
        }
    }
    cout << endl;
    if (isComplete) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
}

int main() {
    int n;
    if (cin >> n) {
        Node* root = NULL;
        int val;
        for (int i = 0; i < n; i++) {
            cin >> val;
            root = insert(root, val);
        }
        checkAndPrint(root);
    }
    return 0;
}