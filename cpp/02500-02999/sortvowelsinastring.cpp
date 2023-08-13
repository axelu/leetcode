
// 2785. Sort Vowels in a String
// https://leetcode.com/problems/sort-vowels-in-a-string/



class Solution {
public:
    string sortVowels(string s) {
        int n = s.size();

        //        0 1 2 3 4 5 6 7 8 9
        // vowles A E I O U a e i o u
        int vowels[10];memset(vowels,0,sizeof vowels);
        queue<int> vs_idx;
        for(int i = 0; i < n; ++i)
            if( s[i] == 'A' ) {
                ++vowels[0];
                vs_idx.push(i);
            } else if( s[i] == 'E' ) {
                ++vowels[1];
                vs_idx.push(i);
            } else if( s[i] == 'I' ) {
                ++vowels[2];
                vs_idx.push(i);
            } else if( s[i] == 'O' ) {
                ++vowels[3];
                vs_idx.push(i);
            } else if( s[i] == 'U' ) {
                ++vowels[4];
                vs_idx.push(i);
            } else if( s[i] == 'a' ) {
                ++vowels[5];
                vs_idx.push(i);
            } else if( s[i] == 'e' ) {
                ++vowels[6];
                vs_idx.push(i);
            } else if( s[i] == 'i' ) {
                ++vowels[7];
                vs_idx.push(i);
            } else if( s[i] == 'o' ) {
                ++vowels[8];
                vs_idx.push(i);
            } else if( s[i] == 'u' ) {
                ++vowels[9];
                vs_idx.push(i);
            }

        int vowel = 0;
        while( !vs_idx.empty() ) {
            while( vowels[vowel] == 0 )
                ++vowel;
            if( vowel == 0 ) {
                s[vs_idx.front()] = 'A';
            } else if( vowel == 1 ) {
                s[vs_idx.front()] = 'E';
            } else if( vowel == 2 ) {
                s[vs_idx.front()] = 'I';
            } else if( vowel == 3 ) {
                s[vs_idx.front()] = 'O';
            } else if( vowel == 4 ) {
                s[vs_idx.front()] = 'U';
            } else if( vowel == 5 ) {
                s[vs_idx.front()] = 'a';
            } else if( vowel ==6 ) {
                s[vs_idx.front()] = 'e';
            } else if( vowel == 7 ) {
                s[vs_idx.front()] = 'i';
            } else if( vowel == 8 ) {
                s[vs_idx.front()] = 'o';
            } else {
                s[vs_idx.front()] = 'u';
            }
            --vowels[vowel];
            vs_idx.pop();
        }

        return s;
    }
};
