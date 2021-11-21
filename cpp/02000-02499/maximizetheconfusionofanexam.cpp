
// 2024. Maximize the Confusion of an Exam
// https://leetcode.com/problems/maximize-the-confusion-of-an-exam/





class Solution {
private:
    int maxLengthSubarray(string& answerKey, int n, char c, int k) {
        // sliding window
        int ret = 0;
        int cs = 0;                     // number of char c
        int i = 0;                      // left index
        for(int j = 0; j < n; ++j) {    // right index
            if( answerKey[j] == c )
                ++cs;

            if( cs > k ) // we need to shrink our sliding window
                while( i < j && cs > k) {
                    if( answerKey[i] == c )
                        --cs;
                    ++i;
                }

            ret = max(ret,j-i+1);
            if( ret == n )
                return n;
        }

        return ret;
    }



public:
    int maxConsecutiveAnswers(string& answerKey, int k) {
        // we are searching for the maximum length subarray, with either
        // number of Ts <= k OR
        // number of Fs <= k

        int n = answerKey.size(); // this would also be our best possible outcome
        if( k == n )
            return n;

        int T = maxLengthSubarray(answerKey,n,'T',k);
        if( T == n )
            return n;
        return max(T,maxLengthSubarray(answerKey,n,'F',k));
    }
};
