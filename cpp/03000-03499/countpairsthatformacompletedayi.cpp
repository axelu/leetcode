
// 3184. Count Pairs That Form a Complete Day I
// https://leetcode.com/problems/count-pairs-that-form-a-complete-day-i/



class Solution {
public:
    int countCompleteDayPairs(vector<int>& hours) {
        int n = hours.size(); // 1 <= hours.length <= 100

        int ans = 0;

        // brute force since small constraint
        for(int i = 0; i < n-1; ++i)
            for(int j = i+1; j < n; ++j)
                if( (hours[i] + hours[j]) % 24 == 0 )
                    ++ans;

        return ans;
    }
};
