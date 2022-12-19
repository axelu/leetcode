
// 2455. Average Value of Even Numbers That Are Divisible by Three
// https://leetcode.com/problems/average-value-of-even-numbers-that-are-divisible-by-three/




class Solution {
public:
    int averageValue(vector<int>& nums) {
        int cnt = 0;
        int sum = 0;
        for(int x: nums)
            if( x % 3 == 0 && x % 2 == 0 ) {
                ++cnt;
                sum += x;
            }

        return cnt > 0 ? sum/cnt : 0;
    }
};
