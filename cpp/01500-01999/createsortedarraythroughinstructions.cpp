
// 1649. Create Sorted Array Through Instructions
// https://leetcode.com/problems/create-sorted-array-through-instructions/
// day 10 January 2021 challenge
// https://leetcode.com/explore/featured/card/january-leetcoding-challenge-2021/580/week-2-january-8th-january-14th/3599/



class Solution {
private:
    int MOD = 1000000007;
    int mx;
    int tree[100005];

    void update(int idx, int val) {
        while(idx <= mx) {
            tree[idx] += val;
            idx += (idx & -idx);
        }
    }

    int q(int ind) { // query range [1, ind]
        int ans = 0;
        while(ind > 0) {
            ans += tree[ind];
            ind -= (ind & -ind);
        }
        return ans;
    }
public:
    int createSortedArray(vector<int>& instructions) {
        // Fenwick Tree
        size_t n = instructions.size();
        if( n == 1 ) return 0;

        memset(tree,0,sizeof tree);

        mx = *max_element(begin(instructions),end(instructions));
        int idx,l,r;
        int ans = 0;
        for(int i = 0; i < n; ++i) {
            idx = instructions[i];
            l = q(idx - 1);
            r = q(mx) - q(idx);
            ans = (ans + min(l, r)) % MOD;
            update(idx, 1);
        }
        return ans;
    }
};
