
// 2355. Maximum Number of Books You Can Take
// https://leetcode.com/problems/maximum-number-of-books-you-can-take/

class Solution {    
public:
    long long maximumBooks(vector<int>& books) {
        int n = books.size();
        if( n == 1 )
            return books[0];
        
        // precalc
        long long mem[100002];
        mem[0] = 0;
        for(int i = 1; i <= 100001; ++i)
            mem[i] = i-1 + mem[i-1];
                
        // dp[i] is the maximum number of books we can take,
        // if we can only take books from bookshelves 0 to i and 
        // we must take books from bookshelf i.
        long long dp[n];
        dp[0] = books[0];
        
        stack<int> stck;
        stck.push(0);
        for(int i = 1; i < n; ++i) {
            
            while( !stck.empty() && books[stck.top()] > books[i] - (i-stck.top()) )
                stck.pop();
                
            if( stck.empty() )
                dp[i] = mem[books[i]+1] - mem[max(0,books[i]-i)];
            else
                dp[i] = dp[stck.top()] + mem[books[i]+1] - mem[max(0,books[i]-(i-stck.top()-1))];
            stck.push(i);
        }
        
        long long ans = 0;
        for(int i = 0; i < n; ++i)
            ans = max(ans,dp[i]);
        
        return ans;
    }
};
