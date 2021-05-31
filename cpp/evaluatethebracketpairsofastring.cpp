
// 1807. Evaluate the Bracket Pairs of a String
// https://leetcode.com/problems/evaluate-the-bracket-pairs-of-a-string/




class Solution {
public:
    string evaluate(string& s, vector<vector<string>>& knowledge) {
        int i,l,r = 0;

        unordered_map<string,string> kmap;
        for(i = 0; i < knowledge.size(); ++i)
            kmap.insert({knowledge[i][0],knowledge[i][1]});

        string ans = "";
        unordered_map<string,string>::iterator f;
        for(i = 0; i < s.size(); ++i) {
            if( s[i] == '(' ) {
                l = i+1;
                if( r != i ) {
                    ans += s.substr(r,i-r);
                }
            }
            else if( s[i] == ')' ) {
                f = kmap.find(s.substr(l,i-l));
                ans += f != kmap.end() ? f->second : "?";
                r = i+1;
            }
        }
        // finish up
        if( r != i ) ans += s.substr(r,i-r);

        return ans;
    }
};
