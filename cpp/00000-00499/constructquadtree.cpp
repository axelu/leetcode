
// 427. Construct Quad Tree
// https://leetcode.com/problems/construct-quad-tree/




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
private:
    Node* rec(vector<vector<int>>& grid, int il, int jl, int ih, int jh) {
        // il and jl = i,j of top left corner
        // ih and jh = i,j of bottom right corner
        if( il == ih ) // we are down to a single cell
            return new Node(grid[il][jl],true);


        // divide
        int midi = il + ((ih-il)/2);
        int midj = jl + ((jh-jl)/2);
        // top left
        Node* ntl = rec(grid,il,jl,midi,midj);
        // top right
        Node* ntr = rec(grid,il,midj+1,midi,jh);
        // bottom left
        Node* nbl = rec(grid,midi+1,jl,ih,midj);
        // bottom right
        Node* nbr = rec(grid,midi+1,midj+1,ih,jh);

        // merge/combine
        // our node can only be a leaf node if all four are leave nodes
        // AND all four have the same value
        Node* ret;
        if( ntl->isLeaf && ntr->isLeaf && nbl->isLeaf && nbr->isLeaf &&
            ( (  ntl->val &&  ntr->val &&  nbl->val &&  nbr->val  ) ||
              ( !ntl->val && !ntr->val && !nbl->val && !nbr->val ) ) ) {
            ret = new Node(ntl->val,true);
            delete ntl; delete ntr;
            delete nbl; delete nbr;
        } else {
            ret = new Node(false,false,ntl,ntr,nbl,nbr);
        }
        return ret;
    }

public:
    Node* construct(vector<vector<int>>& grid) {
        // n == grid.length == grid[i].length
        // n == 2^x where 0 <= x <= 6
        int n = grid.size();
        return rec(grid,0,0,n-1,n-1);
    }
};
