
// 3624. Number of Integers With Popcount-Depth Equal to K II
// https://leetcode.com/problems/number-of-integers-with-popcount-depth-equal-to-k-ii/



// see 3621. Number of Integers With Popcount-Depth Equal to K I
// https://leetcode.com/problems/number-of-integers-with-popcount-depth-equal-to-k-i/

// initialize once
bool init = false;
int _popcountDepth[52];

class Solution {
private:
    int countSetBits(long long i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1LL;
            i >>= 1LL;
        }
        return count;
    }

    int rec(int i) {
        if( _popcountDepth[i] != -1 )
            return _popcountDepth[i];

        int setbits = countSetBits(i);
        return _popcountDepth[i] = 1 + rec(setbits);
    }

    array<int,5> t[200000]; // segment tree memory efficient indexing, range query (sum), point update

    array<int,5> combine(array<int,5>& a, array<int,5>& b) {
        array<int,5> ret;
        ret[0] = a[0] + b[0];
        ret[1] = a[1] + b[1];
        ret[2] = a[2] + b[2];
        ret[3] = a[3] + b[3];
        ret[4] = a[4] + b[4];
        return ret;
    }

    void build(vector<long long>& a, int v, int tl, int tr) {
        if (tl == tr) {
            if( a[tl] == 1LL ) {
                t[v][0] = 1;
                return;
            }
            int setbits = countSetBits(a[tl]);
            t[v][_popcountDepth[setbits]] = 1;
        } else {
            int tm = (tl + tr) / 2;
            build(a, v+1, tl, tm);
            build(a, v+2*(tm-tl+1), tm+1, tr);
            t[v] = combine(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }

    // range query (sum)
    array<int,5> get(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return array<int,5>({0,0,0,0,0});
        if (l == tl && r == tr)
            return t[v];

        int tm = (tl + tr) / 2;
        auto lft = get(v+1, tl, tm, l, min(r, tm));
        auto rgt = get(v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r);
        return combine(lft, rgt);
    }

    // point update
    void update(int v, int tl, int tr, int pos, long long new_val) {
        if (tl == tr) {
            t[v] = array<int,5>({0,0,0,0,0});
            if( new_val == 1LL ) {
                t[v][0] = 1;
                return;
            }
            int setbits = countSetBits(new_val);
            t[v][_popcountDepth[setbits]] = 1;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v+1, tl, tm, pos, new_val);
            else
                update(v+2*(tm-tl+1), tm+1, tr, pos, new_val);
            t[v] = combine(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }


public:
    vector<int> popcountDepth(vector<long long>& nums, vector<vector<long long>>& queries) {
        if( !init ) {
            init = true;

            memset(_popcountDepth,-1,sizeof _popcountDepth);
            _popcountDepth[1] = 1;
            for(int i = 2; i <= 51; ++i) {
                rec(i);
                // cout << "set bits " << i << " popcountDepth " << _popcountDepth[i] << endl;
            }
        }

        int n = nums.size();

        // with the constraints given, we know that the 1 <= popcountDepth <= 4 for each nums[i]
        // so we could make a segment tree that holds at each node the count of
        // popcountDepth 1, 2, 3 and 4 for the segment the node represents, 
        // the tree needs to support range query and point update

        memset(t, 0, sizeof t);
        build(nums, 1, 0, n-1);


        vector<int> ans;

        int q_sz = queries.size();
        for(int i = 0; i < q_sz; ++i) {
            if( queries[i][0] == 1LL ) {
                // Determine the number of indices j such that l <= j <= r and 
                // the popcount-depth of nums[j] is equal to k

                int l = queries[i][1];
                int r = queries[i][2];
                int k = queries[i][3];
                
                if( k == 5 ) {
                    ans.push_back(0);
                } else {
                    // query the tree
                    auto a = get(1, 0, n-1, l, r);
                    ans.push_back(a[k]);
                }

            } else { // queries[i][0] == 2LL
                // update query
                int idx = queries[i][1];
                long long val = queries[i][2];
                update(1, 0, n-1, idx, val);
            }
        }

        return ans;
    }
};
