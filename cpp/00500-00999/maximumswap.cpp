
// 670. Maximum Swap
// https://leetcode.com/problems/maximum-swap/





class Solution {
public:
    int maximumSwap(int num) {
        if( num < 10 )
            return num;

        string s = to_string(num);
        int n = s.size();

        // find the 1st digit from the left less than 9
        // try to find a digit from the right greater that digit
        // if found swqp, otherwise repeat

        bool f = false;
        for(int i = 0; i < n && f == false; ++i) {
            char a = s[i];
            if( a == '9' )
                continue;

            char mx  = a;
            int idx = -1;
            for(int j = n-1; j > i; --j) {
                char b = s[j];
                if( b > mx ) {
                    mx = b;
                    idx = j;
                }
            }

            if( mx > a ) {
                s[idx] = a;
                s[i] = mx;
                break;
            }
        }

        return stoi(s);
    }
};
