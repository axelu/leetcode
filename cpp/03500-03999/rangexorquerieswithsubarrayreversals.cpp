
// 3526. Range XOR Queries with Subarray Reversals
// https://leetcode.com/problems/range-xor-queries-with-subarray-reversals/






/* based on hint in the problem, using an adaptation of an AVL Tree
 * https://www.geeksforgeeks.org/cpp-program-to-implement-avl-tree/
 * https://en.wikipedia.org/wiki/AVL_tree#Rebalancing
 * https://github.com/AKKamath/AVL-Merge-Split/blob/master/AVL.h
 */
class Solution {
private:
    struct node
    {
        // we are not doing it by key
        // instead, the key of a node is
        // the number of children in its left subtree
        // int key;		   	// Search value
        node *left, *right; // Pointers to children
        int height;		 	// Height of subtree

        // augmenting properties
        int _val;
        int _xor;
        int _size; // size of right and left subtree + 1
        bool _reversed;

        node()
        {
            left = nullptr;
            right = nullptr;
            height = 0;
        }
    };

    int get_size(node * node) {
        if( node == nullptr )
            return 0;
        return node->_size;
    }

    int get_xor(node * node) {
        if( node == nullptr )
            return 0;
        return node->_xor;
    }

    // maintain size and xor
    void update(node * node) {
        node->_xor = node->_val ^ get_xor(node->left) ^ get_xor(node->right);
        node->_size = 1 + get_size(node->left) + get_size(node->right);
        return;
    }

    int height(node * node) {
        if( node == nullptr )
            return 0;
        return node->height;
    }

    void push(node *n) {
        if( n != nullptr && n->_reversed ) {
            n->_reversed = false;
            node *t = n->left;
            n->left = n->right;
            n->right = t;

            if( n->left != nullptr )
                n->left->_reversed ^= true;
            if( n->right != nullptr )
                n->right->_reversed ^= true;
        }

        return;
    }

    node * rotateRight(node *n) {
        if( n == nullptr || n->left == nullptr )
            return n;

        // perform the rotation
        node *t = n->left;
        n->left = t->right;
        t->right = n;

        // after the rotation n is the right child of t
        // so we need to update n first, then t
        update(n);
        update(t);

        // Set heights
        if (n->left != nullptr && n->right != nullptr )
            n->height = max(n->left->height, n->right->height) + 1;
        else if( n->left != nullptr )
            n->height = n->left->height + 1;
        else if( n->right != nullptr )
            n->height = n->right->height + 1;
        else
            n->height = 1;

        if( t->left != nullptr )
            t->height = max(n->height, t->left->height) + 1;
        else
            t->height = n->height + 1;

        return t;
    }

    node * rotateLeft(node *n) {
        if( n == nullptr || n->right == nullptr )
            return n;

        // perform the rotation
        node *t = n->right;
        n->right = t->left;
        t->left = n;

        // after the rotation n is the right child of t
        // so we need to update n first, then t
        update(n);
        update(t);

        // Set heights
        if( n->left != nullptr && n->right != nullptr )
            n->height = max(n->left->height, n->right->height) + 1;
        else if( n->left != nullptr)
            n->height = n->left->height + 1;
        else if( n->right != nullptr )
            n->height = n->right->height + 1;
        else
            n->height = 1;

        if( t->right != nullptr )
            t->height = max(n->height, t->right->height) + 1;
        else
            t->height = n->height + 1;

        return t;
    }

    node * checkHeights(node *n) {
        if( n == nullptr )
            return n;

        update(n);

        if( n->left == nullptr && n->right == nullptr ) {
            n->height = 1;
            return n;
        } else if( n->left == nullptr ) {
            n->height = n->right->height + 1;
            if( n->right->height >= 2 ) {
                if( n->right->left != nullptr && (n->right->right == nullptr || n->right->left->height > n->right->right->height) )
                    n->right = rotateRight(n->right);
                return rotateLeft(n);
            }
        } else if(n->right == nullptr) {
            n->height = n->left->height + 1;
            if( n->left->height >= 2 ) {
                if( n->left->right != nullptr && (n->left->left == nullptr || n->left->right->height > n->left->left->height) )
                    n->left = rotateLeft(n->left);
                return rotateRight(n);
            }
        } else {
            n->height = max(n->left->height, n->right->height) + 1;
            if( abs(n->left->height - n->right->height ) >= 2) {
                if( n->left->height > n->right->height ) {
                    if( n->left->right != nullptr && (n->left->left == nullptr || n->left->right->height > n->left->left->height) )
                        n->left = rotateLeft(n->left);
                    return rotateRight(n);
                } else {
                    if( n->right->left != nullptr && (n->right->right == nullptr || n->right->left->height > n->right->right->height) )
                        n->right = rotateRight(n->right);
                    return rotateLeft(n);
                }
            }
        }
        return n;
    }

