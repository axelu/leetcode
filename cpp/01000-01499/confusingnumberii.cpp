
// 1088. Confusing Number II
// https://leetcode.com/problems/confusing-number-ii/


// apprached based on provided solution

class Solution {
private:
    char other(char c) {
        switch(c) {
            case '0' :  break;
            case '1' :  break;
            case '8' :  break;
            case '6' :  c = '9';
                        break;
            case '9' :  c = '6';
                        break;
            default :   c = '?';
                        break;
        }
        return c;
    }

    char digits[5] = {'0','1','6','8','9'};

    int rec(string& s, bool smaller, string& num) {
        if( num.size() == s.size() ) {

            // skip leading zeros
            auto fi = num.begin();
            while( fi != num.end() && *fi == '0' )
                ++fi;

            auto ri = num.rbegin();
            while( fi < ri.base() ) {
                if( *fi != other(*ri) )
                    return 1;
                ++fi;
                ++ri;
            }
            return 0;
        }

        int ret = 0;

        for(char c : digits) {
            if( !smaller && c > s[num.size()] )
                break;

            num.push_back(c);
            ret += rec(s, smaller || c < s[num.size() - 1], num);
            num.pop_back(); // back tracking
        }

        return ret;
    }


public:
    int confusingNumberII(int n) {
        string s = to_string(n);
        string num = "";

        return rec(s,false,num);
    }
};
