
// 2560. House Robber IV
// https://leetcode.com/problems/house-robber-iv/





class Solution {
private:
    int n;

    bool solve(vector<int>& nums, int mx, int k) {
        int lst = -2;
        for(int i = 0; i < n; ++ i) {
            if( nums[i] <= mx && lst <= i-2 ) {
                lst = i;
                --k;
                if( k == 0 )
                    return true;
            }
        }

        return false;
    }

    // binary search
    int search(vector<int>& nums, int s, int e, set<int>& st, int k) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        auto it = st.begin();
        advance(it,mid);
        bool f = solve(nums,*it,k);
        if( f ) {
            // can we do better?
            int t = search(nums,s,mid-1,st,k);
            return t != -1 ? t : mid;
        }

        return search(nums,mid+1,e,st,k);
    }

public:
    int minCapability(vector<int>& nums, int k) {
        n = nums.size();

        set<int> st;
        for(int val: nums)
            st.insert(val);

        // our solution is between min and max
        int offset = search(nums,0,st.size()-1,st,k);
        auto it = st.begin();
        advance(it,offset);
        return *it;
    }
};
