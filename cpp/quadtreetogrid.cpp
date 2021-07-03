




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
    vector<vector<int>> quadtree2grid(Node* qt) {
        if( qt->isLeaf ) {
            return {{qt->val}};
        }

        // top left
        vector<vector<int>> gtl = quadtree2grid(qt->topLeft);
        // top right
        vector<vector<int>> gtr = quadtree2grid(qt->topRight);
        // bottom left
        vector<vector<int>> gbl = quadtree2grid(qt->bottomLeft);
        // bottom right
        vector<vector<int>> gbr = quadtree2grid(qt->bottomRight);

        // merge / combine
        // the largest sub grid dictates the size of the returned grid
        int ngtl = gtl.size();
        int ngtr = gtr.size();
        int ngbl = gbl.size();
        int ngbr = gbr.size();
        int n = max({ngtl,ngtr,ngbl,ngbr})*2;

        vector<vector<int>> ret(n,vector<int>(n));
        int mid = n/2,i,j;
        // top left
        if( ngtl < mid ) {
            for(i = 0; i < mid; ++i)
                for(j = 0; j < mid; ++j)
                    ret[i][j] = gtl[0][0];
        } else {
            for(i = 0; i < mid; ++i)
                for(j = 0; j < mid; ++j)
                    ret[i][j] = gtl[i][j];
        }
        // top right
        if( ngtr < mid ) {
            for(i = 0; i < mid; ++i)
                for(j = mid; j < n; ++j)
                    ret[i][j] = gtr[0][0];
        } else {
            for(i = 0; i < mid; ++i)
                for(j = mid; j < n; ++j)
                    ret[i][j] = gtr[i][j-mid];
        }
        // bottom left
        if( ngbl < mid ) {
            for(i = mid; i < n; ++i)
                for(j = 0; j < mid; ++j)
                    ret[i][j] = gbl[0][0];
        } else {
            for(i = mid; i < n; ++i)
                for(j = 0; j < mid; ++j)
                    ret[i][j] = gbl[i-mid][j];
        }
        // bottom right
        if( ngbr < mid ) {
            for(i = mid; i < n; ++i)
                for(j = mid; j < n; ++j)
                    ret[i][j] = gbr[0][0];
        } else {
            for(i = mid; i < n; ++i)
                for(j = mid; j < n; ++j)
                    ret[i][j] = gbr[i-mid][j-mid];
        }

        return ret;
    }

public:
    vector<vector<int>> quadtreetogrid(Node* quadTree) {
        // create grid from Quadtree
        vector<vector<int>> grid = quadtree2grid(quadTree);

        return grid;
    }
};
