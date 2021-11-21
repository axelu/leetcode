
// 46. Permutations
// https://leetcode.com/problems/permutations/
// solution inspired by 
// https://www.geeksforgeeks.org/heaps-algorithm-for-generating-permutations/


class Solution {
private:
    vector<int> * pNums;
    vector<vector<int>> * pR;

    void permute(int n) {
        if( n == 1 ) {
            pR->push_back(*pNums);
            return;
        }

        int t;
        for(int i = 0; i < n; ++i) {
            permute(n-1);

            if( n % 2 == 1 ) {
                // size is odd,: swap first and size-1 element
                t = (*pNums)[0];
                (*pNums)[0] = (*pNums)[n-1];
                (*pNums)[n-1] = t;
            } else {
                // size is even: swap ith and size-1 element
                t = (*pNums)[i];
                (*pNums)[i] = (*pNums)[n-1];
                (*pNums)[n-1] = t;
            }
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        auto n = nums.size();
        pNums = &nums;

        vector<vector<int>> r;
        pR = &r;
        permute(n);
        return r;
    }
};
