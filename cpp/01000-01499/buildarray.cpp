
// 1441. Build an Array With Stack Operations
// https://leetcode.com/problems/build-an-array-with-stack-operations/

class Solution {
public:
    vector<string> buildArray(vector<int>& target, int n) {
        vector<string> r;
        int j = 0; // idx in target
        int m = target.size();
        int i = 1; // list
        while(true) {
            r.push_back("Push");
            if( target[j] != i ) {
                r.push_back("Pop");
            } else {
                ++j;
            }
            if( j == m ) break;
            ++i;
        }
        return r;
    }
};
