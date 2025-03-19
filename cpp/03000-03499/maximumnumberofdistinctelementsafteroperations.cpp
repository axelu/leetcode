
// 3397. Maximum Number of Distinct Elements After Operations
// https://leetcode.com/problems/maximum-number-of-distinct-elements-after-operations/





class Solution {
public:
    int maxDistinctElements(vector<int>& nums, int k) {
        int n = nums.size(); // cout << "n " << n << endl;

        // edge case
        if( n == 1 )
            return 1;

        // edge case
        if( n == 2 ) {
            if( k == 0 ) {
                return nums[0] == nums[1] ? 1 : 2;
            } else
                return 2;
        }

        unordered_map<int,int> um;

        // edge case
        if( k == 0 ) {
            for(int i = 0; i < n; ++i)
                ++um[nums[i]];
            return um.size();
        }

        sort(begin(nums),end(nums));


        // make the smaller ones smaller, make the larger one larger - greedy
        // keep track of the largest smaller one and the smallest larger on
        int largest_smaller = nums[0] - k;
        int smallest_larger = nums[n-1] + k;

        // cout << "i 0 nums[i] " << nums[0] << " largest_smaller " << largest_smaller << " j " << n-1 << " nums[j] " << nums[n-1] << " smallest_larger " << smallest_larger << endl;

        int i = 1;
        int j = n-2;
        int uniques = 2;
        while( i < j ) {
            bool largest_smaller_reset = false;
            bool smallest_larger_reset = false;

            largest_smaller = max(largest_smaller+1, nums[i] - k);
            if( largest_smaller > nums[i] + k || largest_smaller == smallest_larger ) {
                // can't do it
                --largest_smaller;
                largest_smaller_reset = true;
            }

            smallest_larger = min(smallest_larger-1, nums[j] + k);
            if( smallest_larger < nums[j] - k || smallest_larger == largest_smaller ) {
                // can't do it
                ++smallest_larger;
                smallest_larger_reset = true;
            }

            // cout << "i " << i << " nums[i] " << nums[i] << " largest_smaller " << largest_smaller << " j " << j << " nums[j] " << nums[j] << " smallest_larger " << smallest_larger << endl;

            if( largest_smaller == smallest_larger )
                break;

            if( largest_smaller_reset && smallest_larger_reset ) {
                // do nothing
            } else if( largest_smaller_reset || smallest_larger_reset ) {
                uniques += 1;
            } else {
                uniques += 2;
            }

            ++i;
            --j;
        }

        /*
        cout << "i " << i << " j " << j << endl;
        cout << "largest_smaller " << largest_smaller << " smallest_larger " << smallest_larger << endl;
        cout << "uniques " << uniques << endl;
        */

        if( largest_smaller == smallest_larger ) {
            ++uniques;
        } else if( i == j ) {
            // we already know largest_smaller < smallest_larger
            /*
            if( largest_smaller != nums[i] && nums[i] != smallest_larger ) {
                ++uniques;
            } else if( smallest_larger - largest_smaller >= 2 ) {
                ++uniques;
            }
            */
            if( smallest_larger - largest_smaller >= 2 )
                ++uniques;
        }

        return uniques;

        /*
        int ans;
        if( largest_smaller == smallest_larger ) {
            ans = n - (j-i+1) + 1;
        } else { // i == j if n == odd or i > j if n == even (i-1 == j)
            if( largest_smaller == nums[i] && nums[i] == smallest_larger )
                ans = n-2;
            else if( largest_smaller == nums[i] || nums[i] == smallest_larger )
                ans = n-1;
            else
                ans = n;
        }

        return ans;
        */
    }
};
