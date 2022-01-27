
// 922. Sort Array By Parity II
// https://leetcode.com/problems/sort-array-by-parity-ii/



class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& nums) {
        stack<int> e; // even
        stack<int> o; // odd
        // pass1
        for(int i : nums) {
            if( i % 2 == 0 ) e.push(i);
            else o.push(i);
        }
        // pass2
        for(int i = 0; i < nums.size(); ++i) {
            nums[i] = e.top(); e.pop();
            ++i;
            nums[i] = o.top(); o.pop();
        }

        return nums;
    }
};
