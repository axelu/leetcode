
// 2085. Count Common Words With One Occurence
// https://leetcode.com/problems/count-common-words-with-one-occurrence/



class Solution {
public:
    int countWords(vector<string>& words1, vector<string>& words2) {
        unordered_map<string,int> cnt1,cnt2;
        for(string s : words1)
            ++cnt1[s];
        for(string s : words2)
            ++cnt2[s];

        int ans = 0;
        for(auto p : cnt1) {
            if( p.second == 1 ) {
                auto f = cnt2.find(p.first);
                if( f != cnt2.end() && f->second == 1 )
                    ++ans;
            }
        }

        return ans;
    }
};
