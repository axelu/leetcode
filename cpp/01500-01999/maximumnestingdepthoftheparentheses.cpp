
// 1614. Maximum Nesting Depth of the Parentheses
// https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/

class Solution {
public:
    int maxDepth(string s) {
        int r = 0;
        int d = 0;
        for(char c : s) {
            if( c == '(' ) ++d;
            if( c == ')' ) --d;
            r = max(r,d);
        }
        return r;
    }
};

int main() {

    Solution s;
    string s;

    s = "(1+(2*3)+((8)/4))+1";
    int r = s.maxDepth(s);

    return 0;
}
