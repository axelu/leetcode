
// 2564. Substring XOR Queries
// https://leetcode.com/problems/substring-xor-queries/



/*  a  ^   b   = c
 * val ^ first = second
 *
 * example
 * val           11
 * first    1  0001
 * second   2  0010
 *
 * generally, if we do first ^ second, we know what we are looking for
 *
 * 1e9 30 digits in binary
 */
class Solution {
private:
    string int2binarystring(int x) {
        string ret(30,'0');
        for(int i = 0; i < 30; ++i)
            if( (x>>i) & 1 )
                ret[30-1-i] = '1';
        // trim leading 0s, if any
        while(ret.size() > 1 && ret.front() == '0' )
            ret.erase(0,1);
        return ret;
    }

    int binarystring2int(string s, int n) {
        int ret = 0;
        for(int i = n-1; i >= 0; --i)
            if( s[i] == '1' )
                ret |= 1 << (n-1-i);
        return ret;
    }

vector<int> lps_table(string& pattern) {
    // LPS (longest proper prefix that is also a suffix)
    int m = pattern.size();
    vector<int> LPS(m);
    LPS[0] = 0;  // LPS value of the first element is always 0
    int k = 0; // length of previous longest proper prefix that is also a suffix
    for(int i = 1; i < m; ++i) {
        while( pattern[i] != pattern[k] && k > 0 )
            k = LPS[k-1];
        if( pattern[i] == pattern[k] )
            LPS[i]=++k;
    }
    return LPS;
}

int kmp_search(string& pattern, string& s) {
    // returns index of the 1st match of pattern in s or -1 if not found
    int n = s.size();
    int m = pattern.size();

    vector<int> LPS = lps_table(pattern);
    int j = 0; // index into pattern
    for(int i = 0; i < n; ++i) {
        while( pattern[j] != s[i] && j > 0)
            j = LPS[j-1];
        if( pattern[j] == s[i] ) {
            ++j;
            if( j == m )            // j pointer has reached end of pattern
               return (i+1) - j;    // index of the match
        }
    }
    return -1;  // no match
}


public:
    vector<vector<int>> substringXorQueries(string s, vector<vector<int>>& queries) {
        int s_sz = s.size();
        int q_sz = queries.size();

        vector<vector<int>> ans(q_sz,vector<int>(2,-1));

        unordered_map<int,int> um;
        // we also need to catch the 1st 0 if any
        um[0] = -1;
        for(int j = 0; j < s_sz; ++j) {
            if( s[j] == '0' ) {
                if( um[0] == -1 )
                    um[0] = j;
                continue;
            }
            for(int i = 0; i < 30 && j + i < s_sz; ++i) {
                int t = binarystring2int(s.substr(j,i+1),i+1);
                um.insert({t,j});
            }
        }

        for(int i = 0; i < q_sz; ++i) {
            int t = queries[i][0] ^ queries[i][1];
            string t_str = int2binarystring(t);

            auto f = um.find(t);
            if( f != um.end() ) {
                ans[i][0] = f->second;
                ans[i][1] = f->second + t_str.size() - 1;
            }


            /*
            int idx = kmp_search(t_str,s);
            if( idx != -1 ) {
                ans[i][0] = idx;
                ans[i][1] = idx + t_str.size() - 1;
            }
            */
        }

        return ans;
    }
};
