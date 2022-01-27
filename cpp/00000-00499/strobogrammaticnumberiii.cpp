
// 248. Strobogrammatic Number III
// https://leetcode.com/problems/strobogrammatic-number-iii/



class Solution {
private:
    int ans;

    void cmp(string& s, int n, string& low, string& high) {
        if( low.size() == high.size() ) {
            if( low <= s && s <= high) ++ans;
        } else if( low.size() == n ) {
            if( low <= s ) ++ans;
        } else {
            // high.size() == n
            if( s <= high) ++ans;
        }
    }

    void rec(string& s, int n, int l, int r, string& low, string& high) {
        // cout << "rec n " << n << " l " << l << " r " << r << endl;
        if( l == r ) {
            if( low.size() < n && n < high.size() ) {
                ans += 3;
            } else {
                s[l]='0';cmp(s,n,low,high);
                s[l]='1';cmp(s,n,low,high);
                s[l]='8';cmp(s,n,low,high);
            }
        } else if( l+1 == r ) {
            if( n > 2 ) {
                if( low.size() < n && n < high.size() ) {
                    ++ans;
                } else {
                    s[l]='0';s[r]='0';cmp(s,n,low,high);
                }
            }
            if( low.size() < n && n < high.size() ) {
                ans += 4;
            } else {
                s[l]='1';s[r]='1';cmp(s,n,low,high);
                s[l]='8';s[r]='8';cmp(s,n,low,high);
                s[l]='6';s[r]='9';cmp(s,n,low,high);
                s[l]='9';s[r]='6';cmp(s,n,low,high);
            }
        } else {
            if( l > 0 ) {
                s[l] = '0'; s[r] = '0'; rec(s,n,l+1,r-1,low,high);
            }
            s[l] = '1'; s[r] = '1'; rec(s,n,l+1,r-1,low,high);
            s[l] = '8'; s[r] = '8'; rec(s,n,l+1,r-1,low,high);
            s[l] = '6'; s[r] = '9'; rec(s,n,l+1,r-1,low,high);
            s[l] = '9'; s[r] = '6'; rec(s,n,l+1,r-1,low,high);
        }
    }

public:
    int strobogrammaticInRange(string low, string high) {
        ans = 0;
        for(int i = low.size(); i <= high.size(); ++i) {
            string s(i,'a');
            rec(s,i,0,i-1,low,high);
        }
        return ans;
    }
};
