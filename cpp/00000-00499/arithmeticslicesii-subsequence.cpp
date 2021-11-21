
// 446. Arithmetic Slices II - Subsequence
// https://leetcode.com/problems/arithmetic-slices-ii-subsequence/
// day 10 Sept 2021 challenge
// https://leetcode.com/explore/challenge/card/september-leetcoding-challenge-2021/637/week-2-september-8th-september-14th/3970/





class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size();

        long long ans = 0; // -2^31 <= nums[i] <= 2^31 - 1, hence using long long

        // store for a given index, how many arithmetic sequence with a given difference we found
        vector<map<long long,int>> mp(n);
        long long diff,cnt;
        for(int i = 1; i < n; ++i)
            for(int j = 0; j < i; ++j) {

                diff = (long long)nums[i] - (long long)nums[j];

                cnt = 0;
                if( mp[j].find(diff) != mp[j].end() )
                    cnt = mp[j][diff];


                mp[i][diff] += cnt + 1;

                ans += cnt;
            }


        return ans;
    }
};
