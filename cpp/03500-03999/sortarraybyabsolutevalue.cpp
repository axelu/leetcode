
// 3667. Sort array by Absooute Value
// https://leetcode.com/problems/sort-array-by-absolute-value/



class Solution {
public:
    vector<int> sortByAbsoluteValue(vector<int>& nums) {
        sort(begin(nums), end(nums), [](int a, int b){
            if( abs(a) < abs(b) ) {
                return true;
            } else if( abs(a) == abs(b) ) {
                if( a < b ) {
                    return true;
                }
            }
            return false;
        });
        return nums;
    }
};
