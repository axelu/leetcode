
// 1415. The k-th Lexicographical String of All Happy Strings of Length n
// https://leetcode.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/


class Solution {
private:
    int cnt;
    string ans;

    void dfs(string& s, char p, int n, int k) {
        if( !ans.empty() ) return;
        if( s.size() == n ) {
            ++cnt;
            if( cnt == k ) ans = s;
            return;
        }

        char c[] = {'a','b','c'};
        for(int i = 0; i < 3; ++i) {
            if( p != c[i] ) {
                s += c[i];
                dfs(s,c[i],n,k);
                s.pop_back(); // back tracking
            }
        }

    }

public:
    string getHappyString(int n, int k) {
        cnt = 0;
        ans = "";
        string s = "";
        dfs(s,'z',n,k);

        return ans;
    }
};
