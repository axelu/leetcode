
// 3455. Shortest Matching Substring
// https://leetcode.com/problems/shortest-matching-substring/






class Solution {
private:
    void kmp_table(string& W, vector<int>& T) {
        // https://en.wikipedia.org/wiki/Knuth–Morris–Pratt_algorithm

        // input:  an array of characters, W (the word to be analyzed)
        // output: an array of integers, T (the table to be filled)

        int pos = 1; // current position we are computing in t
        int cnd = 0; // zero-based index in w of the next character of the current candidate substring

        T[0] = -1;

        while(pos < W.size()) {
            if( W[pos] == W[cnd] ) {
                T[pos] = T[cnd];
            } else {
                T[pos] = cnd;
                while(cnd >= 0 && W[pos] != W[cnd]) {
                    cnd = T[cnd];
                }
            }
            ++pos;
            ++cnd;
        }

        T[pos] = cnd; // only needed when all word occurrences are searched
    }

    int kmp_search(string& S, string& W, vector<int>& P) {
        // https://en.wikipedia.org/wiki/Knuth–Morris–Pratt_algorithm

        // input:   an array of characters, S (the text to be searched)
        //          an array of characters, W (the word sought)
        // output:  an array of integers, P (positions in S at which W is found)
        //          an integer, nP (number of positions)

        int j = 0; // the position of the current character in S
        int k = 0; // the position of the current character in W
        vector<int> T(W.size()+1); kmp_table(W,T); // Partial Match

        int nP = 0;

        while(j < S.size()) {
            if( W[k] == S[j] ) {
                ++j;
                ++k;
                if( k == W.size() ) {
                    // occurrence found, if only first occurrence is needed, m ← j - k  may be returned here
                    P[nP] = j - k; nP = nP + 1;
                    k = T[k]; // T[length(W)] can't be -1
                }
            } else {
                k = T[k];
                if( k < 0 ) {
                    ++j;
                    ++k;
                }
            }
        }
        return nP;
    }

    int solve1(string& S, string& W) {
        vector<int> P(S.size(),0);
        int nP = kmp_search(S,W,P);

        return nP > 0 ? W.size() : -1;
    }

    // binary search lower bound
    int search(vector<int>& nums, int n, int target) {
        // returns 'n' if target greater than greatest element
        // returns  0  if target less or equal than smallest element
        // binary search lower bound while loop
        // lower bound -> equal or greater than target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target <= nums[mid] )
                e = mid;
            else
                s = mid+1;
        }
        if( s < n && nums[s] < target )
            ++s;

