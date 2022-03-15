
// 727. Minimum Window Subsequence
// https://leetcode.com/problems/minimum-window-subsequence/


class Solution {
private:
    int n1,n2;
    int mn,idx;
    bool f;

    int rec(string& s1, string& s2, int pos1, int pos2, int mem[][100]) {
        if( pos2 == n2 ) {
            f = true;
            return 0;
        }

        if( mem[pos1][pos2] != -1 )
            return mem[pos1][pos2];

        // remaining length
        int s1_rem = n1-pos1;
        int s2_rem = n2-pos2;
        if( s1_rem == s2_rem ) {
            // no need to go any further as the remaining
            // length of both strings is equal
            if( s1.substr(pos1) == s2.substr(pos2) ) {
                f = true;
                if( pos2 == 0 ) {
                    // the current length is the shortest length possible
                    // s1_rem == s2_rem == n2
                    if( n2 < mn ) {
                        idx = pos1;
                        mn = n2;
                    }
                }
                return s1_rem;
            } else {
                return 100000;
            }
        }

        // we have a choice
        // if the current char in s1 matches current char in s2
        // we can either take it and continue in s1 at pos1+1 with s2[pos2+1,n2-1] OR
        // we can assume we find something better by going on in s1 at pos1+1 with s2[pos2,n2-1]

        int t1 = 100000;
        if( s1[pos1] == s2[pos2] )
            t1 = 1 + rec(s1,s2,pos1+1,pos2+1,mem);

        int t2 = 1 + rec(s1,s2,pos1+1,pos2,mem);

        if( s1[pos1] == s2[pos2] && pos2 == 0 ) {
            if( t1 < mn ) {
                mn  = t1;
                idx = pos1;
            } else if( t1 == mn && pos1 < idx ) {
                idx = pos1;
            }
        }

        return mem[pos1][pos2] = min(t1,t2);
    }

public:
    string minWindow(string& s1, string& s2) {
        n1 = s1.size();
        n2 = s2.size();
        if( n2 > n1 )
            return "";
        if( n1 == n2 )
            return s1 == s2 ? s1 : "";

        mn  = 100000;
        idx = 100000;
        f   = false;
        int mem[n1][100];memset(mem,-1,sizeof mem);

        rec(s1,s2,0,0,mem);
        // cout << "mn " << mn << " idx " << idx << " f " << f << endl;
        return f ? s1.substr(idx,mn) : "";
    }
};
