
// 2075. Decode the Slanted Ciphertext
// https://leetcode.com/problems/decode-the-slanted-ciphertext/




class Solution {
public:
    string decodeCiphertext(string& encodedText, int rows) {
        if( rows == 1 )
            return encodedText;

        string ans = "";

        int n = encodedText.size();
        int cols = n / rows;

        int encodedText_idx;
        int spaces = 0;
        for(int c = 0; c < cols; ++c) {
            for(int i = 0; i < rows; ++i) {
                int j = c + i;
                if( j == cols )
                    break;

                encodedText_idx = i * cols + j;
                if( encodedText[encodedText_idx] == ' ' ) {
                    ++spaces;
                } else {
                    while( spaces > 0 ) {
                        ans = ans + ' ';
                        --spaces;
                    }
                    ans = ans + encodedText[encodedText_idx];
                }
            }
        }

        return ans;
    }
};
