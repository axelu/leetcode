
// 157. Read N Characters Given Read4
// https://leetcode.com/problems/read-n-characters-given-read4/




/**
 * The read4 API is defined in the parent class Reader4.
 *     int read4(char *buf4);
 */

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    int read(char *buf, int n) {

        // read4 will read 4 or lesss chars
        // if less than 4, then there are no more chars left in the 'file'
        char buf4[4];
        int cntBuf4, red;
        int ans = 0;
        while(true) {
            cntBuf4 = read4(buf4);
            red = 0;
            while(ans<n && red<cntBuf4) {
                buf[ans] = buf4[red];
                ++ans;
                ++red;
            }
            if( ans == n ) break;
            if( cntBuf4 < 4 ) break;
        }

        return ans;
    }
};
