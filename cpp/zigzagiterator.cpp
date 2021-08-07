
// 281. Zigzag Iterator
// https://leetcode.com/problems/zigzag-iterator/



class ZigzagIterator {
private:
    vector<int> * V1;
    vector<int> * V2;
    int n1,i,n2,j,nxt;
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        V1 = &v1; n1 = v1.size(); i = 0;
        V2 = &v2; n2 = v2.size(); j = 0;

        nxt = n1 > 0 ? 0 : 1;
    }

    int next() {
        int ret;
        if( nxt == 0 ) {
            // read current element from v1
            ret = (*V1)[i];
            // advance index in v1
            ++i;
            if( j < n2 )
                nxt = 1;
        } else {
            // read current element from v2
            ret = (*V2)[j];
            // advance index in v2
            ++j;
            if( i < n1 )
                nxt = 0;
        }
        return ret;
    }

    bool hasNext() {
        return i != n1 || j != n2;
    }
};

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */
