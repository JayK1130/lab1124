#include <iostream>
#include <vector>

struct Node{
    int data;
    Node *left;
    Node *right;
    Node (int data): data(data), left(nullptr), right(nullptr) {}
};

void printlevel(Node *root, int level){
    if(root == nullptr) return;
    if(level == 0) std::cout << root->data << " ";
    else if (level > 0) {
        printlevel(root->left, level-1);
        printlevel(root->right, level-1);
    }
}

void BSTinsert(Node *&root, int value) {
    Node *current = root;
    if (root == nullptr){
        root = new Node(value);
        return;
    }

    while(current != nullptr){
        if (value < current->data){
            if(current->left == nullptr) {
                current->left = new Node(value);
                return;
            } else {
                current = current->left;
            }
        } else {
            if(current->right == nullptr) {
                current->right = new Node(value);
                return;
            } else {
                current = current->right;
            }
        }
    }
    std::cout << "Can we print this statement?" << std::endl;
}

int treeHeight(Node* root) {
    if (root == nullptr) return -1;
    if (root->left == nullptr && root->right == nullptr) return 0;
    return 1 + std::max(treeHeight(root->left), treeHeight(root->right));
}

Node* BSTdelete(Node *root, int target){
    Node *current = root; Node *parent = nullptr;
    if(root == nullptr) return root;

    while(current != nullptr && current->data != target){
        parent = current;
        if (target < current-> data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == nullptr) return root;
    //case1
    if(current->left == nullptr && current->right == nullptr){
        if(parent == nullptr) {
            delete current;
            return nullptr;
        }
        if (parent->left == current){
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
        delete current;
        return root;
    }
    //case2 and 3
    if(current->left == nullptr || current->right == nullptr)
    {
        Node *child = (current->left != nullptr)? current->left : current->right;
        if (parent == nullptr){
            delete current;
            return child;
        } 
        if (parent->left == current){
            parent->left = child;
        } else {
            parent->right = child;
        }
        delete current;
        return root;
    }
    //case 4
    Node *successor = current->right;
    Node *successorParent = current;
    while(successor->left != nullptr){
        successorParent = successor;
        successor = successor->left;
    }
    if(successorParent->left == successor){
        successorParent->left = successor->left;
    } else {
        successorParent->right = successor->right;
    }
    delete successor;
    return root;
}

int main() 
{
    std::vector<int> data = {5,3,8,2,4,7,9,1,6};
    Node *root = nullptr;
    
    for (auto v: data) {
        BSTinsert(root, v);
    }
    std::cout << std::endl;
    int depth = treeHeight(root);
    for (int i = 0; i <=depth; i++) {
        printlevel(root, i); std::cout << std::endl;
    }
    std::cout << std::endl;

    int target = 1;
    BSTdelete(root, target);

    // find the node1. parent = 2, current = 1
    for (int i = 0; i<=depth; i++) {
        printlevel(root, i); std::cout << std::endl;
    }
}