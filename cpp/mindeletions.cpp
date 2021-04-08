
// 1647. Minimum Deletions to Make Character Frequencies Unique
// https://leetcode.com/problems/minimum-deletions-to-make-character-frequencies-unique/


class Solution {
public:
    int minDeletions(string s) {
        auto n = s.size();
        if( n == 1 ) return 0;

        int chs[26]; memset(chs,0,sizeof chs);
        for(char c : s) ++chs[c - 'a'];

        multiset<int> ms;
        set<int> ss;
        for(int i = 0; i < 26; ++i)
            if( chs[i] != 0 ) {
                ms.insert(chs[i]);
                ss.insert(chs[i]);
            }

        int r = 0;
        for(auto it = ms.rbegin(); it != ms.rend(); ++it) {
            if( it == ms.rbegin() ) continue;
            if( *it == *it.base() )
                // 'fix' it-1 aka it.base()
                // find freqency value to reduce to
                for(int i = *it.base() - 1; i >= 0; --i)
                    if( ss.count(i) == 0 ) {
                        r += *it.base() - i;
                        if( i != 0 ) ss.insert(i);
                        break;
                    }
        }

        return r;
    }
};
