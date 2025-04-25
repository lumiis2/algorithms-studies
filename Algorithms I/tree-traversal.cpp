#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;

const int MAX = 100;
int adj[MAX][MAX]; // adjacency matrix
int n; // number of nodes

struct Node {
    int val;
    Node* left;
    Node* right;
    
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

// Pre-order: root, left, right
void preorder(Node* root) {
    if (!root) return;
    cout << root->val << ' ';
    preorder(root->left);
    preorder(root->right);
}

// In-order: left, root, right
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->val << ' ';
    inorder(root->right);
}

// Post-order: left, right, root
void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->val << ' ';
}


// Finds the left and right child of a given node (if any)
pair<int, int> get_children(int u) {
    int left = -1, right = -1;
    for (int v = 0; v < n; ++v) {
        if (adj[u][v]) {
            if (left == -1) left = v;
            else right = v;
        }
    }
    return {left, right};
}

void preorder(int u) {
    if (u == -1) return;
    cout << u+1 << ' ';
    auto [l, r] = get_children(u);
    preorder(l);
    preorder(r);
}

void inorder(int u) {
    if (u == -1) return;
    auto [l, r] = get_children(u);
    inorder(l);
    cout << u+1 << ' ';
    inorder(r);
}

void postorder(int u) {
    if (u == -1) return;
    auto [l, r] = get_children(u);
    postorder(l);
    postorder(r);
    cout << u+1 << ' ';
}

int main() { _
    /*
        Example tree:
        
              1
             / \
            2   3
           / \
          4   5
    */

    // with a tree data structure
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    cout << "Pre-order: ";
    preorder(root);
    cout << endl;

    cout << "In-order: ";
    inorder(root);
    cout << endl;

    cout << "Post-order: ";
    postorder(root);
    cout << endl;

    // with a adjacency matrix
        /*
        Tree example

              1
             / \
            2   3
           / \
          4   5

        */
    n = 5; // -> 0-based index
    adj[0][1] = 1;
    adj[0][2] = 1;
    adj[1][3] = 1;
    adj[1][4] = 1;

    cout << "Pre-order: ";
    preorder(0);
    cout << endl;

    cout << "In-order: ";
    inorder(0);
    cout << endl;

    cout << "Post-order: ";
    postorder(0);
    cout << endl;

    return 0;
}
