
// 1324. Print Words Vertically
// https://leetcode.com/problems/print-words-vertically/



class Solution {
private:

    pair<int,vector<string>> string2words(string& s) {
        int n = 0;
        vector<string> v;
        stringstream ss(s);
        string t;
        while( getline(ss,t,' ') ) {
            v.push_back(t);
            n = max(n,(int)t.size());
        }
        return {n,v};
    }




public:
    vector<string> printVertically(string& s) {
        // longest word in s determines the number of 'cols' in answer
        // the number of words in s determines the number of 'rows' in answer

        pair<int,vector<string>> p = string2words(s);
        vector<string> words = p.second;
        int m = words.size();   // rows
        int n = p.first;        // cols

        vector<string> ans(n);
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {

                if( words[i].size() > j )
                    ans[j] += words[i][j];
                else
                    ans[j] += ' ';

            }
        }

        // remove trailing spaces
        for(int j = 0; j < n; ++j)
            while( ans[j].back() == ' ' )
                ans[j].pop_back();

        return ans;
    }
};
