
// 1394. Find Lucky Integer in an Array
// https://leetcode.com/problems/find-lucky-integer-in-an-array/

class Solution {
public:
    int findLucky(vector<int>& arr) {
        int a[501];
        int i = 0;
        for(; i < 501; ++i)
            a[i] = 0;

        auto n = arr.size();
        i = 0;
        for(; i < n; ++i)
            ++a[arr[i]];

        int r = -1;
        i = 500;
        for(; i >=1; --i)
            if( i == a[i] ) {
                r = i;
                break;
            }

        return r;
    }
};
