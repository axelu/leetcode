
// 1702. Maximum Binary String After Change
// https://leetcode.com/problems/maximum-binary-string-after-change/



class Solution {
public:
    string maximumBinaryString(string binary) {
        // op1: 00 -> 10
        // op2: 10 -> 01

        // observation:
        //    the best we can get to is that one zero is left in binary
        //    now the question becomes: at what pos is the remaining zero?
        //    let k be number of 1s to the right of the left most zero
        //    pos of remaining zero = (n-1) - k

        int n = binary.size();

        bool seen_zero = false;
        int k = 0;
        for(int i = 0; i < n; ++i) {

            if( binary[i] == '0' ) {
                seen_zero = true;
                binary[i] = '1';

            } else  if( seen_zero && binary[i] == '1' ) {
                ++k;
            }
        }

        if( seen_zero )
            binary[n-1-k] = '0';

        return binary;
    }
};
