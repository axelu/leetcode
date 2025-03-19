
// 3403. Find the Lexicographically Largest String From the Box I
// https://leetcode.com/problems/find-the-lexicographically-largest-string-from-the-box-i/





/* Definition lexicographically smaller
 * A string a is lexicographically smaller than a string b
 * if in the first position where a and b differ, string a has a letter
 * that appears earlier in the alphabet than the corresponding letter in b.
 * If the first min(a.length, b.length) characters do not differ,
 * then the shorter string is the lexicographically smaller one.
 */
class Solution {
private:
    bool cmp(string& a, string& b) {
        // returns true if string a is lexicographically smaller than string b
        // it is guaranteed that a and b are non-empty

        int a_sz = a.size();
        int b_sz = b.size();
        for(int i = 0; i < a_sz && i < b_sz; ++i)
            if( a[i] != b[i] )
                return a[i] < b[i];

        return a_sz < b_sz;
    }

public:
    string answerString(string word, int numFriends) {
        if( numFriends == 1 )
            return word;

        int n = word.size();

        if( numFriends == n ) {
            char mx_chr = word[0];
            for(char chr : word )
                mx_chr = max(mx_chr, chr);
            return string(1,(char)mx_chr);
        }

        // find all occurences of the largest letter in word
        // if only 1, than the longest length possible substring
        // starting at that char is our ans
        // longest length possible substring
        // n - (numFriends-1) but watch out for it going beyond the end
        // based on the pos of char

        int mxl = n - (numFriends-1);

        vector<int> positions[26];
        for(int i = 0; i < n; ++i)
            positions[word[i]-'a'].push_back(i);

        string a;
        for(int i = 25; i >= 0; --i) {
            if( !positions[i].empty() ) {
                int s = positions[i][0];
                int e = min(s + mxl - 1, n-1);
                a = word.substr(s, e-s+1);

                for(int j = 1; j < positions[i].size(); ++j) {
                    s = positions[i][j];
                    e = min(s + mxl - 1, n-1);
                    string b = word.substr(s, e-s+1);
                    if( cmp(a, b) )
                        swap(a,b);
                }
                break;
            }
        }

        return a;
    }
};
