
// 2354. Number of Excellent Pairs
// https://leetcode.com/problems/number-of-excellent-pairs/



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

    // binary search lower bound
    int lb(vector<int>& nums, int n, int target) {
        // returns 'n' if target greater than greatest element
        // returns  0  if target less or equal than smallest element
        // binary search lower bound while loop
        // lower bound -> equal or greater than target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target <= nums[mid] )
                e = mid;
            else
                s = mid+1;
        }
        if( s < n && nums[s] < target )
            ++s;

        return s;
    }

public:
    long long countExcellentPairs(vector<int>& nums, int k) {
        // from the hints:
        // the sum of the number of set bits in (num1 OR num2) and (num1 AND num2)
        // is equal to the sum of the number of set bits in num1 and num2.

        unordered_set<int> us;
        vector<int> bitcounts;
        for(int x: nums) {
            if( us.insert(x).second )
                bitcounts.push_back(countSetBits(x));
        }
        sort(bitcounts.begin(),bitcounts.end());
        long long n = bitcounts.size();

        long long ans = 0LL;
        for(auto it = us.begin(); it != us.end(); ++it) {
            int t = countSetBits(*it);
            if( t >= k ) {
                ans += n;
                continue;
            }
            // min number of setbits that the other num needs to have to make an excellent pair
            int d = k-t;

            int s = lb(bitcounts,n,d);
            if( s == n )
                continue;

            long long l = n - s;
            // if our current number is part of what we found
            // the number of pairs will include it
            // if not, then we actually have a length of our current number plus what we found
            //if( t < d )
            //    ++l;
            ans += l;
        }

        return ans;
    }
};
