
// 2035. Partition Array Into Two Arrays to Minimize Sum Difference
// https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/

class Solution {
private:
    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

    int solve(int half1sum, set<int> half2[], int n, int i, int target) {
        int diff = INT_MAX;
        int res;
        auto lb = half2[n-i].lower_bound(target-half1sum);
        if( lb != half2[n-i].end() ) {
            if( half1sum + *lb == target ) {
                res = target;
                return res;
            } else {

                int t = abs(half1sum + *lb - target);
                if( diff > t ) {
                    res = half1sum + *lb;
                    diff = t;
                }
                if( lb != half2[n-i].begin() ) {
                    t = abs(half1sum + *prev(lb) - target);
                    if( diff > t ) {
                        res = half1sum + *prev(lb);
                        diff = t;
                    }
                }
            }
        } else {
            int t = abs( (half1sum + *prev(half2[n-i].end())) - target );
            if( diff > t ) {
                res = half1sum + *prev(half2[n-i].end());
                diff = t;
            } 
        }
        return res;
    }
       
public:
    int minimumDifference(vector<int>& nums) {
        int n = nums.size()/2;  // 1 <= n <= 15, nums.length == 2 * n
                                // -10^7 <= nums[i] <= 10^7
        
        int sum = accumulate(nums.begin(),nums.end(),0);
        int target = sum/2;
        
        set<int> half2[n+1]; // store all possible sum values if k elements from this half are added
        half2[0] = {0};
        int bits = (2*n-1)-n;  // e-s
        int setBits,t;
        for(int i = 1; i < pow(2,((2*n-1)-n)+1); ++i) {
            t = 0;
            setBits = countSetBits(i);
            for(int k = bits; k >= 0; --k) {
                if( i & (1 << k) ) 
                    t += nums[n+k];
            }
            half2[setBits].insert(t);
        }

        int ans = INT_MAX;
        bits = n-1; // e-s
        for(int i = 0; i < pow(2,n); ++i) {
            t = 0;
            setBits = countSetBits(i);
            for(int k = bits; k >= 0; --k) {
                if( i & (1 << k) ) 
                    t += nums[k];
            }
            
            int a = solve(t,half2,n,setBits,target);
            ans = min(ans,abs(a - (sum-a)));
        }
        
        return ans;
    }
};
