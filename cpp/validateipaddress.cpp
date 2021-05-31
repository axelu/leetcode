
// 468. Validate IP Address
// https://leetcode.com/problems/validate-ip-address/




class Solution {
private:
    bool validOctet(string& s, int b, int e) {
        if( b == e ) {
            // 1 digit
            if( !isdigit(s[b]) ) return false;
            return true;
        } else if( e - b == 1 ) {
            // 2 digits
            if( !isdigit(s[b]) ) return false;
            if( !isdigit(s[e]) ) return false;
            if( s[b] == '0' ) return false;
            return true;
        } else if( e - b == 2 ) {
            // 3 digts
            if( !isdigit(s[b])   ) return false;
            if( !isdigit(s[b+1]) ) return false;
            if( !isdigit(s[e])   ) return false;
            if( s[b] == '0'  ) return false;
            if( s[b] > '2'   ) return false;
            if( s[b] == '2' && s[b+1] > '5' ) return false;
            if( s[b] == '2' && s[b+1] == '5' && s[b+2] > '5') return false;
            return true;
        } else {
            return false;
        }
    }

public:
    string validIPAddress(string IP) {
        int n = IP.size();
        if( n < 7 ) return "Neither";

        vector<int> dots;
        vector<int> colons;
        for(int i = 0; i < IP.size(); ++i) {
            if( IP[i] == '.' ) dots.push_back(i);
            if( IP[i] == ':' ) colons.push_back(i);
        }
        if( (dots.size() == 0 && colons.size() == 0) ||
            (dots.size() != 0 && colons.size() != 0 ) )
            return "Netiher";

        if( dots.size() == 3 ) {
            if( !validOctet(IP,0,dots[0]-1) )           return "Neither";
            if( !validOctet(IP,dots[0]+1,dots[1]-1) )   return "Neither";
            if( !validOctet(IP,dots[1]+1,dots[2]-1) )   return "Neither";
            if( !validOctet(IP,dots[2]+1,IP.size()-1) ) return "Neither";
            return "IPv4";
        }
        if( colons.size() == 7 ) {
            colons.push_back(IP.size());
            int b = 0,e;
            for(int i = 0; i < 8; ++i) {
                e = colons[i]-1;
                if( e-b < 0 || e-b > 3) return "Neither";
                for(int j = b; j <= e; ++j) {
                    if( !isdigit(IP[j]) && !isalpha(IP[j]) )
                        return "Neither";
                    if( isalpha(IP[j]) ) {
                        if( ( IP[j] >= 71 && IP[j] <= 90   ) ||
                            ( IP[j] >= 103 && IP[j] <= 122 ) )
                            return "Neither";
                    }
                }
                b = e+2;
            }
            return "IPv6";
        }
        return "Neither";
    }
};
