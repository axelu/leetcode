
// Path In Zigzag Labelled Binary Tree
// https://leetcode.com/problems/path-in-zigzag-labelled-binary-tree/


class Solution {
public:
    vector<int> pathInZigZagTree(int label) {
        // 1 <= label <= 10^6

        // determine number of rows (rows indexed at 0) and
        // position of node with label 'label' in row
        int row = 0; // 0 indexed
        int pe = 0;  // prior row end node (left to right)
        int pos;
        while(true) {
            int n = pow(2,row); // number of nodes in current row
            int s = pe + 1;     // start node of current row (left to right)
            int e = pe + n;     // end node of current row (left to right)

            if( pe < label && e + 1 > label ) {
                // node aka label is in this row
                // determine position (0 indexed) of label in row

                pos = label - s;
                if ( row % 2 != 0 ) {
                    // odd rows numbered right to left
                    pos = n - 1 - pos;
                }
                break;
            }
            pe = e;
            ++row;
        }

        // debug
        // cout << "row " << row << " pos " << pos << endl;

        vector<int> r = {label};

        for(row = row - 1; row >= 0; --row) {
            int n = pow(2,row); // number of nodes in current row
            pe = pe - n;        // end node of prior row (left to right)
            int s = pe + 1;     // start node of current row (left to right)
            int e = pe + n;     // end node of current row (left to right)

            // calculate position of 'parent' node
            pos = pos / 2;

            // calculate label of that position
            label = ( row % 2 == 0 ) ? s + pos : e - pos;

            r.insert(r.begin(),label);
        }

        return r;
    }
};
