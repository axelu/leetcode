
// 158. Read N Characters Given Read4 II - Call multiple times
// https://leetcode.com/problems/read-n-characters-given-read4-ii-call-multiple-times/




/**
 * The read4 API is defined in the parent class Reader4.
 *     int read4(char *buf4);
 */

class Solution {
private:
    bool eof = false; // end of file
    queue<char> q;


public:
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    int read(char *buf, int n) {
        // cout << "read n " << n << " eof " << eof << " q.size() " << q.size() << endl;
        if( eof && q.empty() )
            return 0;

        // we could have something left from our last invocation of read4
        // use that first
        int i = 0; // index into buffer
        while( !q.empty() && n > 0 ) {
            buf[i] = q.front();
            q.pop();
            ++i;
            --n;
        }
        if( n == 0 || eof )
            return i;


        while(true) {
            char buf4[4];
            int r = read4(buf4);

            if( r < 4 )
                eof = true;
            if( r == 0 )
                break;

            for(int j = 0; j < r; ++j) {
                if( n > 0 ) {
                    buf[i] = buf4[j];
                    ++i;
                    --n;
                } else {
                    q.push(buf4[j]);
                }
            }

            if( n == 0 || eof )
                break;
        }

        return i;
    }
};