    node * insert(node *n, int idx, int val) {
        // Create and insert node
        if( n == nullptr ) {
            n = new node;
            // n->key = key;

            n->_val = val;
            n->_xor = val;
            n->_size = 1;
            n->_reversed = false;

            n->height = 1;
            return n;
        }

        // Insert into appropriate subtree
        /*
        if(n->key <= key)
            n->right = insert(n->right, key);
        else
            n->left = insert(n->left, key);
        */

        push(n);

        int _key = get_size(n->left);
        if( idx <= _key )
            n->left = insert(n->left, idx, val);
        else
            n->right = insert(n->right, idx - (_key + 1), val);

        // Recalculate heights and rotate
        return checkHeights(n);
    }

	// tree2 is tree with smaller keys
    // tree2 - mergenode - tree1
    node * mergeWithNode(node *tree1, node *tree2, node *mergeNode) {
        push(tree1);
        push(tree2);

        if( mergeNode == nullptr )
            return tree1;

        if( tree1 == nullptr && tree2 == nullptr )
            return mergeNode;
        else if( tree1 == nullptr )
        {
            // int t = mergeNode->key;
            // tree2 = insert(tree2, t);
            int _idx = get_size(tree2);
            int _val = mergeNode->_val;
            tree2 = insert(tree2, _idx, _val);
            delete mergeNode;
            return tree2;
        }
        else if(tree2 == nullptr)
        {
            // int t = mergeNode->key;
            // tree1 = insert(tree1, t);
            int _idx = 0;
            int _val = mergeNode->_val;
            tree1 = insert(tree1, _idx, _val);
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

    // Tree1 is initial tree, as well as final larger tree
    node * breakTree(int idx, node **tree1, node **tree2) {
        push((*tree1));
        push((*tree2));

        if(tree1 == nullptr)
            return nullptr;

        // Move to appropriate node
        // then store subtree in appropriate tree

        int _key = get_size((*tree1)->left);
        node * n;

        if( idx > _key )
        {
            // we are going to the right

            n = breakTree(idx - (_key + 1), &(*tree1)->right, tree2);
            node *t = (*tree1)->right;
            if( (*tree2) != nullptr )
            {
                (*tree2) = mergeWithNode((*tree2), (*tree1)->left, (*tree1));
            }
            else
            {
                // there were no 'keys' in the right subtree <= index
                // so we make our left subtree tree2
                // and we are inserting us

                (*tree2) = (*tree1)->left;
                // (*tree2) = insert((*tree2), (*tree1)->key);
                int _idx = get_size((*tree2));
                int _val = (*tree1)->_val;
                (*tree2) = insert((*tree2), _idx, _val);
                delete (*tree1);
            }
            (*tree1) = t;

        } else if( idx < _key ) {
            // we are going to the left

            n = breakTree(idx, &(*tree1)->left, tree2);
            if( (*tree1)->left != nullptr && (*tree1)->right != nullptr )
                (*tree1) = mergeWithNode((*tree1)->right, (*tree1)->left, (*tree1));
            else
            {
                if( (*tree1)->left == nullptr )
                {
                    node* t = (*tree1);
                    (*tree1) = (*tree1)->right;
                    // (*tree1) = insert((*tree1), t->key);
                    int _idx = 0;
                    int _val = t->_val;
                    (*tree1) = insert((*tree1), _idx, _val);
                    delete t;
                }
                else if( (*tree1)->right == nullptr )
                {
                    node *t = (*tree1);
                    (*tree1) = (*tree1)->left;
                    // (*tree1) = insert((*tree1), t->key);
                    int _idx = get_size(t);
                    int _val = t->_val;
                    (*tree1) = insert((*tree1), _idx, _val);
                    delete t;
                }
            }

        } else {
            n = (*tree1);

            (*tree2) = (*tree1)->left;
            (*tree1) = (*tree1)->right;

            // delete n;

            n->_xor = n->_val;
            n->_size = 1;
            n->height = 1;
            n->left = nullptr;
            n->right = nullptr;
        }

        return n;
    }

    // debug
    void inorder(node * node) {
        if( node == nullptr )
            return;

        inorder(node->left);

        int key = get_size(node->left);
        cout << key << "(val:" << node->_val << ", xor:" << node->_xor << ") ";

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
                    int key = get_size(q.front()->left);
                    //cout << key << "(" << q.front()->height << ")";
                    cout << q.front()->_val << "(" << q.front()->_xor << ")";

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

public:
    vector<int> getResults(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();

        // build initial AVLTree (AVL Tree)
        // but not based on keys, but index as the key
        node * root = nullptr;
        for(int i = 0; i < n; ++i)
            root = insert(root, i, nums[i]);

        // debug
        // inorder(root); cout << endl;
        // disp(root); cout << endl;

        vector<int> ans;

        int q_sz = queries.size();
        for(int i = 0; i < q_sz; ++i) {
            if( queries[i][0] == 1 ) {
                // Update query
                int index = queries[i][1];
                int value = queries[i][2];

                // split the tree at index, which will remove that key
                // from the tree and return it to us
                // then change that key's value and
                // merge the two trees and merge node

            	// tree2 will contain smaller keys
	            node * tree2 = nullptr;
	            node * m = breakTree(index, &root, &tree2);

                m->_val = value;
                m->_xor = value;

                root = mergeWithNode(root, tree2, m);

                // cout << "after update query i " << i << " index " << index << " new_val " << value << endl;
                // inorder(root); cout << endl;
                // disp(root); cout << endl;

            } else {
                // queries[i][0] == 2 Range XOR query
                // queries[i][0] == 3 Reverse Subarray query

                // Reverse is same as for the Range XOR query
                // we need to split our tree, and then
                // on the relevant part (root node of that part)
                // we reverse it
                // we do reversing lazyly
                // reversing does neither change _xor, _size nor height
                // but it does change the 'keys' as the number
                // of nodes in left and right tree maybe be different

                // if a node is currently marked as reversed, and
                // we are marking it again, then we basically are saying
                // to not reverse it

                int left  = queries[i][1];
                int right = queries[i][2];

                if( left == 0 && right == n-1 ) {
                    // one part
                    // 0...n-1
                    if( queries[i][0] == 2 )
                        ans.push_back(root->_xor);
                    else // queries[i][0] == 3
                        root->_reversed ^= true;

                } else if( left == 0 ) {
                    // two parts
                    // left part   right part
                    // 0...right   r+1...n-1
                    // xor of left part is our answer

                    // tree2 will contain smaller keys
                    node * tree2 = nullptr; // left part
                    node * m = breakTree(right+1, &root, &tree2);

                    if( queries[i][0] == 2 )
                        ans.push_back(get_xor(tree2));
                    else // queries[i][0] == 3
                        tree2->_reversed ^= true;

                    root = mergeWithNode(root, tree2, m);

                } else if( right == n-1 ) {
                    // two parts
                    // left part   right part
                    // 0...left-1  left...n-1
                    // xor of right part is our answer

                    // tree2 will contain smaller keys
                    node * tree2 = nullptr; // left part
                    node * m = breakTree(left-1, &root, &tree2);

                    if( queries[i][0] == 2 )
                        ans.push_back(get_xor(root));
                    else // queries[i][0] == 3
                        root->_reversed ^= true;

                    root = mergeWithNode(root, tree2, m);

                } else {
                    /*  we need to split our tree into three parts:
                     *    left part     middle part    right part
                     *  -------------  -------------   -------------
                     *    0...left-1    left...right   right+1...n-1
                     *
                     *  xor of the middle part is out answer
                     */

                    node * tree2 = nullptr; // left part
                    node * m2 = breakTree(left-1, &root, &tree2);

                    // our split index must be calculated as we removed left nodes
                    // let us say that we have n = 7 nodes
                    // let our range be left = 2 and right = 4
                    // 0  1  2  3  4  5  6
                    //       -------
                    // so far we have split into two parts
                    // 0  1  2  3  4  5  6
                    // ====  =============
                    //         root is now original range 2...6 but 0 indexed:
                    //       0  1  2  3  4
                    //       hence we need to calculate our new split point
                    //       right + 1 - left
                    //         4   + 1 -   2  = 3 in our example

                    node * tree3 = nullptr; // middle part
                    node * m3 = breakTree((right+1)-left, &root, &tree3);


                    // cout << "tree to answer range query or reverse after query i " << i << " left " << left << " right " << right << endl;
                    // inorder(tree3); cout << endl;
                    // disp(tree3); cout << endl;

                    if( queries[i][0] == 2 )
                        ans.push_back(get_xor(tree3));
                    else // queries[i][0] == 3
                        tree3->_reversed ^= true;

                    root = mergeWithNode(root, tree3, m3);
                    root = mergeWithNode(root, tree2, m2);
                }

            }
        }

        return ans;
    }
};