        return s;
    }

    int solve2(string& S, vector<string>& patterns) {
        int s_sz = S.size();

        // lets find the 1st pattern (pattern 0) in S
        vector<int> P0(s_sz,0); // positions of pattern 0 in S
        int nP0 = kmp_search(S,patterns[0],P0);
        if( nP0 == 0 )
            return -1;

        // lets find the 2nd pattern (pattern 1) in S
        vector<int> P1(s_sz,0); // positions of pattern 1 in S
        int nP1 = kmp_search(S,patterns[1],P1);
        if( nP1 == 0 )
            return -1;

        int p0_sz = patterns[0].size();
        int p1_sz = patterns[1].size();

        int ret = INT_MAX;

        for(int i = 0; i < nP0; ++i) {
            // pattern 0 was found at pos P0[i] in S
            // pattern 0 ends at index (P0[i] + p0_sz - 1) in S
            // smallest index pattern 1 can start in S is P0[i] + p0_sz
            // we know we tried already w/o a wildcard,
            // so technically we know that there will be at least
            // 1 char between  pattern 0 end and pattern 1 start
            // we will ignore that here for simplicity

            int p1_start_min = P0[i] + p0_sz;

            // does pattern 1 still fit into S?
            if( p1_start_min == s_sz || s_sz - p1_start_min < p1_sz )
                break;

            // find the smallest index >= p1_start_min in P1
            // lower_bound
            int p1_start = search(P1, nP1, p1_start_min);
            if( p1_start == nP1 )
                break;

            int p1_start_idx = P1[p1_start];
            int p1_end_idx = p1_start_idx + p1_sz - 1;

            ret = min(ret, p1_end_idx - P0[i] + 1);
        }

        return ret != INT_MAX ? ret : -1;
    }

    int solve3(string& S, vector<string>& patterns) {
        int s_sz = S.size();

        // lets find the 1st pattern (pattern 0) in S
        vector<int> P0(s_sz,0); // positions of pattern 0 in S
        int nP0 = kmp_search(S,patterns[0],P0);
        if( nP0 == 0 )
            return -1;

        // lets find the 2nd pattern (pattern 1) in S
        vector<int> P1(s_sz,0); // positions of pattern 1 in S
        int nP1 = kmp_search(S,patterns[1],P1);
        if( nP1 == 0 )
            return -1;

        // lets find the 3rd pattern (pattern 2) in S
        vector<int> P2(s_sz,0); // positions of pattern 2 in S
        int nP2 = kmp_search(S,patterns[2],P2);
        if( nP2 == 0 )
            return -1;

        int p0_sz = patterns[0].size();
        int p1_sz = patterns[1].size();
        int p2_sz = patterns[2].size();

        int ret = INT_MAX;

        for(int i = 0; i < nP0; ++i) {
            // pattern 0 was found at pos P0[i] in S
            // pattern 0 ends at index (P0[i] + p0_sz - 1) in S
            // smallest index pattern 1 can start in S is P0[i] + p0_sz

            int p1_start_min = P0[i] + p0_sz;
            // does pattern 1 + pattern 2 still fit into S?
            if( p1_start_min == s_sz || p1_start_min + p1_sz + p2_sz > s_sz )
                break;

            // find the smallest index >= p1_start_min in P1
            // lower_bound
            int p1_start = search(P1, nP1, p1_start_min);
            if( p1_start == nP1 )
                break;

            int p1_start_idx = P1[p1_start];
            int p1_end_idx = p1_start_idx + p1_sz - 1;

            int p2_start_min = p1_end_idx + 1;
            // does pattern 2 still fit into S?
            if( p2_start_min == s_sz || p2_start_min + p2_sz > s_sz )
                break;

            // find the smallest index >= p2_start_min in P2
            // lower bound
            int p2_start = search(P2, nP2, p2_start_min);
            if( p2_start == nP2 )
                break;

            int p2_start_idx = P2[p2_start];
            int p2_end_idx = p2_start_idx + p2_sz - 1;

            ret = min(ret, p2_end_idx - P0[i] + 1);
        }

        return ret != INT_MAX ? ret : -1;
    }

public:
    int shortestMatchingSubstring(string s, string p) {
        int s_sz = s.size();
        int p_sz = p.size(); // 2 <= p_sz <= 1e5, p contains exactly two '*'
        // p_sz == 2 => p = "**"
        if( p_sz == 2 )
            return 0;

        // p options other than "**"
        // let a, b and c be one of more chars
        // a** or *a* or **a    => basically one sequence of chars to match
        // a*b* or a**b or *a*b => basically two sequences of chars to match
        // a*b*c                => basically three sequences of chars to match

        vector<string> patterns;
        stringstream ss(p);
        string t;
        string pattern = "";
        int patterns_total_len = 0; // our best answer
        while( getline(ss,t,'*') ) {
            if( !t.empty() ) {
                patterns.push_back(t);
                patterns_total_len += t.size();
                pattern.append(t);
            }
        }
        /*
        cout << patterns.size() << endl;
        for(string str: patterns)
            cout << str << " ";
        cout << endl;
        */

        if( patterns_total_len > s_sz )
            return -1;
        if( patterns_total_len == s_sz ) {
            return s == pattern ? patterns_total_len : -1;
        }

        // lets try to find the whole pattern
        // if found, that is our best solution
        int res = solve1(s, pattern);
        if( patterns.size() == 1 || res != -1 )
            return res;

        // if we are here, pattern.size() either 2 or 3 and we know
        // the pattern does not exist w/o using the wild cards

        if( patterns.size() == 2 )
            return solve2(s, patterns);

        return solve3(s, patterns);
    }
};
