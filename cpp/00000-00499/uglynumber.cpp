
// 263. Ugly Number
// https://leetcode.com/problems/ugly-number/



class Solution {
public:
    bool isUgly(int num) {
        // base case
        if( 0 >= num ) return false;

        while(num%2==0) num/=2;
        while(num%3==0) num/=3;
        while(num%5==0) num/=5;
        return num == 1;
    }
};
