

// 115. Distinct Subsequences
// https://leetcode.com/problems/distinct-subsequences/
// day 19 September 2021 challenge
// https://leetcode.com/explore/challenge/card/september-leetcoding-challenge-2021/638/week-3-september-15th-september-21st/3980/



// n = 7    n = 6
// 0123456  012345
// rabbbit  rabbit
//  012345
//  rabbit

// 0123456
// rabbbit


class Solution {
private:
    int mem[1000][1000];

    int rec(string& s, string& t, int sn, int tn, int spos, int tpos) {
        // cout << "rec spos " << spos << " tpos " << tpos << endl;

        if( tpos == tn )
            return 1;

        if( mem[spos][tpos] != -1 )
            return mem[spos][tpos];

        int ret = 0;

        // number of remaining chars in t after our curr position in t
        int k = tn-1-tpos;
        for(int i = spos; i < sn-k; ++i)
            if( s[i] == t[tpos] )
                ret += rec(s,t,sn,tn,i+1,tpos+1);


        return mem[spos][tpos] = ret;
    }

public:
    int numDistinct(string s, string t) {
        int sn = s.size();
        int tn = t.size();
        if( sn < tn )
            return 0;
        if( sn == tn )
            return s == t;

        memset(mem,-1,sizeof mem);
        return rec(s,t,sn,tn,0,0);
    }
};
