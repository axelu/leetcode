
// 1839. Longest Substring Of All Vowels in Order
// https://leetcode.com/problems/longest-substring-of-all-vowels-in-order/



class Solution {
public:
    int longestBeautifulSubstring(string word) {
        // vowels aeiou
        int n = word.size();
        if( n < 5 )
            return 0;

        int ans = 0;

        int j;
        char c,pre;
        for(int i = 0; i <= n-5; ++i) {    // left index
            if( word[i] != 'a' )
                continue;

            pre = 'a';
            // expand to the right side as long as the expected letter
            for(j = i+1; j < n; ++j) {  // right index
                c = word[j];
                if( c == 'u' && c == pre ) {
                    ans = max(ans,j-i+1);
                } else if( c > pre ) {
                    if( pre == 'a' && c == 'e' )
                        pre = 'e';
                    else if( pre == 'e' && c == 'i' )
                        pre = 'i';
                    else if( pre == 'i' && c == 'o' )
                        pre = 'o';
                    else if( pre == 'o' ) { // c must be 'u'
                        pre = 'u';
                        ans = max(ans,j-i+1);
                    } else {
                        i = j-1; // loop will advance i
                        break;
                    }
                } else if( c < pre ) {
                    i = j-1; // loop will advance i
                    break;
                }
            }
            if( j == n )
                break;
        }

        return ans;
    }
};
