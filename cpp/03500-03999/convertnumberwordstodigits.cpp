
// 3758. Convert Number Words to Digits
// https://leetcode.com/problems/convert-number-words-to-digits/



class Solution {
private:
    bool is_digit_word(string& s, int i, string& word) {
        int n = s.size();
        int m = word.size();
        bool f = true;
        int k = 1;
        for(int j = i+1; j < n && k < m; ++j, ++k) {
            if( s[j] != word[k] ) {
                f = false;
                break;
            }
        }
        return f && k == m;
    }

public:
    string convertNumber(string s) {
        int n = s.size();

        string ans = "";

        // brute force
        string zero = "zero", one = "one", two = "two", three = "three", four = "four";
        string five = "five", six = "six", seven = "seven", eight = "eight", nine = "nine";
        for(int i = 0; i < n;) {
            char c = s[i];
            if( c == 'z' )
                if( is_digit_word(s, i, zero) ) {
                    ans.push_back('0');
                    i += 4;
                    continue;
                }
            if( c == 'o' )
                if( is_digit_word(s, i, one) ) {
                    ans.push_back('1');
                    i += 3;
                    continue;
                }
            if( c == 't')
                if( is_digit_word(s, i, two) ) {
                    ans.push_back('2');
                    i += 3;
                    continue;
                }
            if( c == 't')
                if( is_digit_word(s, i, three) ) {
                    ans.push_back('3');
                    i += 5;
                    continue;
                }
            if( c == 'f')
                if( is_digit_word(s, i, four) ) {
                    ans.push_back('4');
                    i += 4;
                    continue;
                }
            if( c == 'f')
                if( is_digit_word(s, i, five) ) {
                    ans.push_back('5');
                    i += 4;
                    continue;
                }
            if( c == 's')
                if( is_digit_word(s, i, six) ) {
                    ans.push_back('6');
                    i += 3;
                    continue;
                }
            if( c == 's')
                if( is_digit_word(s, i, seven) ) {
                    ans.push_back('7');
                    i += 5;
                    continue;
                }
            if( c == 'e')
                if( is_digit_word(s, i, eight) ) {
                    ans.push_back('8');
                    i += 5;
                    continue;
                }
            if( c == 'n')
                if( is_digit_word(s, i, nine) ) {
                    ans.push_back('9');
                    i += 4;
                    continue;
                }
            ++i;
        }

        return ans;
    }
};
