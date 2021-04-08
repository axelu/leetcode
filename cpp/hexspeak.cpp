
// 1271. Hexspeak
// https://leetcode.com/problems/hexspeak/



class Solution {
private:
    // https://leetcode.com/problems/convert-a-number-to-hexadecimal/
    string toHex(long num) {
        string ans = "";
        long rem;
        while( num > 0 ) {
            rem = num % 16L;
            if( rem > 9L )
                ans.insert(ans.begin(),'7' + rem);
            else
                ans = to_string(rem) + ans;
            num /= 16L;
        }
        return ans;
    }

public:
    string toHexspeak(string num) {
        // 1 <= N <= 10^12
        string hex = toHex(stol(num));
        for(int i = 0; i < hex.size(); ++i) {
            if(hex[i] == 'A' || hex[i] == 'B' || hex[i] == 'C' ||
               hex[i] == 'D' || hex[i] == 'E' || hex[i] == 'F' ) {
                // do nothing
            } else if( hex[i] == '0' ) {
                hex[i] = 'O';
            } else if( hex[i] == '1' ) {
                hex[i] = 'I';
            } else {
                return "ERROR";
            }
        }
        return hex;
    }
};
