#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>   
#include <cmath>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int val) {
    if (root == NULL) {
        return new Node(val);
    }
    if (val < root->data)
        root->left = insert(root->left, val);
    else if (val > root->data)
        root->right = insert(root->right, val);
    return root;
}

int Height(Node* root) {
    if (root == NULL) return -1;

    int leftHeight = Height(root->left);
    int rightHeight = Height(root->right);

    return max(leftHeight, rightHeight) + 1;
}

Node* findMin(Node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

Node* deleteNode(Node* root, int val) {
    if (root == NULL) return NULL;

    if (val < root->data) {
        root->left = deleteNode(root->left, val);
    }
    else if (val > root->data) {
        root->right = deleteNode(root->right, val);
    }
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int main() {
    srand(time(NULL));

    int ns[] = { 100, 500, 1000, 2000, 5000, 10000 };
    int num_tests = 6;

    for (int i = 0; i < num_tests; i++) {
        int n = ns[i];
        Node* root = NULL;
        int last_val = 0;

        for (int j = 0; j < n; j++) {
            last_val = rand();
            root = insert(root, last_val);
        }

        int h = Height(root);

        double ratio = h / log2(n);

        cout << "n = " << n << ", height = " << h << ", ratio = " << ratio << endl;

        root = deleteNode(root, last_val);
    }

    return 0;
}