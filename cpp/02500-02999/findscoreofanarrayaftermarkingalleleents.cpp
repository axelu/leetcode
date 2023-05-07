
// 2593. Find Score of an Array After Marking All Elements
// https://leetcode.com/problems/find-score-of-an-array-after-marking-all-elements/



class Solution {
public:
    long long findScore(vector<int>& nums) {
        int n = nums.size();

        auto cmp = [](const array<int,2>& a, const array<int,2>& b){
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

        long long ans = 0;

        vector<bool> seen(n,false);

        while( !pq.empty() ) {

            long val = pq.top()[0];
            int idx = pq.top()[1];
            pq.pop();

            if( seen[idx] )
                continue;

            ans = ans + val;

            seen[idx] = true;
            if( idx - 1 >= 0 )
                seen[idx-1] = true;
            if( idx + 1 < n )
                seen[idx+1] = true;
        }

        return ans;
    }
};
