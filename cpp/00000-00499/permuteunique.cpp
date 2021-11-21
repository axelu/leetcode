
// 47. Permutations II
// day 12 November 2020 challenge
// https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/565/week-2-november-8th-november-14th/3528/
// https://leetcode.com/problems/permutations-ii/



// inspired by
// https://www.geeksforgeeks.org/print-all-permutations-of-a-string-with-duplicates-allowed-in-input-string
class Solution {
private:
    vector<int> * pNums;
    size_t n;

    int rfindCeil(int cur, int l) {
        int ceilIdx = l; // idx to the right of cur

        // iterate starting at l+1 and find smallest element greater than cur
        for(int i = l + 1; i < n; ++i)
            if ((*pNums)[i] > cur && (*pNums)[i] < (*pNums)[ceilIdx])
                ceilIdx = i;
        return ceilIdx;
    }

public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        pNums = &nums;
        n = nums.size();
        sort(begin(nums),end(nums));

        vector<vector<int>> r;
        bool done = false;
        int i,ceilIdx,t;
        while(!done) {
            r.push_back(nums);

            // rightmost idx of an element smaller than element at idx+1
            for(i = n-2; i >= 0; --i)
                if( nums[i] < nums[i+1])
                    break;

            if( i == -1 ) {
                // elements are in decreasing order = we are done
                done = true;
            } else {

                // find smallest element greater than nums[i] to the right of i
                ceilIdx = rfindCeil(nums[i],i+1);

                // swap
                t = nums[i];
                nums[i] = nums[ceilIdx];
                nums[ceilIdx] = t;

                // sort the remainder
                sort(begin(nums)+i+1,end(nums));
            }
        }

        return r;
    }
};
