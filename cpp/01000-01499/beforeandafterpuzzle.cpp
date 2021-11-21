
// 1181. Before and After Puzzle
// https://leetcode.com/problems/before-and-after-puzzle/




class Solution {
private:
    void getFirstAndLast(string& str, string* fst, string* sfx, string* lst) {
        auto n = str.find(' ');
        if( n == string::npos ) {
            *fst = str;
            *sfx = "";
        } else {
            *fst = str.substr(0,(int)n);
            *sfx = str.substr((int)n);
        }

        n = str.rfind(' ');
        if( n == string::npos ) {
            *lst = str;
        } else {
            *lst = str.substr((int)n+1);
        }
    }
public:
    vector<string> beforeAndAfterPuzzles(vector<string>& phrases) {
        int n = phrases.size();

        string fst[n];string sfx[n];
        string lst[n];

        set<string> ansSet;
        for(int i = 0; i < n-1; ++i) {
            if( fst[i].empty() ) getFirstAndLast(phrases[i],fst+i,sfx+i,lst+i);

            for(int j = i+1; j < n; ++j) {
                if( fst[j].empty() ) getFirstAndLast(phrases[j],fst+j,sfx+j,lst+j);
                if( lst[i] == fst[j] )
                    ansSet.insert(phrases[i]+sfx[j]);
                if( lst[j] == fst[i] )
                    ansSet.insert(phrases[j]+sfx[i]);
            }
        }

        vector<string> ans;
        for(string s : ansSet)
            ans.push_back(s);
        return ans;
    }
};
