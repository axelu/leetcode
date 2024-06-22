
// 3005. Count Elements With Maximum Frequency
// https://leetcode.com/problems/count-elements-with-maximum-frequency/




class Solution {
public:
    int maxFrequencyElements(vector<int>& nums) {
        // 1 <= nums[i] <= 100
        int freq[101];memset(freq,0,sizeof freq);
        for(int x: nums)
            ++freq[x];

        int max_freq = 0;
        int max_freq_occurence = 0;
        for(int i = 0; i <= 100; ++i) {
            int curr_freq = freq[i];
            if( curr_freq > max_freq ) {
                max_freq = freq[i];
                max_freq_occurence = curr_freq;
            } else if( curr_freq == max_freq ) {
                max_freq_occurence += curr_freq;
            }
        }

        return max_freq_occurence;
    }
};
