

// 1255. Maximum Score Words Formed by Letters
// https://leetcode.com/problems/maximum-score-words-formed-by-letters/



class Solution {
private:
    int chars[26];

    int rec(vector<string>& words, int n, int i, vector<int>& score) {
        if( i == n )
            return 0;

        // we have  choice
        //    don't form the current word, or
        //    form the current word (if we can)

        int a = rec(words,n,i+1,score);

        int word_i_sz = words[i].size();
        int k = 0;
        int pts = 0;
        for(; k < word_i_sz; ++k) {
            if( chars[words[i][k]-'a'] > 0 ) {
                --chars[words[i][k]-'a'];
                pts += score[words[i][k]-'a'];
            } else {
                break;
            }
        }
        int b = 0;
        if( k == word_i_sz ) { // we were able to make the word
            b = pts + rec(words,n,i+1,score);
        }
        // backtrack
        --k;
        for(; k >= 0; --k)
           ++chars[words[i][k]-'a'];

        return max(a,b);
    }

public:
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        int n = words.size();

        memset(chars,0,sizeof chars);

        for(int i = 0; i < letters.size(); ++i)
            ++chars[letters[i]-'a'];

        return rec(words,n,0,score);
    }
};
