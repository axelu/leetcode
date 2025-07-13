
// 3591. Check if Any Element Has Prime Frequency
// https://leetcode.com/problems/check-if-any-element-has-prime-frequency/




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
    bool checkPrimeFrequency(vector<int>& nums) {
        int cnt[101];memset(cnt,0,sizeof cnt);
        for(int x: nums)
            ++cnt[x];

        for(int i = 0; i <= 100; ++i)
            if( isPrime(cnt[i]) )
                return true;

        return false;
    }
};
