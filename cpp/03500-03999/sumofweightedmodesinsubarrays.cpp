
// 3672. Sum of Weighted Modes in Subarrays
// https://leetcode.com/problems/sum-of-weighted-modes-in-subarrays/




class Solution {
public:
    long long modeWeight(vector<int>& nums, int k) {
        int n = nums.size(); // 1 <= n <= 1e5; 1 <= nums[i] <= 1e5

        int freq[100001];memset(freq,0,sizeof freq);
        map<int,set<int>> mp; // key: freq; value: integers with said frequency

        long long ans = 0;

        // sliding window
        int i = 0;                   // left index
        for(int j = 0; j < n; ++j) { // right index
            int x = nums[j];
            int curr_freq_x = freq[x];
            if( curr_freq_x > 0 ) {
                mp[curr_freq_x].erase(x);
                if( mp[curr_freq_x].empty() )
                    mp.erase(curr_freq_x);
            }
            int new_freq_x = curr_freq_x + 1;
            mp[new_freq_x].insert(x);
            ++freq[x];

            if( j-i+1 == k ) {
                // cout << "i " << i << " j " << j << endl;

                // mode: element with the highest frequency.
                // If multiple choices for mode, the smallest is taken.
                int highest_freq = mp.rbegin()->first;
                int mode = *(mp[highest_freq].begin());
                long long weight = (long long)mode * (long long)highest_freq;

                // cout << "  mode " << mode << " freq " << highest_freq << " weight " << weight << endl;

                ans += weight;

                int y = nums[i];
                int curr_freq_y = freq[y];
                mp[curr_freq_y].erase(y); // guaranteed to be in there
                if( mp[curr_freq_y].empty() )
                    mp.erase(curr_freq_y);
                int new_freq_y = curr_freq_y - 1;
                if( new_freq_y > 0 )
                    mp[new_freq_y].insert(y);
                --freq[y];
                ++i;
            }
        }

        return ans;
    }
};
