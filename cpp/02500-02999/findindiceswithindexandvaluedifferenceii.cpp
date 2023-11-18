
// 2905. Find Indices With Index and Value Difference II
// https://leetcode.com/problems/find-indices-with-index-and-value-difference-ii/





class Solution {
public:
    vector<int> findIndices(vector<int>& nums, int indexDifference, int valueDifference) {
        int n = nums.size();
        int k = n-indexDifference;
        if( k <= 0 )
            return {-1,-1};

        pair<int,int> mnr2l[n]; // val,idx
        mnr2l[n-1] = {nums[n-1],n-1};
        pair<int,int> mxr2l[n]; // val,idx
        mxr2l[n-1] = {nums[n-1],n-1};
        for(int i = n-2; i >= 0; --i) {
            mnr2l[i] = nums[i] < mnr2l[i+1].first ? make_pair(nums[i],i) : mnr2l[i+1];
            mxr2l[i] = nums[i] > mxr2l[i+1].first ? make_pair(nums[i],i) : mxr2l[i+1];
        }

        int mnl2r = INT_MAX;
        int mxl2r = INT_MIN;
        for(int i = 0, j = indexDifference; j < n; ++i,++j) {
            mnl2r = min(mnl2r,nums[i]);
            mxl2r = max(mxl2r,nums[i]);

            if( abs(mnl2r - mxr2l[j].first) >= valueDifference )
                return {i,mxr2l[j].second};
            else if( abs(mxl2r - mnr2l[j].first) >= valueDifference )
                return {i,mnr2l[j].second};
        }

        return {-1,-1};
    }
};
