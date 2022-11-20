
// 2163. Minimum Difference in Sums After Removal of Elements
// https://leetcode.com/problems/minimum-difference-in-sums-after-removal-of-elements/



class Solution {
public:
    long long minimumDifference(vector<int>& nums) {
        int n = nums.size(); // n is a multiple of 3

        // we need to optimize sumfirst to be minimum and
        // sumsecond to be maximum

        // sumsecond
        // from right to left
        // chose exactly n/3 elements in range [n/3,n-1] inclusive whose sum is maximum
        // max sum of a subsequence of n/3 elements starting at index i
        long long sumsecond[n-n/3+1];
        long long t = 0;
        priority_queue<int,vector<int>,greater<int>> mn_heap;
        for(int i = n-1; i >= n - n/3; --i) {
            mn_heap.push(nums[i]);
            t = t + nums[i];
        }
        sumsecond[n-n/3] = t;
        for(int i = n - n/3 - 1; i >= n/3; --i)
            if( nums[i] > mn_heap.top() ) {
                sumsecond[i] = sumsecond[i+1] - mn_heap.top() + nums[i];
                mn_heap.pop();
                mn_heap.push(nums[i]);
            } else {
                sumsecond[i] = sumsecond[i+1];
            }

        /*
        // debug
        cout << "sumsecond" << endl;
        for(int i = n/3; i <= n-n/3; ++i)
            cout << i << ":" << sumsecond[i] << " ";
        cout << endl;
        */

        // sumfirst
        // from left to right
        // chose exactly n/3 elements in range[0,n-n/3-1] inclusive whose sum is minimum
        // min sum of a subsequence of n/3 elements ending at index i
        long long sumfirst[n-n/3];
        t = 0;
        priority_queue<int> mx_heap;
        for(int i = 0; i < n/3; ++i) {
            mx_heap.push(nums[i]);
            t = t + nums[i];
        }
        sumfirst[n/3-1] = t;
        for(int i = n/3; i < n-n/3; ++i)
            if( nums[i] < mx_heap.top() ) {
                sumfirst[i] = sumfirst[i-1] - mx_heap.top() + nums[i];
                mx_heap.pop();
                mx_heap.push(nums[i]);
            } else {
                sumfirst[i] = sumfirst[i-1];
            }

        /*
        cout << "sumfirst" << endl;
        for(int i = n/3-1; i < n-n/3; ++i)
            cout << i << ":" << sumfirst[i] << " ";
        cout << endl;
        */

        long long ans = LLONG_MAX;
        for(int i = n/3-1; i < n-n/3; ++i)
            ans = min(ans,sumfirst[i]-sumsecond[i+1]);

        return ans;
    }
};
