
// 3264. Final Array State After K Multiplication Operations I
// https://leetcode.com/problems/final-array-state-after-k-multiplication-operations-i/




class Solution {
public:
    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
        int n = nums.size();

        // array<int,2> val, pos
        auto cmp = [](const array<int,2>& a, const array<int,2>& b) {
            if( a[0] > b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] > b[1] ) {
                    return true;
                }
            }
            return false;
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq(cmp);

        for(int i = 0; i < n; ++i)
            pq.push({nums[i],i});

        for(int i = 0; i < k; ++i) {
            int val = pq.top()[0];
            int pos = pq.top()[1];
            pq.pop();

            val *= multiplier;

            pq.push({val, pos});
        }

        vector<int> ans(n);
        while( !pq.empty() ) {
            int val = pq.top()[0];
            int pos = pq.top()[1];
            pq.pop();

            ans[pos] = val;
        }

        return ans;
    }
};
