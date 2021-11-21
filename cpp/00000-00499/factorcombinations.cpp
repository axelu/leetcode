
// 254. Factor Combinations
// https://leetcode.com/problems/factor-combinations/

class Solution {
private:
    bool isPrime(int n) {
        if( n == 2 || n == 3 )
            return true;

        if( n <= 1 || n % 2 == 0 || n % 3 == 0  )
            return false;

        for(int i = 5; i * i <= n; i += 6 ) {
            if( n % i == 0 || n % (i + 2) == 0 )
                return false;
        }

        return true;
    }

    void rec(int n, vector<int>& prefix, vector<vector<int>>& ans) {        
        if( isPrime(n) )
            return;
        
        for(int i = 2; i*i <= n; ++i) {
            if( n%i == 0 ) {
                // n is divisible by i
                // add solution to answer
                int q = n/i;
                if( !prefix.empty() && i < prefix.back() ) // keep it unique
                    continue;
                prefix.push_back(i);
                prefix.push_back(q);
                
                ans.push_back(prefix);

                // backtrack
                prefix.pop_back();

                rec(q,prefix,ans);
                // backtrack
                prefix.pop_back();
           }
       }

    }

public:
    vector<vector<int>> getFactors(int n) {
        // 1 <= n <= 10^7
        vector<vector<int>> ans;
        if( n == 1 || isPrime(n) )
            return ans;

        vector<int> prefix;
        rec(n,prefix,ans);

        return ans;
    }
};
