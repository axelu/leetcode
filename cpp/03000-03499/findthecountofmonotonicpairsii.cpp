
// 3251. Find the Count of Monotonic Pairs II
// https://leetcode.com/problems/find-the-count-of-monotonic-pairs-ii/







class Solution {
private:
    const long mod = 1000000007;

public:
    int countOfPairs(vector<int>& nums) {
        int n = nums.size(); // 1 <= n <= 2000; 1 <= nums[i] <= 50
        if( n == 1 )
            return nums[0] + 1;

        int arr1_max[n];
        int arr1_min[n];

        int arr2_max[n];
        int arr2_min[n];

        // pass 1
        // arr1_max from right to left
        arr1_max[n-1] = nums[n-1];
        for(int i = n-2; i >= 0; --i)
            arr1_max[i] = min(arr1_max[i+1], nums[i]);
        // with that we can determine an initial min value for arr2 -> arr2_min
        arr2_min[n-1] = 0;
        for(int i = n-2; i >= 0; --i)
            arr2_min[i] = max(nums[i] - arr1_max[i], arr2_min[i+1]);
        // we need to go back to arr1_max again and adjust it
        for(int i = n-2; i >= 0; --i) {
            int t = nums[i] - arr2_min[i];
            arr1_max[i] = min(arr1_max[i+1], t);
        }

        //
        // arr2_max from left to right
        arr2_max[0] = nums[0];
        for(int i = 1; i < n; ++i)
            arr2_max[i] = min(arr2_max[i-1], nums[i]);
        // with that we can determine an initial min value for arr1 -> arr1_min
        arr1_min[0] = 0;
        for(int i = 1; i < n; ++i)
            arr1_min[i] = max(arr1_min[i-1], nums[i] - arr2_max[i]);
        // we need to go back to arr2_max again and adjust it
        for(int i = 1; i < n; ++i) {
            int t = nums[i] - arr1_min[i];
            arr2_max[i] = min(arr2_max[i-1], t);
        }

/*
        for(int i = 0; i < n; ++i)
            cout << arr1_min[i] << " ";
        cout << endl;
         for(int i = 0; i < n; ++i)
            cout << arr1_max[i] << " ";
        cout << endl;
        for(int i = 0; i < n; ++i)
            cout << arr2_min[i] << " ";
        cout << endl;
        for(int i = 0; i < n; ++i)
            cout << arr2_max[i] << " ";
        cout << endl;
*/

        long _pre[1002];memset(_pre,0,sizeof _pre);
        long * pre = _pre;
        long _cur[1002];memset(_cur,0,sizeof _cur);
        long * cur = _cur;
        for(int i = arr1_min[n-1]; i <= arr1_max[n-1]; ++i)
            pre[i] = 1L;

/*
        cout << "i = " << n-1 << endl; cout << "    ";
        cout << " pre ";
        for(int k = 0; k <= 3; ++k)
            cout << k << ":" << pre[k] << " ";
        cout << endl;
*/
        for(int i = n-2; i >= 0; --i) {
/*
            cout << "i = " << i << endl;
            cout << "before" << endl;
            cout << "    ";
            cout << " pre ";
            for(int k = 0; k <= 3; ++k)
                cout << k << ":" << pre[k] << " ";
            cout << endl;
            cout << "    ";
            cout << " cur ";
            for(int k = 0; k <= 3; ++k)
                cout << k << ":" << cur[k] << " ";
            cout << endl;
*/

            // prefixSum of pre
            long prefixSum[1003];
            prefixSum[0] = 0L;
            for(int k = 1; k < 1002; ++k)
                prefixSum[k] = (prefixSum[k-1] + pre[k-1]) % mod;



            for(int val1 = arr1_max[i]; val1 >= arr1_min[i]; --val1) {
                int val2 = nums[i] - val1;

                int k = max({val1, arr1_min[i+1], nums[i+1] - val2});
                // for(; k <= arr1_max[i+1]; ++k)
                //    cur[val1] = (cur[val1] + pre[k]) % mod;

                long t = prefixSum[arr1_max[i+1]+1] - prefixSum[k];
                if( t < 0L )
                    t += mod;

                // cur[val1] = (cur[val1] + (prefixSum[arr1_max[i+1]+1] - prefixSum[k])) % mod;
                cur[val1] = (cur[val1] + t) % mod;

            }

/*
            cout << "after" << endl;
            cout << "    ";
            cout << " pre ";
            for(int k = 0; k <= 3; ++k)
                cout << k << ":" << pre[k] << " ";
            cout << endl;
            cout << "    ";
            cout << " cur ";
            for(int k = 0; k <= 3; ++k)
                cout << k << ":" << cur[k] << " ";
            cout << endl;
*/

            long * t = pre;
            pre = cur;
            cur = t;
            for(int j = 0; j < 1002; ++j)
                cur[j] = 0L;
        }

        long ans = 0L;
        for(int i = 0; i < 1002; ++i)
            ans = (ans + pre[i]) % mod;

        return ans;
    }
};
