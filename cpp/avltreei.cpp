#include <iostream>
#include <queue>

using namespace std;

struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(int key) : key(key), left(nullptr), right(nullptr), height(1) {}
};

int height(AVLNode * node) {
    if( node == nullptr )
        return 0;
    return node->height;
}

int balanceFactor(AVLNode * node) {
    if( node == nullptr )
        return 0;
    return height(node->left) - height(node->right);
}

void update(AVLNode * node) {
    if( node == nullptr )
        return;
    node->height = 1 + max(height(node->left), height(node->right));
    return;
}

AVLNode * rightRotate(AVLNode * y) {
    AVLNode * x = y->left;
    AVLNode * T2 = x->right;

    /*    y               x
     *   /     rotation     \
     *  x      ------->      y
     *   \                  /
     *    T2               T2
     */

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update y and x, nothing has changed for T2
    // order of update matters: y is child of x now, so update y before x
    update(y);
    update(x);

    // Return new root
    return x;
}

AVLNode * leftRotate(AVLNode * x) {
    AVLNode * y = x->right;
    AVLNode * T2 = y->left;

    /*    x                 y
     *     \   rotation    /
     *      y  ------->   x
     *     /               \
     *    T2                T2
     */

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update x and y, nothing has changed for T2
    // order of update matters: x is now a child of y, so update x before y
    update(x);
    update(y);

    // Return new root
    return y;
}

// function to insert a new key into the subtree rooted at node
AVLNode * insert(AVLNode * node, int key) {
    if( node == nullptr )
        return new AVLNode(key);

    if( key < node->key )
        node->left = insert(node->left, key);
    else if( key > node->key )
        node->right = insert(node->right, key);
    else
        return node;

    update(node);

    // Get the balance factor of our ancestor node
    int balance = balanceFactor(node);

    // If node becomes unbalanced, then there are 4 cases

    // Left Left Case 
    if( balance > 1 && key < node->left->key ) 
        return rightRotate(node); 

    // Right Right Case 
    if( balance < -1 && key > node->right->key ) 
        return leftRotate(node); 

    // Left Right Case 
    if( balance > 1 && key > node->left->key ) { 
        node->left = leftRotate(node->left); 
        return rightRotate(node); 
    } 

    // Right Left Case 
    if( balance < -1 && key < node->right->key ) { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 

    return node;
}

// debug
void inorder(AVLNode * node) {
    if( node == nullptr )
        return;

    inorder(node->left);
    cout << node->key << " ";
    inorder(node->right);
    return;
}

// debug
void disp(AVLNode * root) {
	if( root == nullptr ){
		cout<<"NULL\n";
		return;
	}

	int sp = 1;
	for(int i = 1; i < root->height; ++i)
		sp *= 2;

	queue<AVLNode *> p, q;
	int i = 0;
	q.push(root);
	while(i != root->height) {
		while(!q.empty()) {
			for(int j = 0; j < sp; ++j)
				cout<<"	";
			if(q.front() != nullptr) {
				cout << q.front()->key << "(" <<q.front()->height << ")";
				p.push(q.front()->left);
				p.push(q.front()->right);
			} else {
				cout << "NULL";
				p.push(nullptr);
				p.push(nullptr);
			}
			q.pop();
		}
		cout << "\n";
		++i;
		sp /= 2;
		swap(q,p);
	}
}

int main() { 

    // AVL Tree, no duplicate keys, supports
    // insert

    AVLNode * root = nullptr;
    for(int i = 0; i < 20; ++i) {
        cout << "inserting " << i << endl;
        root = insert(root, i);
    }

    // expect 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19
    inorder(root); cout << endl;

    cout << "height of root " << root->height << endl;
    cout << "height left child " << height(root->left) << " height right child " << height(root->right) << endl;
    cout << "balanceFactor (height(node->left) - height(node->right)) " << balanceFactor(root) << endl; 
    
    disp(root);

    return 0;
}

// clang++ --std=c++17 avltreei.cpp -o avltreei
// https://www.geeksforgeeks.org/insertion-in-an-avl-tree/
// https://github.com/AKKamath/AVL-Merge-Split/blob/master/AVL.h
