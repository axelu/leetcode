
// 1664. Ways to Make a Fair Array
// https://leetcode.com/problems/ways-to-make-a-fair-array/

class Solution {
public:
    int waysToMakeFair(vector<int>& nums) {
        size_t n = nums.size();
        if( n == 1 ) return 1;
        if( n == 2 ) return 0;

        int even[n];memset(even,0,sizeof even);
        int odd[n];memset(odd,0,sizeof odd);
        int e = 0, o = 0;
        for(int i = 0; i < n; ++i) {
            if( i % 2 == 0 )
                e += nums[i];
            else
                o += nums[i];
            even[i] = e;
            odd[i] = o;
        }

        int r = 0;

        // removing idx 0
        if( o == e - nums[0] ) ++r;
        // removing idx n-1
        if( even[n-2] == odd[n-2] ) ++r;

        int s1, s2;
        for(int i = 1; i < n-1; ++i) {
            if( i % 2 == 0 ) {
                s1 = even[i-1] + o - odd[i-1];
                s2 = odd[i-1] + e - even[i];
            } else {
                s1 = even[i-1] + o - odd[i];
                s2 = odd[i-1] + e - even[i];
            }
            if( s1 == s2 ) ++r;
        }
        return r;
    }
};
