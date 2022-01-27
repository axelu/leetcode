
// 633. Sum of Square Numbers
// https://leetcode.com/problems/sum-of-square-numbers/



class Solution {
private:
    // binary search
    bool search(int s, int e, int target) {
        if( s > e ) return false;

        int mid = s + ((e - s)/2);
        int t = mid * mid;
        if( t == target ) {
            return true;
        } else if( t < target ) {
            return search(mid+1,e,target);
        } else {
            return search(s,mid-1,target);
        }
    }

public:
    bool judgeSquareSum(int c) {
        // constraint: 0 <= c <= 2^31 - 1 (= INT_MAX = 2147483647)
        //   46341^2 = 2147488281 > INT_MAX
        //   46340^2 = 2147395600
        // base case
        if( c <= 1 ) return true;

        int a,b,target;
        for(int i = 0; i < 46341; ++i) {
            a = i*i;
            if( a == c ) return true;
            if( a > c  ) break;
            target = c - a;
            if( target > 2147395600 ) continue;
            if( search(1,46340,target) ) return true;
        }
        return false;
    }
};
