
// 2169. Count Operations to Obtain Zero
// https://leetcode.com/problems/count-operations-to-obtain-zero/



class Solution {
public:
    int countOperations(int num1, int num2) {
        int ans = 0;

        while(true) {
            if( num1 == 0 || num2 == 0 )
                break;

            if( num1 >= num2 ) {
                num1 -= num2;
            } else {
                num2 -= num1;
            }
            ++ans;
        }

        return ans;
    }
};
