
// 2342. Max Sum of a Pair With Equal Sum of Digits
// https://leetcode.com/problems/max-sum-of-a-pair-with-equal-sum-of-digits/



class Solution {
public:
    int maximumSum(vector<int>& nums) {
        sort(nums.begin(),nums.end(),greater<int>());

        int ans = -1;

        unordered_map<int,pair<int,int>> um;
        for(int i: nums) {

            int x = i;
            int t = 0;
            while( x > 0 ) {
                t = t + (x % 10);
                x /= 10;
            }
            auto p = um.insert({t,{i,-1}});
            if( !p.second && p.first->second.second == -1 ) {
                p.first->second.second = i;
                ans = max(ans, p.first->second.first + p.first->second.second);
            }
        }

        return ans;
    }
};
