
// 558. Logical OR of Two Binary Grids Represented as Quad-Trees
// https://leetcode.com/problems/logical-or-of-two-binary-grids-represented-as-quad-trees/




/*
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/

class Solution {
public:
    Node* intersect(Node* a, Node* b) {

        /* Node* a   | Node* b   | action
         * ----------+-----------+---------------------------------------------
         * leaf      | leaf      | apply Logical OR and return
         * leaf      | non-leaf  | if leaf val=1, leaf wins and return
         *           |           | if leaf val=0, non-leaf wins and return
         * non-leaf  | leaf      | if leaf val=1, leaf wins and return
         *           |           | if leaf val=0, non-leaf wins and return
         * non-leaf  | non-leaf  | keep going
        */

        if( a->isLeaf && b->isLeaf ) {
            return a->val ? a : b;
        } else if( a->isLeaf && !b->isLeaf ) {
            return a->val ? a : b;
        } else if (!a->isLeaf && b->isLeaf ) {
            return b->val ? b : a;
        } else {
            Node* ntl = intersect(a->topLeft,b->topLeft);
            Node* ntr = intersect(a->topRight,b->topRight);
            Node* nbl = intersect(a->bottomLeft,b->bottomLeft);
            Node* nbr = intersect(a->bottomRight,b->bottomRight);

            // merge/combine
            // our node can only be a leaf node if all four are leave nodes
            // AND all four have the same value
            Node* ret;
            if( ntl->isLeaf && ntr->isLeaf && nbl->isLeaf && nbr->isLeaf &&
                ( (  ntl->val &&  ntr->val &&  nbl->val &&  nbr->val  ) ||
                  ( !ntl->val && !ntr->val && !nbl->val && !nbr->val ) ) ) {
                ret = new Node(ntl->val,true);
            } else {
                ret = new Node(false,false,ntl,ntr,nbl,nbr);
            }
            return ret;
        }
    }
};
