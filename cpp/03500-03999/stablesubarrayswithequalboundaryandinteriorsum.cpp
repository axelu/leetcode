
// 3728. Stable Subarrays With Equal Boundary and Interior Sum
// https://leetcode.com/problems/stable-subarrays-with-equal-boundary-and-interior-sum/

class Solution {
public:
    long long countStableSubarrays(vector<int>& capacity) {
        int n = capacity.size(); // 3 <= n <= 1e5
        long long ans = 0LL;

        long long prefixSum = 0LL;

        // map key:   {capacity[i],prefixSum[i+1]}
        // map value: count
        map<pair<int,long long>,long long> mp;

        pair<int,long long> key = {INT_MIN, LLONG_MIN}; // can never be found
        for(int i = 0; i < n; ++i) {

            long long target_prefixSum = prefixSum - (long long)capacity[i];
            pair<int,long long> search_key = {capacity[i], target_prefixSum};
            auto f = mp.find(search_key);
            if( f != mp.end() )
                ans += f->second;


            ++mp[key]; // delayed insert as we never look one back due to length >= 3
            prefixSum += (long long)capacity[i];
            key = {capacity[i], prefixSum};
        }

        return ans;
    }
};





// brute force, not even submitted as it will lead to TLE

class Solution {
public:
    long long countStableSubarrays(vector<int>& capacity) {
        int n = capacity.size(); // 3 <= n <= 1e5
        long long ans = 0LL;

        // brute force, which will lead to TLE

        long long prefixSum[100001];
        prefixSum[0] = 0LL;
        // we could either go by
        //     having seen a given prefixSum OR
        //     having seen same capacity[i] before
        unordered_map<int,vector<int>> um; // key: x; value: list of i where capacity[i] == x
        for(int i = 0; i < n; ++i) {
            prefixSum[i+1] = prefixSum[i] + (long long)capacity[i];
            auto f = um.find(capacity[i]);
            if( f != um.end() ) {
                for(int j = 0; j < f->second.size(); ++ j) {
                    int k = f->second[j];
                    if( k == i-1 ) // length has to be at least 3
                        break;
                    // sum in between
                    long long s = prefixSum[i] - prefixSum[k+1];
                    if( s == capacity[i] )
                        ++ans;
                }
            }
            um[capacity[i]].push_back(i);
        }

        return ans;
    }
};
