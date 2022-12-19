
// 2060. Check if an Original String Exists Given Two Encoded Strings
// https://leetcode.com/problems/check-if-an-original-string-exists-given-two-encoded-strings/



class Solution {
private:
    int n1,n2;
    char * s1;
    char * s2;

    int mem[41][41][2001];

    bool rec(int s1_idx, int s1_len, int s2_idx, int s2_len) {
        //cout << "rec s1_idx " << s1_idx << " s1_len " << s1_len;
        //cout << " s2_idx " << s2_idx << " s2_len " << s2_len;
        //cout << endl;

        if( s1_idx == n1 && s2_idx == n2 )
            return s1_len == s2_len;

        if( s1_len == s2_len &&
            s1_idx < n1 && islower(s1[s1_idx]) &&
            s2_idx < n2 && islower(s2[s2_idx]) &&
            s1[s1_idx] != s2[s2_idx] ) {

            return false;
        }

        // what matters is the relative difference between s1_len and s2_len
        // max for either is 999, hence offset by that
        if( mem[s1_idx][s2_idx][s1_len-s2_len+1000] != -1 )
           return mem[s1_idx][s2_idx][s1_len-s2_len+1000];

        // cases:
        // alpha alpha
        // alpha digit
        // digit alpha
        // digit digit

        bool f = false;

        int k = 0;
        int t = 0;
        while( !f && k < 3 && s1_idx + k < n1 && isdigit(s1[s1_idx+k]) ) {
            t = t * 10 + (s1[s1_idx+k]-'0');
            f = rec(s1_idx+1+k,s1_len+t,s2_idx,s2_len);
            ++k;
        }

        k = 0;
        t = 0;
        while( !f && k < 3 && s2_idx + k < n2 && isdigit(s2[s2_idx+k]) ) {
            t = t * 10 + (s2[s2_idx+k]-'0');
            f = rec(s1_idx,s1_len,s2_idx+1+k,s2_len+t);
            ++k;
        }

        // s1 ran out and s2 is alpha
        if( !f && s1_idx == n1 && islower(s2[s2_idx]) && s2_len < s1_len )
            f = rec(s1_idx,s1_len,s2_idx+1,s2_len+1);

        // s2 ran out and s1 is alpha
        if( !f && s2_idx == n2 && islower(s1[s1_idx]) && s1_len < s2_len )
            f = rec(s1_idx+1,s1_len+1,s2_idx,s2_len);

        if( !f && s1_idx < n1 && islower(s1[s1_idx]) && s2_idx < n2 && islower(s2[s2_idx]) )
            if( s1_len < s2_len )
                f = rec(s1_idx+1,s1_len+1,s2_idx,s2_len);
            else
                f = rec(s1_idx,s1_len,s2_idx+1,s2_len+1);

        return mem[s1_idx][s2_idx][s1_len-s2_len+1000] = f;
        // return f;
    }
public:
    bool possiblyEquals(string s1, string s2) {
        n1 = s1.size();
        this->s1 = s1.data();
        n2 = s2.size();
        this->s2 = s2.data();

        // cout << "n1 " << n1 << " n2 " << n2 << endl;

        memset(mem,-1,sizeof mem);
        return rec(0,0,0,0);
    }
};
