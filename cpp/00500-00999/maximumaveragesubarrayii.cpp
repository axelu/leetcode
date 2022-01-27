
// 644. Maximum Average Subarray II
// https://leetcode.com/problems/maximum-average-subarray-ii/



// solution approach #2
class Solution {
private:
    int n;

    bool check(vector<int>& nums, double mid, int k){
        double sum = 0;
        double prev_sum = 0;
        double min_sum = 0;
        for(int i = 0; i < n; ++i) {
            sum += nums[i] - mid;
            if( i >= k) {
                prev_sum += nums[i-k] - mid;
                min_sum = min(prev_sum,min_sum);
            }
            if( i >= k-1 && sum > min_sum ) return false;
        }
        return true;
    }

public:
    double findMaxAverage(vector<int>& nums, int k) {
        if( k == 1 )
            return (double)*max_element(nums.begin(),nums.end());
        n = nums.size();
        if( k == n )
            return (double)accumulate(nums.begin(),nums.end(),0)/k;

        double s = INT_MAX;
        double e = INT_MIN;

        for(int i = 0; i < n; ++i) {
            e = max(e,double(nums[i]));
            s = min(s,double(nums[i]));
        }

        double mid;
        while(s + 0.00001 < e) {
            mid = s + (e - s)/2;
            if( check(nums,mid,k) ) e = mid;
            else s = mid;
        }
        return s;
    }
};
