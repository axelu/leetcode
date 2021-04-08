
// 1013. Partition Array Into Three Parts With Equal Sum
// https://leetcode.com/problems/partition-array-into-three-parts-with-equal-sum/

class Solution {
public:
    bool canThreePartsEqualSum(vector<int>& arr) {
        size_t n = arr.size();
        int sum = 0;
        int i = 0;
        for(; i < n; ++i)
            sum += arr[i];

        if( sum % 3 != 0 ) return false;
        sum /= 3;

        i = 0;

        // part 1
        int a = 0;
        for(; i < n; ++i) {
            a += arr[i];
            if( a == sum ) break;
        }
        ++i;
        if( i >= n ) return false;

        // part 2
        a = 0;
        for(; i < n; ++i) {
            a += arr[i];
            if( a == sum ) break;
        }
        ++i;
        if( i >= n ) return false;

        // part 3
        a = 0;
        for(; i < n; ++i)
            a += arr[i];
        if( a == sum && i == n ) return true;

        return false;
    }
};
