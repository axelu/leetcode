
// 1862. Sum of Floored Pairs
// https://leetcode.com/problems/sum-of-floored-pairs/

class Solution {
private:
    long mod = 1000000007;

    // binary search greatest element less than target or equal target
    int _greatest_element_less_than_target_or_equal_target(vector<array<int,2>>& nums, int s, int target ) {
        int n = nums.size();
        // returns n-1 if nums[n-1] < target
        // returns s-1 if nums[s] > target
        //int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( nums[mid][0] >= target )
                e = mid;
            else
                s = mid+1;
        }
        if( (s < n && nums[s][0] > target) || s == n )
            --s;

        return s;
    }

public:
    int sumOfFlooredPairs(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return 1;

        // build a map by value and frequency of value
        sort(nums.begin(),nums.end());
        vector<array<int,2>> mp; // value,count (could use map)
        int pre = nums[0];
        int cnt = 1;
        for(int i = 1; i < n; ++i)
            if( nums[i] != pre ) {
                mp.push_back({pre,cnt});
                pre = nums[i];
                cnt = 1;
            } else
                ++cnt;
        mp.push_back({pre,cnt});

        long ans = n; // each number divided by itself = 1

        // build prefixSum of counts
        int mp_sz = mp.size(); // cout << mp_sz << endl;
        long prefixSum[mp_sz+1];
        prefixSum[0] = 0;
        for(int i = 1; i <= mp_sz; ++i) {
            prefixSum[i] = prefixSum[i-1] + mp[i-1][1];

            // each number occuring more than ones makes two times
            // f * (f-1)/2 pairs with division result 1 with f being the frequency
            // two times because forwards AND backwards
            long f = mp[i-1][1];
            ans += ((f * (f-1)/2) * 2) % mod;
        }

        /*
        for(int i = 0; i <= mp_sz; ++i)
            cout << prefixSum[i] << " ";
        cout << endl;
        */

        for(int i = 0; i < mp_sz-1; ++i) {
            // cout << "i " << i << " mp[i][0] " << mp[i][0] << endl;
            int s = i+1; // start initial search at next index

            for(int j = 2; j < 100002; ++j) { // 1 <= nums[i] <= 10^5
                int target = mp[i][0] * j - 1;
                // cout << "j " << j << endl;
                // determine the number of elements less or equal target
                // starting at current idx+1 and mp_sz

                // cout << "search starting at idx " << s << " target " << target << endl;
                int t = _greatest_element_less_than_target_or_equal_target(mp,s,target);
                // returns mp_sz-1 if mp[mp_sz-1] < target
                // returns s-1 if mp[s] > target
                // cout << "t " << t << endl;
                ans = (ans + ((prefixSum[t+1] - prefixSum[s]) * (j-1)) * mp[i][1]) % mod;

                s = t+1; // start the next search at next index of our current result
                if( s == mp_sz )
                    break;
            }
        }

        return ans;
    }
};
