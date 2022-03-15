
// 2140. Solving Questions With Brainpower
// https://leetcode.com/problems/solving-questions-with-brainpower/




class Solution {
private:
    long long rec(vector<vector<int>>& questions, int& n, int i, long long mem[]) {
        if( i >= n )
            return 0;

        if( mem[i] != -1LL )
            return mem[i];

        // we have a choice
        // skip the current question
        // take the current question having to skip the next
        //     question[i][1] questions, meaning continue at i + question[i][1] + 1
        long long a = rec(questions,n,i+1,mem);

        long long b = (long long)questions[i][0] + rec(questions,n,i+questions[i][1]+1,mem);

        return mem[i] = max(a,b);
    }

public:
    long long mostPoints(vector<vector<int>>& questions) {
        int n = questions.size();

        /*
        // top down recursion + memoization
        long long mem[n];
        for(int i = 0; i < n; ++i)
            mem[i] = -1LL;
        return rec(questions,n,0,mem);
        */


        // bottom up
        if( n == 1 )
            return questions[0][0];

        long long dp[n];
        dp[n-1] = questions[n-1][0];
        long long a,b;
        for(int i = n-2; i >= 0; --i) {
            // skip current question
            a = dp[i+1];

            // solve current question
            b = questions[i][0];
            if( i + questions[i][1] + 1 < n )
                b += dp[i + questions[i][1] + 1];

            dp[i] = max(a,b);
        }

        return dp[0];
    }
};
