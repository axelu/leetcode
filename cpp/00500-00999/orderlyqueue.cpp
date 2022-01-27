
// 899. Orderly Queue
// https://leetcode.com/problems/orderly-queue/





class Solution {
public:
    string orderlyQueue(string s, int k) {
        if( k == 1 ) {
            // brute force
            string mn = s;
            for(int i = 0; i < s.size(); ++i) {
                s += s[0];s.erase(0,1);
                if( s < mn )
                    mn = s;
            }
            return mn;
        }

        sort(begin(s),end(s));
        return s;
    }
};
