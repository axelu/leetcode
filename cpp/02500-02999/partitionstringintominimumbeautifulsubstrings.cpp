
// 2767. Partition String Into Minimum Beautiful Substrings
// https://leetcode.com/problems/partition-string-into-minimum-beautiful-substrings/






/*
powers of 5
    decimal binary          bits
5^0	    1	             1	 1
5^1	    5	           101	 3
5^2	   25	         11001	 5
5^3	  125	       1111101	 7
5^4	  625	    1001110001	10
5^5	 3125	  110000110101	12
5^6	15625	11110100001001	14

 */
class Solution {
private:
    int mem[16];

    int rec(string& s, int n, int pos) {
        // return 0 if there is no solution OR
        // return min nbr of solutions greater 0
        if( s[pos] == '0' )
            return 0;

        if( mem[pos] != -1 )
            return mem[pos];

        int ret = INT_MAX;

        for(int i = pos; i < n; ++i) {
            int l = i - pos + 1;
            if( (l == 1 && s.substr(pos,l) == "1") ||
                (l == 3 && s.substr(pos,l) == "101") ||
                (l == 5 && s.substr(pos,l) == "11001") ||
                (l == 7 && s.substr(pos,l) == "1111101") ||
                (l == 10 && s.substr(pos,l) == "1001110001") ||
                (l == 12 && s.substr(pos,l) == "110000110101") ||
                (l == 14 && s.substr(pos,l) == "11110100001001") ) {

                if( i < n-1 ) {
                    int t = rec(s,n,i+1);
                    if( t > 0 ) {
                        if( ret == INT_MAX )
                            ret = 1 + t;
                        else
                            ret = min(ret, 1 + t);
                    }
                } else { // i == n-1
                    ret = 1;
                }
            }

        }

        if( ret == INT_MAX )
            ret = 0;

        return mem[pos] = ret;
    }

public:
    int minimumBeautifulSubstrings(string s) {
        if( s[0] == '0' )
            return -1;

        memset(mem,-1,sizeof mem);
        int ans = rec(s,s.size(),0);
        return ans == 0 ? -1 : ans;
    }
};
