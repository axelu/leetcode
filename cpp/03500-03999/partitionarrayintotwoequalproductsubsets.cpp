
// 3566. Partition Array into Two Equal Product Subsets
// https://leetcode.com/problems/partition-array-into-two-equal-product-subsets/





class Solution {
private:
    bool rec(vector<int>& nums, int n, int pos, unsigned long long p0, unsigned long long p1, unsigned long long target) {
        if( pos == n ) {
            return p0 == p1 && p0 == target;
        }

        // we have a choice
        //    use nums[pos] for p0 OR
        //    use nums[pos] for p1

        unsigned long long p0_new = (unsigned long long)nums[pos] * (p0 == 0 ? 1LL : p0);
        if( rec(nums, n, pos+1, p0_new, p1, target) )
            return true;

        unsigned long long p1_new = (unsigned long long)nums[pos] * (p1 == 0 ? 1LL : p1);
        return rec(nums, n, pos+1, p0, p1_new, target);
    }
public:
    bool checkEqualPartitions(vector<int>& nums, long long target) {
        int n = nums.size();
        return rec(nums, n, 0, 0ULL, 0ULL, target);
    }
};
