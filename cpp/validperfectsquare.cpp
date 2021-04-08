
// 367. Valid Perfect Square
// https://leetcode.com/problems/valid-perfect-square/



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
    bool isPerfectSquare(int num) {
        // 1 <= num <= 2147483647
        //   46341^2 = 2147488281 > INT_MAX
        //   46340^2 = 2147395600
        // solution is between 1 and 46340
        if( num > 2147395600 ) return false;
        return search(1,46340,num);
    }
};
