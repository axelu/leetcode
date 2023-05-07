
// 2606. Find the Substring With Maximum Cost
// https://leetcode.com/problems/find-the-substring-with-maximum-cost/




class Solution {
private:
    int maxSubArray(vector<int>::iterator first, vector<int>::iterator last) {

        if ( first == last ) return *first;

        // divide
        auto middle = first + (( last - first ) / 2);

        // conquer left side, right side and cross
        return max({maxSubArray(first, middle),
                    maxSubArray(middle + 1, last),
                    maxCross(first, middle, last)});
    }

    int maxCross(vector<int>::iterator first, vector<int>::iterator middle,
            vector<int>::iterator last) {

        // to the left from the middle!!!
        int tmp = 0;
        int lsum = INT_MIN;
        for (auto it = middle; it >= first; --it) {
            tmp += *it;
            if (tmp > lsum) lsum = tmp;
        }

        // to the right from the middle!!!
        tmp = 0;
        int rsum = INT_MIN;
        for (auto it = middle + 1; it <= last; ++it) {
            tmp += *it;
            if (tmp > rsum) rsum = tmp;
        }

        return max({lsum + rsum, lsum, rsum});
    }

public:
    int maximumCostSubstring(string& s, string chars, vector<int>& vals) {
        // problem is the same as maximum sum subarray

        int value[26];
        for(int i = 0; i < 26; ++i)
            value[i] = i+1;
        for(int i = 0; i < chars.size(); ++i)
            value[chars[i]-'a'] = vals[i];

        int n = s.size();
        vector<int> nums(n);
        for(int i = 0; i < n; ++i)
            nums[i] = value[s[i]-'a'];

        if( nums.size() == 1 )
            return nums[0] > 0 ? nums[0] : 0;

        int ans = maxSubArray(nums.begin(), nums.end() - 1);
        return ans > 0 ? ans : 0;
    }
};
