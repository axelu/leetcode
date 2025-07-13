
// 3520. Minimum Threshold for Inversion Pairs Count
// https://leetcode.com/problems/minimum-threshold-for-inversion-pairs-count/




class Solution {
private:
    int sum(vector<int>& bit, int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    int sum(vector<int>& bit, int l, int r) {
        return sum(bit, r) - sum(bit, l - 1);
    }

    void add(vector<int>& bit, int idx, int delta) {
        int n = bit.size();
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }

    bool solve(vector<int>& nums, int k, map<int,int>& dic, int x) {
        // cout << "solve x " << x << endl;
        int n = nums.size();
        int dic_sz = dic.size();

        // binary indexed tree, 0-indexed, range query (sum), point update (addition)
        vector<int> bit(dic_sz,0);

        int val = nums[n-1];
        int idx = dic[val];
        add(bit, idx, 1);

        int cnt = 0;

        for(int i = n-2; i >= 0; --i) {
            val = nums[i];
            idx = dic[val];

            // how many values have we seen in nums,
            // that are between  val-x ... val-1 inclusive ?
            auto itu = dic.find(val);
            if( itu != dic.begin() ) {
                --itu;
                int valu = itu->first;
                if( valu >= val - x ) {
                    int r = dic[valu];

                    auto itl = dic.lower_bound(val-x);
                    int vall = itl->first;
                    int l = dic[vall];

                    cnt += sum(bit, l, r);

                    if( cnt >= k )
                        return true;
                }
            }

            add(bit, idx, 1);
        }

        return false;
    }


    // binary search
    int search(int s, int e, vector<int>& nums, int k, map<int,int>& dic) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        bool f = solve(nums, k, dic, mid);
        if( f ) {
            // can we do better?
            int t = search(s, mid-1, nums, k, dic);
            return t != -1 ? t : mid;
        }

        return search(mid+1, e, nums, k, dic);
    }

public:
    int minThreshold(vector<int>& nums, int k) {
        int n = nums.size(); // 1 <= n <= 1e4

        // formula number of pairs n * (n-1)/2
        long mx_pairs = (long)n * ((n-1)/2.0);
        if( k > mx_pairs )
            return -1;

        set<int> st;
        for(int x: nums)
            st.insert(x);

        int mn = *st.begin();
        int mx = *st.rbegin();
        if( mn == mx )
            return -1;

        // our answer is somewhere between 1 and (mx-mn)
        // cout << "mx " << mx << " mn " << mn << " mx-mn " << mx-mn << endl;

        // coordinate compression
        // we have at most n unique values
        int idx = 0;
        map<int,int> dic; // unique nums, idx
        for(int i: st)
            dic[i] = idx++;

        return search(1, mx-mn, nums, k, dic);
    }
};
