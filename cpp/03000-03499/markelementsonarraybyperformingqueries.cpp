
// 3080. Mark Elements on Array by Performing Queries
// https://leetcode.com/problems/mark-elements-on-array-by-performing-queries/



class Solution {
public:
    vector<long long> unmarkedSumArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();

        vector<pair<int,int>> _nums(n);
        long long sum = 0LL;
        for(int i = 0; i < n; ++i) {
            _nums[i] = {nums[i],i};
            sum += (long long)nums[i];
        }
        sort(_nums.begin(),_nums.end(),[](const pair<int,int>& a, const pair<int,int>& b){
            if( a.first < b.first ) {
                return true;
            } else if( a.first == b.first ) {
                if( a.second < b.second ) {
                    return true;
                }
            }
            return false;
        });

        vector<bool> marked(n,false);
        int m = queries.size();
        vector<long long> ans(m);
        int _nums_idx = 0;
        for(int j = 0; j < m; ++j) {
            int i = queries[j][0];
            int k = queries[j][1];

            if( !marked[i] ) {
                sum -= (long long)nums[i];
                marked[i] = true;
            }

            while( _nums_idx < n && k > 0) {
                if( !marked[_nums[_nums_idx].second] ) {
                    sum -= (long long)_nums[_nums_idx].first;
                    marked[_nums[_nums_idx].second] = true;
                    --k;
                }
                ++_nums_idx;
            }

            ans[j] = sum;
        }

        return ans;
    }
};
