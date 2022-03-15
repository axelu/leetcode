
// 2063. Vowels of All Substrings
// https://leetcode.com/problems/vowels-of-all-substrings/



/*
 * example
 *        0  1  2  3
 *        a  b  a  a   -> ans = 14
 * -----------------
 * i = 0  a
 * i = 1     b
 *        a  b
 * i = 2        a
 *           b  a
 *        a  b  a
 * i = 3           a
 *              a  a
 *           b  a  a
 *        a  b  a  a
 *
 * at any position we need to count
 * how many times the current vowel will show up till the end +
 * how many times the vowel will show up from the front
*/
class Solution {
public:
    long long countVowels(string word) {
        int n = word.size();

        long long ans = 0LL;
        long long after,before;
        char c;
        for(int i = 0; i < n; ++i) {
            c = word[i];
            if( c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ) {
                after = n - i;
                before = (long long)i * after;
                ans += before + after;
            }
        }

        return ans;
    }
};
