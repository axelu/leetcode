
// 3498. Reverse Degree of a String
// https://leetcode.com/problems/reverse-degree-of-a-string/



/* 12345678901234567890123456
   zyxwvutsrqponmlkjihgfedcba
 */
class Solution {
public:
    int reverseDegree(string s) {
        int sum = 0;
        for(int i = 0; i < s.size(); ++i) {
            int c = s[i] - 'a';
            sum += ( (i+1) * (26 - c));
        }

        return sum;
    }
};
