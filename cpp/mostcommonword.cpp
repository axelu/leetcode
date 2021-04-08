
// 819. Most Common Word
// https://leetcode.com/problems/most-common-word/


class Solution {
public:
    string mostCommonWord(string paragraph, vector<string>& banned) {

        unordered_set<string> bannedDic;
        for(int i = 0; i < banned.size(); ++i)
            bannedDic.insert(banned[i]);

        int mxCnt = 0;
        string ans;
        unordered_map<string,int> um;
        pair<unordered_map<string,int>::iterator,bool> p;
        string word = "";
        int n = paragraph.size();
        for(int i = 0; i < n; ++i) {
            if( isalpha(paragraph[i]) ) {
                word += tolower(paragraph[i]);
                if( i < n-1 ) continue;
            }
            if( !word.empty() ) {
                if( bannedDic.find(word) == bannedDic.end() ) {
                    p = um.insert({word,1});
                    if( !p.second )
                        ++p.first->second;
                    if( p.first->second > mxCnt ) {
                        mxCnt = p.first->second;
                        ans = word;
                    }

                }
                word = "";
            }
        }

        return ans;
    }
};
