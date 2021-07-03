
// 89. Gray Code
// https://leetcode.com/problems/gray-code/submissions/
// day 1 July 2021 challenge
// https://leetcode.com/explore/featured/card/july-leetcoding-challenge-2021/608/week-1-july-1st-july-7th/3799/






class Solution {
private:
    // https://en.wikipedia.org/wiki/Gray_code#Converting_to_and_from_Gray_code
    uint BinaryToGray(uint num) {
        return num ^ (num >> 1);
    }

public:
    vector<int> grayCode(int n) {
        int l = pow(2,n);

        int val;
        vector<int> ans(l);

        // gray code to generate a n-bit sequence.
        for(int i = 0; i < l; ++i) {
            val = BinaryToGray(i);
            ans[i] = val;
        }


        return ans;
    }
};
