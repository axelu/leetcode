
// 796. Rotate String
// https://leetcode.com/problems/rotate-string/


class Solution {
public:
    bool rotateString(string A, string B) {
        int n = A.size();
        if( n != B.size() ) return false;
        if( A == B ) return true;
        if( n == 1 ) return false;

        // simulate
        char c;
        for(int i = 0; i < n-1; ++i) {
            c = A[0];
            A.erase(0,1);
            A += c;
            if( A == B ) return true;
        }
        return false;
    }
};
