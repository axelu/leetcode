
// 1089. Duplicate Zeros
// https://leetcode.com/problems/duplicate-zeros/


class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        size_t n = arr.size();
        for(int i = 0; i < n-1; ++i) {
            if( arr[i] == 0 ) {
                arr.pop_back();
                arr.insert(begin(arr)+i,0);
                ++i;
            }
        }
    }
};
