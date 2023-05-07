
// 443. String Compression
// https://leetcode.com/problems/string-compression/



class Solution {
private:
    int deflate(vector<char>& chars, char c, int cnt, int pos) {

        chars[pos++] = c;
        if( cnt > 1 ) {
            stack<int> stck;
            while( cnt > 0 ) {
                stck.push(cnt % 10);
                cnt /= 10;
            }
            while( !stck.empty() ) {
                chars[pos++] = '0' + stck.top();
                stck.pop();
            }
        }

        return pos;
    }

public:
    int compress(vector<char>& chars) {
        int n = chars.size();
        if( n == 1 )
            return 1;

        char pre = chars[0];
        int cnt = 1;
        int j = 0;                      // idx we write to
        for(int i = 1; i < n; ++i) {    // idx we investigate
            if( chars[i] != pre ) {

                j = deflate(chars,pre,cnt,j);
                pre = chars[i];
                cnt = 1;
            } else {
                ++cnt;
            }
        }
        // finish up
        j = deflate(chars,pre,cnt,j);

        return j;
    }
};
