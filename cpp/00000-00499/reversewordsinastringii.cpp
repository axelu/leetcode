
// 186. Reverse Words in a String II
// https://leetcode.com/problems/reverse-words-in-a-string-ii/
// day 8 July 2021 challenge bonus question
// https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/609/week-2-july-8th-july-14th/3806/



class Solution {
private:
    void reverseArr(vector<char>& s, int i, int j) {
        char t;
        while( i < j ) {
            if( s[i] != s[j] ) {
                t = s[i];
                s[i] = s[j];
                s[j] = t;
            }
            ++i;
            --j;
        }
    }

public:
    void reverseWords(vector<char>& s) {
        int n = s.size();
        int i = 0;
        for(; i < n; ++i)
            if( s[i] == ' ' )
                break;
        if( i == n ) // there is only one word
            return;

        // reverse the entire array
        reverseArr(s,0,n-1);

        // reverse words in the arrray
        int lft = 0;
        for(int i = 0; i < n; ++i) {
            if( s[i] == ' ' ) {
                if( i - lft > 1 ) reverseArr(s,lft,i-1);
                lft = i+1;
            }
        }
        // finish up
        if( n - lft > 1 )
            reverseArr(s,lft,n-1);

    }
};
