
// 2121. Intervals Between Identical Elements
// https://leetcode.com/problems/intervals-between-identical-elements/




class Solution {
public:
    vector<long long> getDistances(vector<int>& arr) {
        int n = arr.size();

        unordered_map<int,vector<long long>> um; // val, list of indicies
        for(int i = 0; i < n; ++i)
            um[arr[i]].push_back(i);

        vector<long long> ans(n);
        for(auto it = um.begin(); it != um.end(); ++it) {

            // the 1st occurence of this val
            // the sum of intervals is the prefix sum
            // but we need to compensate for the offset based on
            // at what index the number occurs first and how many of it there are
            int k = it->second.size();
            long long s = accumulate(it->second.begin(),it->second.end(),0LL) - k * it->second[0];
            ans[it->second[0]] = s;

            // now when we move through the indicies,
            //   subtract the distance we are moving times number of occurences to the right
            //   add the distance we are moving times number of occurences to the left
            for(int i = 1; i < k; ++i) {

                // distance we are moving
                long long d = it->second[i] - it->second[i-1];

                // number of occurence to the right including i
                long long r = k - i;
                // number of occurence to the left including i
                long long l = i;

                s = s - r * d + l * d;

                ans[it->second[i]] = s;
            }
        }

        return ans;
    }
};
