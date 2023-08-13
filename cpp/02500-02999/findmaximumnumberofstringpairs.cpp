
// 2744. Find Maximum Number of String Pairs
// https://leetcode.com/problems/find-maximum-number-of-string-pairs/



class Solution {
public:
    int maximumNumberOfStringPairs(vector<string>& words) {
        int n = words.size();
        if( n == 1 )
            return 0;

        vector<string> rev(n);
        for(int i = 0; i < n; ++i) {
            string t = words[i];
            reverse(t.begin(),t.end());
            rev[i] = t;
        }

        int ans = 0;

        // brute force
        vector<bool> seen(n,false);
        for(int i = 0; i < n-1; ++i) {
            if( seen[i] )
                continue;
            for(int j = i+1; j < n; ++j) {
                if( seen[j] )
                    continue;
                if( words[i] == rev[j] ) {
                    seen[i] = true;
                    seen[j] = true;
                    ++ans;
                    break;
                }
            }
        }

        return ans;
    }
};
