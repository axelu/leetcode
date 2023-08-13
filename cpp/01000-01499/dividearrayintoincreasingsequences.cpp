
// 1121. Divide Array Into Increasing Sequences
// https://leetcode.com/problems/divide-array-into-increasing-sequences/




class Solution {
private:
    bool solve1(vector<int>& nums, int k) {
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

        for(int i = 0; i < n; ++i) {
            if( pq.empty() || nums[i] <= pq.top()[0] ) {
                pq.push({nums[i],1});
            } else {
                int l = pq.top()[1];
                pq.pop();
                pq.push({nums[i],l+1});
            }
        }

        while( !pq.empty() ) {
            if( pq.top()[1] < k )
                return false;
            pq.pop();
        }

        return true;
    }

    bool solve2(vector<int>& nums, int k) {
        int n = nums.size();

        auto cmp = [](const array<int,2>& a, const array<int,2>& b){
            if( a[0] < b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] > b[1] ) {
                    return true;
                }
            }
            return false;
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq(cmp);

        for(int i = n-1; i >= 0; --i) {
            if( pq.empty() || nums[i] == pq.top()[0] ) {
                pq.push({nums[i],1});
            } else {
                int l = pq.top()[1];
                pq.pop();
                pq.push({nums[i],l+1});
            }
        }

        while( !pq.empty() ) {
            if( pq.top()[1] < k )
                return false;
            pq.pop();
        }

        return true;
    }

public:
    bool canDivideIntoSubsequences(vector<int>& nums, int k) {
        bool f = solve1(nums,k);
        if( !f )
           f = solve2(nums,k);

        return f;
    }
};
