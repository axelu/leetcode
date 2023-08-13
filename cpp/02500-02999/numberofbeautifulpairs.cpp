
// 2748. Number of Beautiful Pairs
// https://leetcode.com/problems/number-of-beautiful-pairs/



class Solution {
private:
    // recursive function to return gcd of a and b
    long long gcd(long long int a, long long int b) {
        if( b == 0 )
            return a;
        return gcd(b,a % b);
    }

public:
    int countBeautifulPairs(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return 0;

        int ans = 0;

        for(int i = 0; i < n-1; ++i) {
            int di = to_string(nums[i])[0]-'0';
            for(int j = i+1; j < n; ++j) {
                int dj = to_string(nums[j]).back()-'0';
                // cout << "i " << i << " j " << j << " di " << di << " dj " << dj << endl;
                if( gcd(di,dj) == 1 )
                    ++ans;
            }
        }

        return ans;
    }
};
