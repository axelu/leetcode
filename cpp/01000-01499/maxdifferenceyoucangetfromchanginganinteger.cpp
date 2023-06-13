
// 1432. Max Difference You Can Get From Changing an Integer
// https://leetcode.com/problems/max-difference-you-can-get-from-changing-an-integer/



class Solution {
private:
    int convert(string s, char t, char p) {
        // replace all occurences of t in s with p
        for(int i = 0; i < s.size(); ++i)
            if( s[i] == t )
                s[i] = p;

        return stoi(s);
    }

public:
    int maxDiff(int num) {
        string str = to_string(num);

        // max
        int mx = num;
        if( str.size() == 1 ) {
            mx = 9;
        } else {
            for(int i = 0; i < str.size(); ++i) {
                if( str[i] != '9' ){
                    mx = convert(str,str[i],'9');
                    break;
                }
            }
        }
        // cout << "max " << mx << endl;

        // min
        int mn = num;
        if( str.size() == 1 ) {
            mn = 1;
        } else {
            if( str[0] == '1' ) {
                for(int i = 1; i < str.size(); ++i) {
                    if( str[i] != '1' &&  str[i] != '0' ) {
                        mn = convert(str,str[i],'0');
                        break;
                    }
                }
            } else {
                mn = convert(str,str[0],'1');
            }
        }
        // cout << "min " << mn << endl;

        return mx - mn;
    }
};
