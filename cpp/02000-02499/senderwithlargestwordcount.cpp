
// 2284. Sender With Largest Word Count
// https://leetcode.com/problems/sender-with-largest-word-count/



class Solution {
public:
    string largestWordCount(vector<string>& messages, vector<string>& senders) {
        int n = messages.size(); // messages.size() == senders.size()

        // map will sort senders lexicographically
        map<string,int> mp; // sender,spaces
        for(int i = 0; i < n; ++i) {
            int t = 1;
            for(char c: messages[i])
                if( c == ' ' )
                    ++t;
            mp[senders[i]] += t;
        }

        string ans;
        int mx = 0;
        for(auto p: mp)
            if( p.second >= mx ) {
                mx = p.second;
                ans = p.first;
            }

        return ans;
    }
};
