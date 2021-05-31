
// 1209. Remove All Adjacent Duplicates in String II
// https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/
// day 16 April 2021 challenge
// https://leetcode.com/explore/featured/card/april-leetcoding-challenge-2021/595/week-3-april-15th-april-21st/3710/



class Solution {
public:
    string removeDuplicates(string s, int k) {
        stack<pair<char,int>> stck;

        int i;
        for(i = 0; i < s.size(); ++i) {
            if( stck.empty() ) {
                stck.push({s[i],1});
            } else {
                if( stck.top().first == s[i] ) {
                    ++stck.top().second;
                    if( stck.top().second == k ) {
                        stck.pop();
                    }
                } else {
                    stck.push({s[i],1});
                }
            }
        }

        string t,ans = "";
        while( !stck.empty() ) {
            t = "";
            for(i = 0; i < stck.top().second; ++i) t += stck.top().first;
            ans = t + ans;
            stck.pop();
        }
        return ans;
    }
};
