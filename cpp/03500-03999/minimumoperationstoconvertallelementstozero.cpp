
// 3542. Minimum Operations to Convert All Elements to Zero
// https://leetcode.com/problems/minimum-operations-to-convert-all-elements-to-zero/

// see also 3229. Minimum Operations to Make Array Equal to Target 
// https://leetcode.com/problems/minimum-operations-to-make-array-equal-to-target/

class Solution {
private:
    const int INF = 100002; // 0 <= nums[i] <= 1e5

    int t[200000]; // segment tree memory efficient indexing; min, range query

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v+1, tl, tm);
            build(a, v+2*(tm-tl+1), tm+1, tr);
            t[v] = min(t[v+1], t[v+2*(tm-tl+1)]);
        }
    }

    int get(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return INF;
        if (l == tl && r == tr)
            return t[v];

        int tm = (tl + tr) / 2;
        int lft = get(v+1, tl, tm, l, min(r, tm));
        int rgt = get(v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r);
        return min(lft, rgt);
    }

    vector<int> positions[100001];
   
    int rec(vector<int>& nums, int n, int b, int e) {
        if( e < 0 )
            return 0;
        if( b == e )
            return nums[b] == 0 ? 0 : 1;

        int ret = 0;

        // get min in range [b,e] inclusive
        int mn = get(1, 0, n-1, b, e);
        auto it = lower_bound(positions[mn].begin(), positions[mn].end(), b);
        int pos = *it;

        if( nums[pos] != 0 )
            ret = 1;

        // for each range left, in between and right repeat
        // left
        if( pos > b ) {
            ret += rec(nums, n, b, pos-1);
        }
        // in between
        while( next(it) != positions[mn].end() && *(next(it)) <= e ) {
            if( *it + 1 < *(next(it)) ) {
                ret += rec(nums, n, *it + 1, *(next(it)) - 1);
            }
            ++it;
        }
        // right
        if( it != positions[mn].end() && *it < e ) {
            ret += rec(nums, n, *it + 1, e);
        }

        return ret;
    }



public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return nums[0] == 0 ? 0 : 1;

        for(int i = 0; i < n; ++i)
            positions[nums[i]].push_back(i);

        build(nums,1,0,n-1);

        return rec(nums, n, 0, n-1);
    }
};




// passes 954/968 test cases, then TLE as of 5/23/2025


class Solution {
private:
    const int INF = 100002; // 0 <= nums[i] <= 1e5

    // TODO use a segment tree to speed this up
    vector<int> get_min_pos(vector<int>& nums, int b, int e) {
        vector<int> ret;

        int mn = INF;
        for(int i = b; i <= e; ++i) {
            if( nums[i] < mn ) {
                mn = nums[i];
                ret.clear();
                ret.push_back(i);
            } else if( nums[i] == mn ) {
                ret.push_back(i);
            }
        }

        return ret;
    }

    int rec(vector<int>& nums, int b, int e) {

        int ret = 0;

        // get min positions in range [b,e] inclusive
        vector<int> mn_positions = get_min_pos(nums, b, e);
        int mn_positions_sz = mn_positions.size();
        if( mn_positions_sz != 0 && nums[mn_positions[0]] != 0 )
            ret = 1;

        // for each range left, in between and right repeat
        // left
        if( mn_positions_sz != 0 && mn_positions[0] > b ) {
            ret += rec(nums, b, mn_positions[0]-1);
        }
        // in between
        for(int i = 0; i < mn_positions_sz - 1; ++i) {
            if( mn_positions[i] + 1 < mn_positions[i+1] ) {
                ret += rec(nums, mn_positions[i] + 1, mn_positions[i+1] - 1);
            }
        }
        // right
        if( mn_positions_sz != 0 && mn_positions[mn_positions_sz -1] < e ) {
            ret += rec(nums, mn_positions[mn_positions_sz -1] + 1, e);
        }

        return ret;
    }



public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return nums[0] == 0 ? 0 : 1;

        return rec(nums, 0, n-1);
    }
};
