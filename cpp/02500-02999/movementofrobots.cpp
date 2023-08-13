
// 2731. Movement of Robots
// https://leetcode.com/problems/movement-of-robots/





class Solution {
public:
    int sumDistance(vector<int>& nums, string s, int d) {
        // from the hints:
        //   if you ignore collisions, the resultant positions of robots after d seconds would be the same.

        int n = nums.size();
        vector<long> v(n);
        long mn = LONG_MAX;
        for(int i = 0; i < n; ++i) {
            long t;
            if( s[i] == 'R' ) {
                t = (long)nums[i] + d;
            } else {
                t = (long)nums[i] - d;
            }

            mn = min(mn,t);
            v[i] = t;
        }
        if( mn < 0 ) {
            long offset = mn * (-1);
            for(int i = 0; i < n; ++i)
                v[i] += offset;
        }
        sort(v.begin(),v.end(),greater<long>());

        long mod = 1000000007;

        // observation
        //  the ith element in our reverse sorted list will be
        //  added to the running sum n-i-1 times and
        //  substracted from the running sum i times
        unsigned long long sum = 0;
        for(long i = 0; i < n; ++i) {
            // cout << i << ":" << v[i] << endl;
            // cout << "sum " << sum << " p1 " << (n-i-1) * v[i] << " p2 " << i * v[i] << endl;

            sum = sum + (n-i-1) * v[i] - i * v[i];
        }

        return sum % mod;
    }
};
