
// 1295. Find Numbers with Even Number of Digits
// https://leetcode.com/problems/find-numbers-with-even-number-of-digits/



class Solution {
public:
    int findNumbers(vector<int>& nums) {
        int r = 0;

        int k,d;
        for(auto it = begin(nums); it != end(nums); ++it) {
            k = *it;
            d = 0;
            while( k > 0 ) {
                ++d;
                k /= 10;
            }
            if( d % 2 == 0 ) ++r;
        }

        return r;
    }
};
