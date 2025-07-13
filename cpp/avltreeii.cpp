#include <iostream>
#include <queue>

using namespace std;

struct node
{
	int key;		   	// Search value
	node *left, *right; // Pointers to children
	int height;		 	// Height of subtree
	node()
	{
		left = nullptr;
		right = nullptr;
		height = 0;
	}
};

int height(node * node) {
    if( node == nullptr )
        return 0;
    return node->height;
}

node * rotateRight(node *n)
{
	if(n == nullptr || n->left == nullptr)
		return n;
	node *t = n->left;
	n->left = t->right;
	t->right = n;

	// Set heights
	if(n->left != nullptr && n->right != nullptr)
		n->height = max(n->left->height, n->right->height) + 1;
	else if(n->left != nullptr)
		n->height = n->left->height + 1;
	else if(n->right != nullptr)
		n->height = n->right->height + 1;
	else
		n->height = 1;

	if(t->left != nullptr)
		t->height = max(n->height, t->left->height) + 1;
	else
		t->height = n->height + 1;
	return t;
}

node * rotateLeft(node *n)
{
	if(n == nullptr || n->right == nullptr)
		return n;
	node *t = n->right;
	n->right = t->left;
	t->left = n;

	// Set heights
	if(n->left != nullptr && n->right != nullptr)
		n->height = max(n->left->height, n->right->height) + 1;
	else if(n->left != nullptr)
		n->height = n->left->height + 1;
	else if(n->right != nullptr)
		n->height = n->right->height + 1;
	else
		n->height = 1;

	if(t->right != nullptr)
		t->height = max(n->height, t->right->height) + 1;
	else
		t->height = n->height + 1;
	return t;
}

node * checkHeights(node *n)
{
	if(n == nullptr)
		return n;
	if(n->left == nullptr && n->right == nullptr)
	{
		n->height = 1;
		return n;
	}
	else if(n->left == nullptr)
	{
		n->height = n->right->height + 1;
		if(n->right->height >= 2)
		{
			if(n->right->left != nullptr && (n->right->right == nullptr || n->right->left->height > n->right->right->height))
				n->right = rotateRight(n->right);
			return rotateLeft(n);
		}
	}
	else if(n->right == nullptr)
	{
		n->height = n->left->height + 1;
		if(n->left->height >= 2)
		{
			if(n->left->right != nullptr && (n->left->left == nullptr || n->left->right->height > n->left->left->height))
				n->left = rotateLeft(n->left);
			return rotateRight(n);
		}
	}
	else
	{
		n->height = max(n->left->height, n->right->height) + 1;
		if(abs(n->left->height - n->right->height) >= 2)
		{
			if(n->left->height > n->right->height)
			{
				if(n->left->right != nullptr && (n->left->left == nullptr || n->left->right->height > n->left->left->height))
					n->left = rotateLeft(n->left);
				return rotateRight(n);
			}
			else
			{
				if(n->right->left != nullptr && (n->right->right == nullptr || n->right->left->height > n->right->right->height))
					n->right = rotateRight(n->right);
				return rotateLeft(n);
			}
		}
	}
	return n;
}

node * insert(node *n, int key)
{
	// Create and insert node
	if(n == nullptr)
	{
		n = new node;
		n->key = key;
		n->height = 1;
		return n;
	}

	// Insert into appropriate subtree
	if(n->key <= key)
		n->right = insert(n->right, key);
	else
		n->left = insert(n->left, key);

	// Recalculate heights and rotate
	return checkHeights(n);
}

node * delet(node *n, int key)
{
	if(n == nullptr)
	{
		cerr<<"Node not found\n";
		return nullptr;
	}
	// Find and delete node
	if(key == n->key)
	{
		if(n->left == nullptr && n->right == nullptr)
		{
			delete n;
			return nullptr;
		}
		else if(n->left == nullptr)
		{
			node *t = n->right;
			*n = *t;
			delete t;
		}
		else if(n->right == nullptr)
		{
			node *t = n->left;
			*n = *t;
			delete t;
		}
		else
		{
			node *t = n->left;
			while(t->right != nullptr)
				t = t->right;
			int temp = n->key;
			n->key = t->key;
			t->key = temp;
			n->left = delet(n->left, key);
		}
	}
	else if(key < n->key)
		n->left = delet(n->left, key);
	else
		n->right = delet(n->right, key);
	// Rebalance tree
	return checkHeights(n);
}

node * mergeWithNode(node *tree1, node *tree2, node *mergeNode)
{
	if(mergeNode == nullptr)
		return tree1;
	if(tree1 == nullptr && tree2 == nullptr)
		return mergeNode;
	else if(tree1 == nullptr)
	{
		int t = mergeNode->key;
		tree2 = insert(tree2, t);
		delete mergeNode;
		return tree2;
	}
	else if(tree2 == nullptr)
	{
		int t = mergeNode->key;
		tree1 = insert(tree1, t);
		delete mergeNode;
		return tree1;
	}
	if(tree1->height - tree2->height >= 2)
	{
		tree1->left = mergeWithNode(tree1->left, tree2, mergeNode);
		tree1 = checkHeights(tree1);
		return tree1;
	}
	else if(tree2->height - tree1->height >= 2)
	{
		tree2->right = mergeWithNode(tree1, tree2->right, mergeNode);
		tree2 = checkHeights(tree2);
		return tree2;
	}
	mergeNode->left = tree2;
	mergeNode->right = tree1;
	mergeNode = checkHeights(mergeNode);
	return mergeNode;
}

