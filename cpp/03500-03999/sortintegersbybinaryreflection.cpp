
// 3769. Sort Integers by Binary Reflection
// https://leetcode.com/problems/sort-integers-by-binary-reflection/



class Solution {
public:
    vector<int> sortByReflection(vector<int>& nums) {
        sort(begin(nums), end(nums), [](int lhs, int rhs){
            int a = 0;
            int x = lhs;
            while(x) {
                a = a * 2;
                if( x & 1 )
                    a = a + 1;
                x >>= 1;
            }
            int b = 0;
            x = rhs;
            while(x) {
                b = b * 2;
                if( x & 1 )
                    b = b + 1;
                x >>= 1;
            }
            // cout << "lhs " << lhs << " binary reflection " << a << endl;
            // cout << "rhs " << rhs << " binary reflection " << b << endl;
            if( a < b ) {
                return true;
            } else if( a == b ) {
                if( lhs < rhs ) {
                    return true;
                }
            }
            return false;
        });
        return nums;
    }
};
