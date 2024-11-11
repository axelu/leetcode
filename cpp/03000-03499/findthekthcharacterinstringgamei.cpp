
// 3304. Find the K-th Character in String Game I
// https://leetcode.com/problems/find-the-k-th-character-in-string-game-i/



class Solution {
public:
    char kthCharacter(int k) {
        // 1 <= k <= 500

        // brute force
        string word = "a";

        while( true ) {
            string s = "";
            for(char c: word) {
                char new_char = c + 1;
                if( c == 123 )
                    c = 'a';
                s.push_back(new_char);
            }
            word = word + s;
            if( word.size() >= k )
                break;
        }

        return word[k-1];
    }
};
