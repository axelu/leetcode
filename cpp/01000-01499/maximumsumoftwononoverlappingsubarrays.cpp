
// 1031. Maximum Sum of Two Non-Overlapping Subarrays
// https://leetcode.com/problems/maximum-sum-of-two-non-overlapping-subarrays/


class Solution {
public:
    int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
        int n = nums.size();
        if( firstLen+secondLen == n )
            return accumulate(nums.begin(),nums.end(),0);

        // left to right
        // store max sum for subarrays of firstLen up to and including index j
        int l2r[n];memset(l2r,0,sizeof l2r);
        int i = 0; // left index
        int j = 0; // right index
        int sum = 0;
        int mx = 0;
        for(; j < n; ++j) {
            sum += nums[j];
            if( j - i + 1 < firstLen )
                continue;
            mx = max(mx,sum);
            l2r[j] = mx;
            sum -= nums[i];
            ++i;
        }

        // right to left
        // store max sum for subarrays of firsLen starting at index ???
        int r2l[n];memset(r2l,0,sizeof r2l);
        i = n-1; // left index
        j = n-1; // right index
        sum = 0;
        mx = 0;
        for(; i >= 0; --i) {
            sum += nums[i];
            if( j - i + 1 < firstLen )
                continue;
            mx = max(mx,sum);
            r2l[i] = mx;
            sum -= nums[j];
            --j;
        }

        // final path
        i = 0; // left index
        j = 0; // right index
        sum = 0;
        mx = 0;
        int l,r;
        for(; j < n; ++j) {
            sum += nums[j];
            if( j - i + 1 < secondLen )
                continue;

            // sum + max to the left
            l = i > 0 ? l2r[i-1]+sum : sum;
            // sum + max to the right
            r = j < n-1 ? r2l[j+1]+sum : sum;

            mx = max({mx,l,r});

            sum -= nums[i];
            ++i;
        }

        return mx;
    }
};
