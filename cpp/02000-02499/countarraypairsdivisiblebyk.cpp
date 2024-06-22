
// 2183. Count Array Pairs Divisible by K
// https://leetcode.com/problems/count-array-pairs-divisible-by-k/





vector<int> multiples[100001];
bool init = false;

class Solution {
private:
    // greatest common denominator
    int gcd(int a, int b) {
        if (a == 0)
            return b;
        return gcd(b % a, a);
    }

public:
    long long countPairs(vector<int>& nums, int k) {
        if( !init ) {
            init = true;
            for(int a = 100000; a > 0; --a) {
                int square_root = (int) sqrt(a) + 1;
                for(int i = 1; i < square_root; ++i) {
                    if( a % i == 0 && i*i!= a ) {
                        multiples[a].push_back(i);
                        multiples[a].push_back(a/i);
                    }
                    if( a % i == 0 && i*i== a )
                        multiples[a].push_back(i);
                }
            }
        }

        int n = nums.size();
        if( n == 1 )
            return 0;
        if( k == 1 )
            return (long long)n * (n-1)/2LL;

        long long ans = 0;

        // constraint given in problem:
        // 1 <= nums[i] <= 100000
        const int MAX_NUMS = 100000;

        long long cnt[MAX_NUMS+1];memset(cnt,0,sizeof cnt);
        for(int t: multiples[nums[n-1]])
            ++cnt[t];
        for(int i = n-2; i >= 0; --i) {
            int multiplier = k / gcd(k, nums[i]);
            ans += cnt[multiplier];
            /*
            for(int t = multiplier; t <= MAX_NUMS; t += multiplier)
                ans += cnt[t];
            ++cnt[nums[i]];
            */
            for(int t: multiples[nums[i]])
                ++cnt[t];
        }

        return ans;
    }
};
