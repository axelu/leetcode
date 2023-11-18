
// 548. Split Array with Equal Sum
// https://leetcode.com/problems/split-array-with-equal-sum/





class Solution {
private:
    unordered_set<long> us;

    bool rec(vector<int>& nums, int n, long i, long sum, long k, int prefixSum[]) {
        // cout << "rec i " << i << " sum " << sum << " k " << k << endl;
        if( k == 1 )
            return prefixSum[n] - prefixSum[i] == sum;

        long key = (k<<44) + (i<<12) + sum;
        if( us.find(key) != us.end() )
            return false;

        // calculate max end index jmx of subarray
        int jmx;
        if( k == 3 )
            jmx = n-1-4;
        else // k == 2
            jmx = n-1-2;

        for(int j = i; j <= jmx; ++j) {
            if( prefixSum[j+1] - prefixSum[i] != sum )
                continue;

            if( k == 1 || rec(nums,n,j+2,sum,k-1,prefixSum) )
                return true;
        }

        us.insert(key);
        return false;
    }
public:
    bool splitArray(vector<int>& nums) {
        int n = nums.size(); // 1 <= n <= 2000
        if( n < 7 )
            return false;


        // minimum nums size
        //     0     1      2      3      4      5      6
        // _________ _ ___________ _ ___________ _ ___________
        // [0...i-1] i [i+1...j-1] j [j+1...k-1] k [k+1...n-1]

        // brute force
        int prefixSum[n+1];
        prefixSum[0] = 0;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + nums[i-1];

        /*
        // debug
        for(int i = 0; i <= n; ++i)
            cout << i << ":" << prefixSum[i] << " ";
        cout << endl;
        */

        for(int j = 0; j <= n-1-6; ++j)
            if( rec(nums,n,j+2,prefixSum[j+1],3,prefixSum) )
                return true;

        return false;
    }
};
