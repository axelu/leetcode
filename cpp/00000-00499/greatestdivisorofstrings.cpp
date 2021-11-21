
// 071. Greatest Common Divisor of Strings
// https://leetcode.com/problems/greatest-common-divisor-of-strings/



class Solution {
public:
    string gcdOfStrings(string str1, string str2) {
        if( str1 == str2 ) return str1;
        size_t n1 = str1.size();
        size_t n2 = str2.size();
        if( n1 == n2 ) return "";

        if( n1 < n2 ) {
            string s = str2;
            str2 = str1;
            str1 = s;
            int t = n2;
            n2 = n1;
            n1 = t;
        }
        // str2 is now the shorter string, n2 < n1

        int n = n2;
        int i = 1;
        string r = "";
        string t,t1,t2;
        while(n > 0) {
            t2 = "";
            if( n2 % i == 0 ) {
                t = str2.substr(0,n);
                for(int j = 0; j < i; ++j) t2 += t;
                if( t2 == str2 ) {
                    t1 = t2;
                    while( t1.size() <= n1 ) {
                        if( t1.size() == n1 && t1 == str1 ) {
                            r = t;
                            break;
                        }
                        t1 += t;
                    }
                }
            }
            if( r != "" ) break;
            ++i;
            n = n2/i;
        }

        return r;
    }
};
