//
// Created by Evan Warnock on 6/2/25.
//


#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class AVL {
    public:
    //Tree Node struct
    struct Node {
        string name;
        int ufid;
        int height;
        Node* left;
        Node* right;

        Node(string name, int ufid) {
            this->name = name;
            this->ufid = ufid;
            this->left = nullptr;
            this->right = nullptr;
            this->height = 1;
        }
    };
    //AVL tree class functionality from here on out
    private:
    Node* root;


    public:
    //constructor
    AVL() {
        this->root = nullptr;
    }

    //Nine required functions
    void insert(string name, string ufid) {
        //1. Traverse through the tree starting with the root and insert the node in the correct spot
        //2. Get the balance factor of this  ancestor node to check whether this node became unbalanced
        //3.  Update the height of the ancestor node, and perform rotations on the tree as necessary
        //Also, prints “successful” if insertion is successful and prints “unsuccessful” otherwise.
        //
        //Ely advice is to use helper that uses node* as a param
        if (nameChecker(name)&&idChecker(ufid)) {
            root = insertHelper(root,name,stoi(ufid));
            cout << "successful\n";
        }
        else {
            cout << "unsuccessful\n";
        }
    }
    void remove(string id) {
        if (!idChecker(id)) {
            cout << "unsuccessful\n";
            return;
        }
        int ufid = stoi(id);
        removeHelper(root,ufid);
    }
    void searchUFID(string id) {
        if (!idChecker(id)) {
            cout << "unsuccessful\n";
            return;
        }
        int ufid = stoi(id);
        Node* searched = searchIDhelper(root,ufid);
        if (searched) {
            cout << searched->name << endl;
        }
        else {
            cout << "unsuccessful\n";
        }
    }
    void search(string name) {
        //should just make a call to preorder traversal helper and search vector for name
        bool found = false;
        if (!nameChecker(name)) {
            cout << "unsuccessful\n";
            return;
        }
        vector<Node*> nodes = getNodesPreOrder(root);
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i]->name == name) {
                cout << getIDtoString(nodes[i]->ufid) << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "unsuccessful\n";
        }

    }
    void printInorder() {
        vector<Node*> nodes = getNodesInOrder(root);
        for(int i=0;i<nodes.size()-1;i++) {
            cout << nodes[i]->name << ", ";
        }
        cout << nodes[nodes.size()-1]->name << endl;
    }
    void printPreorder() {
        vector<Node*> nodes = getNodesPreOrder(root);
        for(int i=0;i<nodes.size()-1;i++) {
            cout << nodes[i]->name << ", ";
        }
        cout << nodes[nodes.size()-1]->name << endl;
    }
    void printPostorder() {
        vector<Node*> nodes = getNodesPostOrder(root);
        for(int i=0;i<nodes.size()-1;i++) {
            cout << nodes[i]->name << ", ";
        }
        cout << nodes[nodes.size()-1]->name << endl;
    }
    void printLevelCount() {
        if (root == nullptr) {
            cout << 0;
        }
        else {
            cout << root->height << endl;
        }
    }
    void removeInOrder(int N) {
        vector<Node*> nodes = getNodesInOrder(root);
        if (nodes.size()<=N) {
            cout << "unsuccessful\n";
            return;
        }
        Node* node = nodes[N];
        removeHelper(root, node->ufid);
    }

    //rotation functions
    Node* rotateLeft(Node* node) {
        Node* newRoot = node->right;
        Node* child = newRoot->left;

        newRoot->left = node;
        node->right = child;

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

        return newRoot;
    }
    Node* rotateRight(Node* node) {
        Node* newRoot = node->left;
        Node* child = newRoot->right;

        newRoot->right = node;
        node->left = child;

        node->height = max(getHeight(node->left),getHeight(node->right)) + 1;
        newRoot->height = max(getHeight(newRoot->left),getHeight(newRoot->right)) + 1;
        //child node maintains height, doesn't ned to be updated
        return newRoot;
    }
    Node* rotateLeftRight(Node* node) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    Node* rotateRightLeft(Node* node) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    //Testing functions
    bool findIDbool(string id) {
        if (!idChecker(id))
            return false;
        int ufid = stoi(id);
        if (searchIDhelper(root,ufid)) {
            return true;
        }
        return false;
    }
    bool findNAMEbool(string name) {
        vector<Node*> nodes = getNodesPreOrder(root);
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i]->name == name) {
                return true;
            }
        }
        return false;
    }
    vector<string> getNamesInOrder() {
        vector<Node*> inOrder = getNodesInOrder(root);
        vector<string> names;
        for (int i = 0; i < inOrder.size(); i++) {
            names.push_back(inOrder[i]->name);
        }
        return names;
    }
    vector<string> getIdInOrder() {
        vector<Node*> inOrder = getNodesInOrder(root);
        vector<string> ids;
        for (int i = 0; i < inOrder.size(); i++) {
            ids.push_back(getIDtoString(inOrder[i]->ufid));
        }
        return ids;
    }

    //Function helpers
    Node* insertHelper(Node* node, string name, int ufid) {
        if (node == nullptr) {
            node = new Node(name, ufid);
            return node;
        }
        if (node->ufid>ufid) {
            node->left = insertHelper(node->left, name, ufid);
        }
        else if (node->ufid<ufid) {
            node->right = insertHelper(node->right, name, ufid);
        }
        else{
            return node;
        }
        //Have to update node heights
        node->height = max(getHeight(node->left),getHeight(node->right)) + 1;
        //uses new heights to check if tree needs to be rebalanced
        int bal = getBalance(node);
        if (bal >1 && (ufid < node->left->ufid)) {
            return rotateRight(node);
        }
        if (bal < -1 && (ufid > node->right->ufid)) {
            return rotateLeft(node);
        }
        if (bal > 1 && (ufid > node->left->ufid)) {
            return rotateLeftRight(node);
        }
        if (bal < -1 && (ufid < node->right->ufid)) {
            return rotateRightLeft(node);
        }
        return node;
    }
    Node* searchIDhelper(Node* node,int id) {
        if (node == nullptr||id==node->ufid) {
            return node;
        }
        if (id<node->ufid) {
            return searchIDhelper(node->left,id);
        }
        return searchIDhelper(node->right,id);
    }
    Node* removeHelper(Node* node, int id) {
        if (node == nullptr) {
            cout << "unsuccessful\n";
            return node;
        }
        if (node->ufid > id) {
            node->left = removeHelper(node->left, id);
        }
        else if (node->ufid < id) {
            node->right = removeHelper(node->right, id);
        }
        else {
            //Node can have 1. no children 2. one left 3. one right 4. both children
            if (node->left == nullptr && node->right == nullptr) {
                cout << "successful\n";
                delete node;
                return nullptr;
            }
            if (node->left != nullptr && node->right == nullptr) {
                cout << "successful\n";
                Node* successor = node->left;
                delete node;
                return successor;
            }
            if (node->left == nullptr && node->right != nullptr) {
                cout << "successful\n";
                Node* successor = node->right;
                delete node;
                return successor;
            }
            Node* successor = node->right;
            node->ufid = successor->ufid;
            node->name = successor->name;
            node->right = removeHelper(node->right, successor->ufid);
        }
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        return node;
    }
    bool idChecker(string ufid) {
        if (ufid.size()!=8) {
            return false;
        }
        for (int i = 0; i < 8; i++) {
            if (!idCheckerHelper(ufid[i]))
                return false;
        }
        return true;
    }
    bool idCheckerHelper(int c) {
        if (c>=48&&c<=57) {
            return true;
        }
        return false;
    }
    bool nameChecker(string name) {
        if (name.size()==0) {
            return false;
        }
        for (int i=0;i<name.length();i++) {
            if (!nameCheckerHelper(name[i])) {
                return false;
            }
        }
        return true;
    }
    bool nameCheckerHelper(char c) {
        if ((c>=65&&c<=90) || (c>=97&&c<=122)||c==32) {
            return true;
        }
        return false;
    }

    //getters
    vector<Node*> getNodesInOrder(Node* node) {
        vector<Node*> inOrder;
        if (node == nullptr) {
            return inOrder;
        }
        vector<Node*> left = getNodesInOrder(node->left);
        vector<Node*> right = getNodesInOrder(node->right);

        inOrder.insert(inOrder.end(), left.begin(), left.end());
        inOrder.push_back(node);
        inOrder.insert(inOrder.end(), right.begin(), right.end());

        return inOrder;
    }
    vector<Node*> getNodesPreOrder(Node* node) {
        vector<Node*> preOrder;
        if (node == nullptr) {
            return preOrder;
        }
        vector<Node*> left = getNodesPreOrder(node->left);
        vector<Node*> right = getNodesPreOrder(node->right);

        preOrder.push_back(node);
        preOrder.insert(preOrder.end(), left.begin(), left.end());
        preOrder.insert(preOrder.end(), right.begin(), right.end());

        return preOrder;
    }
    vector<Node*> getNodesPostOrder(Node* node) {
        vector<Node*> postOrder;
        if (node == nullptr) {
            return postOrder;
        }
        vector<Node*> left = getNodesPostOrder(node->left);
        vector<Node*> right = getNodesPostOrder(node->right);

        postOrder.insert(postOrder.end(), left.begin(), left.end());
        postOrder.insert(postOrder.end(), right.begin(), right.end());
        postOrder.push_back(node);

        return postOrder;

    }
    int getHeight(Node* node) {
        if (node==nullptr) {
            return 0;
        }
        return node->height;
    }
    int getBalance(Node* node) {
        if (node==nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }
    string getIDtoString(int id) {
        string str = "";
        string snum = to_string(id);
        int diff = 8 - snum.length();
        for (int i = 0; i < diff; i++) {
            str += '0';
        }
        str += snum;
        return str;
    }
    Node* getRoot() {
        return root;
    }

    //destructor
    ~AVL() {
        //Video says to do a postorder traversal to delete nodes bc each node will only be visited once
        destructorHelper(root);
        root = nullptr;
    }
    //Thank you TA Jackie for helping me fix my destructor
    void destructorHelper(Node* node) {
        if (!node) {
            return;
        }
        destructorHelper(node->left);
        destructorHelper(node->right);
        node = nullptr;
        delete node;
    }
};



#endif //AVL_H
