
// 784. Letter Case Permutation
// https://leetcode.com/problems/letter-case-permutation/
// day 16 February 2021 challenge
// https://leetcode.com/explore/challenge/card/february-leetcoding-challenge-2021/586/week-3-february-15th-february-21st/3642/




// https://en.cppreference.com/w/cpp/string/basic_string/find_first_of
// https://en.cppreference.com/w/cpp/string/byte/tolower
class Solution {
    int N;
    vector<string> ans;
    const char* search_cstr = "abcdefghijklmnopqrstuvwxyz";

    string str_tolower(string s) {
        transform(s.begin(), s.end(), s.begin(),[](unsigned char c){
            return std::tolower(c);
        });
        return s;
    }

    void dfs(string& S, int idx) {
        if( idx >= N ) {
            ans.push_back(S);
            return;
        }
        int f = S.find_first_of(search_cstr,idx);
        if( f == string::npos ) {
            ans.push_back(S);
            return;
        }
        dfs(S,f+1);
        char t = S[f];
        S[f] = (int)t < 97 ? (int)t + 32 : (int)t - 32;
        dfs(S,f+1);
        // back track
        S[f] = t;
    }
public:
    vector<string> letterCasePermutation(string S) {
        N = S.size();
        S = str_tolower(S);
        dfs(S,0);
        return ans;
    }
};
