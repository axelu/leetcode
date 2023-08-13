
// 2519. Count the Number of K-Big Indices
// https://leetcode.com/problems/count-the-number-of-k-big-indices/





class Solution {
private:
    int bit[100002]; // binary indexed tree bit, 0 indexed
    int n = 100001;

    // point query
    int get(int r) { // sum of range [0,r] inclusive
        int ret = 0;
        for(; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    // range update [idx,n] inclusive
    void add(int idx, int delta) {
        for(; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }

public:
    int kBigIndices(vector<int>& nums, int k) {
        int nums_sz = nums.size();
        int ans = 0;

        // left to right
        memset(bit,0,sizeof bit);
        int l2r[n];memset(l2r,0,sizeof l2r);
        for(int i = 0; i < nums_sz; ++i) {
            l2r[i] = get(nums[i]);
            add(nums[i]+1,1);
        }
        // debug
        /*
        for(int i = 0; i < nums_sz; ++i)
            cout << i << ":" << l2r[i] << " ";
        cout << endl;
        */

        // right to left
        memset(bit,0,sizeof bit);
        for(int i = nums_sz-1; i >= 0; --i) {
            if( l2r[i] >= k && get(nums[i]) >= k )
                ++ans;
            add(nums[i]+1,1);
        }

        return ans;
    }
};
