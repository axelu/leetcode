
// 1056. Confusing Number
// https://leetcode.com/problems/confusing-number/



class Solution {
public:
    bool confusingNumber(int N) {
        string t = to_string(N), s = "";

        for(int i = 0; i < t.size(); ++i) {
            if( t[i] == '2' || t[i] == '3' || t[i] == '4' || t[i] == '5' || t[i] == '7' )
                return false;
            if( t[i] == '0' )
                s = '0' + s;
            else if( t[i] == '1' )
                s = '1' + s;
            else if( t[i] == '6' )
                s = '9' + s;
            else if( t[i] == '8' )
                s = '8' + s;
            else
                s = '6' + s;
        }
        return N != stoi(s);
    }
};
