
// 3299. Sum of Consecutive Subsequences
// https://leetcode.com/problems/sum-of-consecutive-subsequences/






class Solution {
public:
    int getSum(vector<int>& nums) {
        int n = nums.size();

        const long mod = 1000000007;

        long ans = 0L;
        for(int i = 0; i < n; ++i) {
            ans = (ans + nums[i]) % mod;    // don't double count later
        }

        // pass1 increasing

        // 1 <= nums[i] <= 1e5
        vector<int> nxt[100002]; // indicies at which value is key
        pair<long,long> fup[n];  // number of subsequences, sum of subsequences

        // right to left
        for(int i = n-1; i >= 0; --i) {
            long val = nums[i];

            long nbr_subsequences = 0L; // don't add us to it just yet
            long sum_subsequences = 0L; // don't add us to it just yet
            // get continuations
            for(int j = 0; j < nxt[val+1].size(); ++j) {
                nbr_subsequences = (nbr_subsequences + fup[nxt[val+1][j]].first) % mod;
                sum_subsequences = (sum_subsequences + fup[nxt[val+1][j]].second) % mod;
            }

            // we can add ourselfs to all these
            long t = (((val * nbr_subsequences) % mod) + sum_subsequences) % mod;
            ans = (ans + t) % mod;

            // but someone below us can make a subsequence with us AND what we collected
            fup[i] = {(nbr_subsequences+1) % mod, (t+val) % mod};

            nxt[val].push_back(i);
        }

        // pass2 decreasing !!!don't double count

        // we could reuse the structures we used for increasing TODO
        vector<int> dwn[100002]; // indicies at which value is key
        pair<long,long> fdn[n];  // number of subsequences, sum of subsequences

        // right to left
        for(int i = n-1; i >= 0; --i) {
            long val = nums[i];

            long nbr_subsequences = 0L; // don't add us to it just yet
            long sum_subsequences = 0L; // don't add us to it just yet
            // get continuations
            for(int j = 0; j < dwn[val-1].size(); ++j) {
                nbr_subsequences = (nbr_subsequences + fdn[dwn[val-1][j]].first) % mod;
                sum_subsequences = (sum_subsequences + fdn[dwn[val-1][j]].second) % mod;
            }

            // we can add ourselfs to all these
            long t = (((val * nbr_subsequences) % mod) + sum_subsequences) % mod;
            ans = (ans + t) % mod;

            // but someone below us can make a subsequence with us AND what we collected
            fdn[i] = {(nbr_subsequences+1) % mod, (t+val) % mod};

            dwn[val].push_back(i);
        }






        return ans;
    }
};
