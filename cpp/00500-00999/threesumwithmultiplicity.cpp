
// 923. 3Sum With Multiplicity
// https://leetcode.com/problems/3sum-with-multiplicity/
// day 23 March 2021 challenge
// https://leetcode.com/explore/challenge/card/march-leetcoding-challenge-2021/591/week-4-march-22nd-march-28th/3682/




// resources:
//   calculate number of combinations MOD 10^9+7
//   https://barkingbogart.wordpress.com/2013/02/21/cnk-mod-1000000007/

class Solution {
private:
    int MOD = 1000000007;

    long long modPow(long long a, long long x) {
        // return a^x mod MOD
        long long res = 1;
        while(x>0) {
            if( x & 1 ) res = (res*a) % MOD;
            a = (a*a) % MOD;
            x >>= 1;
        }
        return res;
    }

    long long modInverse(long long a) {
        // return modular multiplicative of: a mod MOD
        return modPow(a,MOD-2);
    }

    long long modCombinations(long long n, long long k) {
        // regular combinations formula C(n,k) = n!/(k!(n-k)!)
        // return C(n,k) mod MOD
        long long numerator = 1; // n*(n-1)* ... * (n-k+1)
        int i;
        for(i=0;i<k;i++) numerator = (numerator*(n-i))%MOD;

        long long denominator = 1; // k!
        for(i=1;i<=k;i++) denominator = (denominator*i) %MOD;

        long long res = modInverse(denominator);
        res = (res*numerator)%MOD;
        return res;
    }



public:
    int threeSumMulti(vector<int>& arr, int target) {
        int n = arr.size(); // 3 <= arr.length <= 3000

        // 0 <= arr[i] <= 100
        // arr[i] + arr[j] + arr[k] == target
        // i < j < k
        //    let x = arr[i]+arr[j], then we will have to ask the question:
        //    how many times does x occur in range [k,n-1] inclusive
        //    we can acummulate so that we can have a 2D array x,k
        int mem[101][3000]; memset(mem,0,sizeof mem);
        for(int i = 0; i < n; ++i)
           mem[arr[i]][i] = 1;
        // accumulate
        for(int i = 0; i < 101; ++i)
            for(int j = 2998; j >= 2; --j)
                mem[i][j] += mem[i][j+1];

        int ans = 0;
        int k,x;
        for(int i = 0; i < n-2; ++i) {
            for(int j = i+1; j < n-1; ++j) {

                k = j+1;
                x = target-(arr[i]+arr[j]);
                if( x < 0 ) continue;

                // how many times does x exist in range [k,n-1] inclusive?
                // 0 <= target <= 300
                // with that, x in the range of 0-300
                if( x > 100 ) continue;

                ans = (ans + mem[x][k]) % MOD;

            }
        }

        return ans;
    }
};
