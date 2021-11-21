
// 93. Restore IP Addresses
// https://leetcode.com/problems/restore-ip-addresses/




class Solution {
private:
    bool validOctet(string& s, int b, int e) {
        if( b == e ) {
            // 1 digit
            return true;
        } else if( e - b == 1 ) {
            // 2 digits
            if( s[b] == '0' ) return false;
            return true;
        } else if( e - b == 2 ) {
            // 3 digts
            if( s[b] == '0'  ) return false;
            if( s[b] > '2'   ) return false;
            if( s[b] == '2' && s[b+1] > '5' ) return false;
            if( s[b] == '2' && s[b+1] == '5' && s[b+2] > '5') return false;
            return true;
        } else {
            return false;
        }
    }

    void rec(string& s, int& n, int pos, string& t, int cnt, vector<string>& ans) {
        // cout << "rec " << pos << " " << cnt << " " << t << endl;

        if( cnt == 3 ) {
            if( validOctet(s,pos,n-1) )
                ans.push_back(t+s.substr(pos));
            return;
        }

        // at each pos we can place a period after
        //    - our current pos
        //    - our current pos+1
        //    - our current pos+2

        for(int i = 1; i <= 3; ++i) {
            if( pos+i <= n-1 && validOctet(s,pos,pos+i-1) ) {
                ++cnt;
                t += s.substr(pos,i) + ".";
                rec(s,n,pos+i,t,cnt,ans);
                // backtrack
                --cnt;
                for(int j = 0; j < i+1; ++j)
                    t.pop_back();
            }
        }
    }


public:
    vector<string> restoreIpAddresses(string& s) {
        int n = s.size();
        vector<string> ans;
        if( n < 4  || n > 12 ) return ans;

        string t = "";
        rec(s,n,0,t,0,ans);
        return ans;
    }
};