node * extractMin(node **tree)
{
	if(tree == nullptr)
		return nullptr;
	// Found minimum node
	if((*tree)->left == nullptr)
	{
		// Copy details
		node *temp = new node;
		*temp = **tree;
		// Remove node from tree
		*tree = delet(*tree, (*tree)->key);
		// Rebalance
		*tree = checkHeights(*tree);
		return temp;
	}
	// Keep moving
	node *t = extractMin(&((*tree)->left));
	// Rebalance
	(*tree) = checkHeights(*tree);
	return t;
}


// Tree1 is initial tree, as well as final larger tree
void breakTree(int key, node **tree1, node **tree2)
{
	if(tree1 == nullptr)
		return;
	// Move to appropriate node
	// then store subtree in appropriate tree
	if(key > (*tree1)->key)
	{
		breakTree(key, &(*tree1)->right, tree2);
		node *t = (*tree1)->right;
		if((*tree2) != nullptr)
		{
			(*tree2) = mergeWithNode((*tree2), (*tree1)->left, (*tree1));
		}
		else
		{
			(*tree2) = (*tree1)->left;
			(*tree2) = insert((*tree2), (*tree1)->key);
			delete (*tree1);
		}
		(*tree1) = t;
	}
	else if(key < (*tree1)->key)
	{
		breakTree(key, &(*tree1)->left, tree2);
		if((*tree1)->left != nullptr && (*tree1)->right != nullptr)
			(*tree1) = mergeWithNode((*tree1)->right, (*tree1)->left, (*tree1));
		else
		{
			if((*tree1)->left == nullptr)
			{
				node* t = (*tree1);
				(*tree1) = (*tree1)->right;
				(*tree1) = insert((*tree1), t->key);
				delete t;
			}
			else if((*tree1)->right == nullptr)
			{
				node *t = (*tree1);
				(*tree1) = (*tree1)->left;
				(*tree1) = insert((*tree1), t->key);
				delete t;
			}
		}
	}
	else
	{
		node *n = (*tree1);
		(*tree2) = (*tree1)->left;
		(*tree1) = (*tree1)->right;
		delete n;
	}
}

/*
// PUBLIC FUNCTIONS
// Returns smaller tree
template <class T>
AVL<T> AVL<T>::split(T key)
{
	AVL tree2;
	breakTree(key, &root, &tree2.root);
	return tree2;
}
// Assumption: Tree2 is tree with smaller keys
template <class T>
AVL<T> AVL<T>::add(AVL<T> tree2)
{
	node *m = extractMin(&root);
	root = mergeWithNode(root, tree2.root, m);
	return *this;
}
template <class T>
AVL<T> AVL<T>::ins(T val)
{
	root = insert(root, val);
	return *this;
}
template <class T>
AVL<T> AVL<T>::del(T val)
{
	root = delet(root, val);
	return *this;
}
*/

int find(node * root, int key)
{
	// Search tree until required value encountered
	node *t = root;
	while(t != nullptr && t->key != key)
	{
		if(key > t->key)
			t = t->right;
		else
			t = t->left;
	}
	// Value not found
	if(t == nullptr)
		return -1;
	// Value found
	return t->key;
}

// debug
void inorder(node * node) {
    if( node == nullptr )
        return;

    inorder(node->left);
    cout << node->key << " ";
    inorder(node->right);
    return;
}

void disp(node * root)
{
	if(root == nullptr)
	{
		cout<<"nullptr\n";
		return;
	}
	int sp = 1;
	for(int i = 1; i < root->height; ++i)
		sp *= 2;
	queue<node *> p, q;
	int i = 0;
	q.push(root);
	while(i != root->height)
	{
		while(!q.empty())
		{
			for(int j = 0; j < sp; ++j)
				cout<<"	";
			if(q.front() != nullptr)
			{
				cout<<q.front()->key<<"("<<q.front()->height<<")";
				p.push(q.front()->left);
				p.push(q.front()->right);
			}
			else
			{
				cout<<"nullptr";
				p.push(nullptr);
				p.push(nullptr);
			}
			q.pop();
		}
		cout<<"\n";
		++i;
		sp /= 2;
		swap(q,p);
	}
}


