
// 2957. Remove Adjacent Almost-Equal Characters
// https://leetcode.com/problems/remove-adjacent-almost-equal-characters/





class Solution {
private:
    int mem[100][30];

    int rec(string& word, int n, int pos, int prev_chr) {
        if( pos == n )
            return 0;

        if( mem[pos][prev_chr] != -1 )
            return mem[pos][prev_chr];

        // we have a choice
        //     leave the char at pos as-is if not adjacent to prior char OR
        //     change it to any other char other than curr char and not adjacent to prev

        int curr_chr = word[pos] - 'a';

        int a = 101;
        if( curr_chr != prev_chr - 1 && curr_chr != prev_chr && curr_chr != prev_chr + 1 )
            a = rec(word,n,pos+1,curr_chr);

        int b = 101;
        for(int i = 0; i < 26; ++i) {
            if( i == curr_chr || i == prev_chr - 1 || i == prev_chr || i == prev_chr + 1)
                continue;

            b = min(b, 1 + rec(word,n,pos+1,i));
        }

        return mem[pos][prev_chr] = min(a,b);
    }

public:
    int removeAlmostEqualCharacters(string& word) {
        int n = word.size(); // 1 <= work <= 100

        memset(mem,-1,sizeof mem);
        return rec(word,n,0,29);
    }
};
