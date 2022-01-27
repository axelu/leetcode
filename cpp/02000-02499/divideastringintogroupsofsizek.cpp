
// 2138. Divide a String Into Groups of Size k
// https://leetcode.com/problems/divide-a-string-into-groups-of-size-k/


class Solution {
public:
    vector<string> divideString(string s, int k, char fill) {
        vector<string> ans;

        int j = 0;
        string t = "";
        for(int i = 0; i < s.size(); ++i) {
            t += s[i];
            ++j;
            if( j == k ) {
                ans.push_back(t);
                j = 0;
                t = "";
            }
        }
        if( !t.empty() && t.size() < k ) {
            while( t.size() < k )
                t += fill;
            ans.push_back(t);
        }

        return ans;
    }
};