int main() {

	// AVL Tree, allows duplicate keys, supports 
	// insert a key, 
	// delete a key, 
	// split (key to be split at will be removed, 
    //     but easily changed to remove key from tree and return that key), 
	// merge (assumes keys in tree to be added <= keys in original tree), 
	// find (return -1 if not found, so assumes keys != -1)

	cout << "building initial tree" << endl;
	
	node * root = nullptr;
	for(int i = 0; i < 20; ++i) {
        cout << "inserting " << i << endl;
        root = insert(root, i);
    }

    // expect 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19
    inorder(root); cout << endl;

    cout << "height of root " << root->height << endl;
    cout << "height left child " << height(root->left) << " height right child " << height(root->right) << endl;
    cout << "balanceFactor (height(node->left) - height(node->right)) " << height(root->left) - height(root->right) << endl; 
    
    disp(root); cout << endl;

	// ------------------------------------------------------------------------

	cout << "interserting dup " << 5 << endl;
	root = insert(root, 5);

    cout << "expect 0 1 2 3 4 5 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19" << endl;
    cout << "actual "; inorder(root); cout << endl;

    cout << "height of root " << root->height << endl;
    cout << "height left child " << height(root->left) << " height right child " << height(root->right) << endl;
    cout << "balanceFactor (height(node->left) - height(node->right)) " << height(root->left) - height(root->right) << endl; 
    
    disp(root); cout << endl;

	// ------------------------------------------------------------------------

	cout << "deleting 7 and 0" << endl;
	root = delet(root, 7);
	root = delet(root, 0);

    cout << "expect 1 2 3 4 5 5 6 8 9 10 11 12 13 14 15 16 17 18 19" << endl;
    cout << "actual "; inorder(root); cout << endl;

    cout << "height of root " << root->height << endl;
    cout << "height left child " << height(root->left) << " height right child " << height(root->right) << endl;
    cout << "balanceFactor (height(node->left) - height(node->right)) " << height(root->left) - height(root->right) << endl; 
    
    disp(root); cout << endl;

	// ------------------------------------------------------------------------

	cout << "extracting minimum " << endl;
	node * min_node = extractMin(&root);

	cout << "min node " << min_node->key << "(" << min_node->height << ")" << endl;
    cout << "expect 2 3 4 5 5 6 8 9 10 11 12 13 14 15 16 17 18 19" << endl;
    cout << "actual "; inorder(root); cout << endl;

    cout << "height of root " << root->height << endl;
    cout << "height left child " << height(root->left) << " height right child " << height(root->right) << endl;
    cout << "balanceFactor (height(node->left) - height(node->right)) " << height(root->left) - height(root->right) << endl; 
    
    disp(root); cout << endl;

	// ------------------------------------------------------------------------

	// note key allows duplicates, hence be careful when breaking the tree
	int break_key = 6;
	cout << "breaking tree at key " << break_key << endl;
	cout << "note that key " << break_key << " will be deleted!!!" << endl;

	// tree2 will contain smaller keys

	node * tree2 = nullptr;
	breakTree(break_key, &root, &tree2);

	cout << "original tree larger keys" << endl;
	cout << "expect 8 9 10 11 12 13 14 15 16 17 18 19" << endl;
    cout << "actual "; inorder(root); cout << endl;

    cout << "height of root " << root->height << endl;
    cout << "height left child " << height(root->left) << " height right child " << height(root->right) << endl;
    cout << "balanceFactor (height(node->left) - height(node->right)) " << height(root->left) - height(root->right) << endl; 
    
    disp(root); cout << endl;

	cout << "tree2 smaller keys" << endl;
	cout << "expect 2 3 4 5 5 " << endl;
    cout << "actual "; inorder(tree2); cout << endl;

    cout << "height of root " << tree2->height << endl;
    cout << "height left child " << height(tree2->left) << " height right child " << height(tree2->right) << endl;
    cout << "balanceFactor (height(node->left) - height(node->right)) " << height(tree2->left) - height(tree2->right) << endl; 
    
    disp(tree2); cout << endl;

	// ------------------------------------------------------------------------

	cout << "merging aka joining two trees" << endl;
	cout << "assumption is that the tree to be added has keys <= smallest key in original tree" << endl;

	// Assumption: Tree2 is tree with smaller keys
	node *m = extractMin(&root);
	root = mergeWithNode(root, tree2, m);
	
	cout << "expect 2 3 4 5 5 8 9 10 11 12 13 14 15 16 17 18 19" << endl;
    cout << "actual "; inorder(root); cout << endl;

    cout << "height of root " << root->height << endl;
    cout << "height left child " << height(root->left) << " height right child " << height(root->right) << endl;
    cout << "balanceFactor (height(node->left) - height(node->right)) " << height(root->left) - height(root->right) << endl; 
    
    disp(root); cout << endl;

	// ------------------------------------------------------------------------

	cout << "find non-existing key, expect -1" << endl;
	cout << find(root, 6) << endl;
	cout << "find existing key, expect key" << endl;
	cout << find(root, 18) << endl;

    return 0;
}

// clang++ --std=c++17 avltreei.cpp -o avltreei
// https://www.geeksforgeeks.org/insertion-in-an-avl-tree/
// https://github.com/AKKamath/AVL-Merge-Split/blob/master/AVL.h
