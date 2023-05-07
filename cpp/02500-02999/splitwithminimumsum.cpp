
// 2578. Split With Minimum Sum
// https://leetcode.com/problems/split-with-minimum-sum/



class Solution {
public:
    int splitNum(int num) {
        vector<int> v;

        while( num > 0 ) {
            v.push_back(num % 10);
            num /= 10;
        }
        sort(v.begin(),v.end());

        int num1 = 0;
        int num2 = 0;
        int t = 0;
        for(int x: v) {
            if( x > 0 ) {
               if( t == 0 ) {
                   num1 = num1 * 10 + x;
                   t = 1;
               } else {
                   num2 = num2 * 10 + x;
                   t = 0;
               }
            }
        }

        return num1 + num2;
    }
};
