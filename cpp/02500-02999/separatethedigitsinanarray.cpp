
// 2553. Separate the Digits in an Array
// https://leetcode.com/problems/separate-the-digits-in-an-array/



class Solution {
public:
    vector<int> separateDigits(vector<int>& nums) {

        vector<int> ans;
        stack<int> stck;

        for(int x: nums) {

            while( x > 0 ) {
                stck.push(x % 10);
                x /= 10;
            }

            while( !stck.empty() ) {
                ans.push_back(stck.top());
                stck.pop();
            }

        }

        return ans;
    }
};
