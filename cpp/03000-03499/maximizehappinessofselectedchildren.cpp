
// 3075. Maximize Happiness of Selected Children
// https://leetcode.com/problems/maximize-happiness-of-selected-children/





class Solution {
public:
    long long maximumHappinessSum(vector<int>& happiness, int k) {
        int n = happiness.size();

        sort(happiness.begin(),happiness.end(),greater<int>());
        long long sum = 0LL;
        long long decr = 0LL;

        for(int i = 0; i < k; ++i) {
            // cout << "i " << i << " happiness[i] " << happiness[i] << " decr " << decr << endl;
            if( happiness[i] - decr <= 0 )
                break;
            sum += (long long)happiness[i] - decr;
            ++decr;
        }

        return sum;
    }
};
