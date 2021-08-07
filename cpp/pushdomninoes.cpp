
// 838. Push Dominoes
// https://leetcode.com/problems/push-dominoes/
// https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/610/week-3-july-15th-july-21st/3821/





class Solution {
public:
    string pushDominoes(string& dominoes) {
        int n = dominoes.size();
        if( n == 1 )
            return dominoes;

        // idea: we only need to find out what happens to initially vertical dominoes
        //    to answer that, we need to know what is to the right and left of
        //    a contigous subarray of vertical dominoes
        //    so we will slide a window accross and process what is in between
        //    there will be nine states (permutation w/ repetition of 3 things taken 2 at a time)
        //    left | right
        //    -----+------
        //      L  |   L
        //      R  |   L
        //      L  |   R
        //      R  |   R
        //      .  |   .
        //      .  |   L
        //      L  |   .
        //      .  |   R
        //      R  |   .

        int i = 0;                   // left index
        for(int j = 1; j < n; ++j) { // right index

            if( j != n-1 && dominoes[j] == '.' )
                continue;

            if( dominoes[i] == 'L' && dominoes[j] == 'L' ) {
                ++i;
                for(; i < j; ++i)
                    dominoes[i] = 'L';
            } else if( dominoes[i] == 'R' && dominoes[j] == 'L' ) {
                ++i;
                int t = j-1;
                while( i < t ) {
                    dominoes[i] = 'R';
                    dominoes[t] = 'L';
                    ++i;
                    --t;
                }
            } else if( dominoes[i] == 'L' && dominoes[j] == 'R' ) {
                // do nothing
            } else if( dominoes[i] == 'R' && dominoes[j] == 'R' ) {
                int t = j-1;
                for(; t > i; --t)
                    dominoes[t] = 'R';
            } else if( dominoes[i] == '.' && dominoes[j] == '.' ) {
                // do nothing
            } else if( dominoes[i] == '.' && dominoes[j] == 'L' ) {
                int t = j-1;
                for(; t >= i; --t)
                    dominoes[t] = 'L';
            } else if( dominoes[i] == 'L' && dominoes[j] == '.' ) {
                // do nothing
            } else if( dominoes[i] == '.' && dominoes[j] == 'R' ) {
                // do nothing
            } else if( dominoes[i] == 'R' && dominoes[j] == '.' ) {
                ++i;
                for(; i <= j; ++i)
                    dominoes[i] = 'R';
            }

            i = j;
        }

        return dominoes;
    }
};
