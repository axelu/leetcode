
// 3780. Maximum Sum of Three Numbers Divisible by Three
// https://leetcode.com/problems/maximum-sum-of-three-numbers-divisible-by-three/




class Solution {
public:
    int maximumSum(vector<int>& nums) {
        int n = nums.size();

        // collect values by remainder 3, so either 0, 1 or 2
        // if the sum of three elements is divisible by 3
        // then the sum of the remainders of the 3 addends
        // must be divisible by 3
        // that leaves us with these options
        // remainders  sum remainders
        // 0 0 0       0
        // 0 1 2       3
        // 1 1 1       3
        // 2 2 2       6

        multiset<int> rem[3];
        for(int x: nums) {
            int _rem = x % 3;
            if( _rem == 2 )
                rem[2].insert(x);
            else if( _rem == 1 )
                rem[1].insert(x);
            else
                rem[0].insert(x);
        }

        int ans = 0;

        // 0 0 0
        if( rem[0].size() >= 3 ) {
            auto it = rem[0].rbegin();
            int t = *it++;
            t += *it++;
            t += *it;
            ans = max(ans, t);
        }
        // 1 1 1
        if( rem[1].size() >= 3 ) {
            auto it = rem[1].rbegin();
            int t = *it++;
            t += *it++;
            t += *it;
            ans = max(ans, t);
        }
        // 2 2 2
        if( rem[2].size() >= 3 ) {
            auto it = rem[2].rbegin();
            int t = *it++;
            t += *it++;
            t += *it;
            ans = max(ans, t);
        }
        // 0 1 2
        if( !rem[0].empty() && !rem[1].empty() & !rem[2].empty() ) {
            int t = *rem[0].rbegin();
            t += *rem[1].rbegin();
            t += *rem[2].rbegin();
            ans = max(ans, t);
        }

        return ans;
    }
};
