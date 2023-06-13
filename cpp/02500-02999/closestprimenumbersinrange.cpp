
// 2523. Closest Prime Numbers in Range
// https://leetcode.com/problems/closest-prime-numbers-in-range/




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

public:
    vector<int> closestPrimes(int left, int right) {
        // brute force

        int pre = -1;
        int mn = INT_MAX;

        vector<int> ans = {-1,-1};

        for(int i = left; i <= right; ++i) {
            if( isPrime(i) ) {
                if(pre != -1 ) {

                    int diff = i - pre;
                    if( diff < mn ) {
                        mn = diff;
                        ans[0] = pre;
                        ans[1] = i;
                    }
                }
                pre = i;
            }
        }

        return ans;
    }
};
