
// 1093. Statistics from a Large Sample
// https://leetcode.com/problems/statistics-from-a-large-sample/





class Solution {
public:
    vector<double> sampleStats(vector<int>& count) {
        // ans[0] = minimum
        // ans[1] = maximum
        // ans[2] = mean
        // ans[3] = median
        // ans[4] = mode: number that appears the most in the sample. It is guaranteed to be unique.

        vector<double> ans(5);

        int minimum = -1;
        int maximum;
        int mx_count = 0;
        int mode;

        int total_cnt = 0;
        double sum = 0; // it is guaranteed that sum(count) <= 10^9

        map<int,pair<int,int>> mp; // val, range[s,e]

        for(int i = 0; i < 256; ++i) {
            if( count[i] > 0 ) {

                if( minimum == -1 )
                    minimum = i;

                maximum = i;

                if( count[i] > mx_count ) {
                    mx_count = count[i];
                    mode = i;
                }

                sum += (long)count[i] * i;
                mp[i] = {total_cnt, total_cnt + count[i] - 1};
                total_cnt += count[i];
            }
        }
        // calculate mean
        double mean = sum / total_cnt;

        // calculate median
        double median;
        if( total_cnt % 2L ) {
            int median_pos = total_cnt / 2;
            for(auto it = mp.begin(); it != mp.end(); ++it) {
                if( it->second.first <= median_pos && it->second.second >= median_pos ) {
                    median = it->first;
                    break;
                }
            }
        } else {
            int median_pos = total_cnt / 2;
            double median1, median2;
            for(auto it = mp.begin(); it != mp.end(); ++it) {
                if( it->second.first <= median_pos-1 && it->second.second >= median_pos-1 ) {
                    median1 = it->first;
                }
                if( it->second.first <= median_pos && it->second.second >= median_pos ) {
                    median2 = it->first;
                    break;
                }
            }
            median = (median1+median2)/2;
        }

        ans[0] = minimum;
        ans[1] = maximum;
        ans[2] = mean;
        ans[3] = median;
        ans[4] = mode;

        return ans;
    }
};
