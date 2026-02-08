
// 3781. Maximum Score After Binary Swaps
// https://leetcode.com/problems/maximum-score-after-binary-swaps/



class Solution {
private:
    pair<int,int> t[200000]; // segment tree, memory efficient implementation, max range query, point update



    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v].first = a[tl];
            t[v].second = tl;
        } else {
            int tm = (tl + tr) / 2;
            build(a, v+1, tl, tm);
            build(a, v+2*(tm-tl+1), tm+1, tr);
            t[v] = max(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }

    pair<int,int> get_max(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return {-1,-1};
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return max(get_max(v+1, tl, tm, l, min(r, tm)),
                   get_max(v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r));
    }

    void update(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            t[v].first = new_val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v+1, tl, tm, pos, new_val);
            else
                update(v+2*(tm-tl+1), tm+1, tr, pos, new_val);
            t[v] = max(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }

public:
    long long maximumScore(vector<int>& nums, string s) {
        int n = nums.size(); // nums.size() == s.size();

        // we cannot do any swaps if all s[i] == 0 or all s[i] == 1
        // if all s[i] == 1, we collect all nums[i]
        // we cannot do any swaps in trailing 0's
        // we cannot do any swaps in leading 1's
        // example 1111000, so we only pick app the values of 1's
        // like nums = [2,1,2,3,10,10,10], s = "1111000" -> ans = 8
        // in other words, we can move 1's left
        // so we are looking for blocks starting at a 0, followed by 1s
        // let v be the number of ones in such a block
        // within such a block we can harvest the v largest values

        long long ans = 0;

        int leftmost0 = -1;
        for(int i = 0; i < n; ++i) {
            if( s[i] == '0' ) {
                leftmost0 = i;
                break;
            } else {
                ans += (long long)nums[i];
            }
        }
        if( leftmost0 == -1 )
            return ans;

        int rightmost1 = -1;
        for(int i = n-1; i >= 0; --i) {
            if( s[i] == '1' ) {
                rightmost1 = i;
                break;
            }
        }
        if( rightmost1 == -1 )
            return 0;

        build(nums, 1, 0, n-1);

        vector<int> ones; // 1 indices
        for(int i = leftmost0; i <= rightmost1; ++i)
            if( s[i] == '1' )
                ones.push_back(i);

        for(int i = 0; i < ones.size(); ++i) {
            // get max in range[leftmost0,ones[i]]
            auto p = get_max(1, 0, n-1, leftmost0, ones[i]);
            ans += (long long)p.first;
            // mark as harvested by setting to 0
            update(1, 0, n-1, p.second, 0);
        }

        return ans;
    }
};
