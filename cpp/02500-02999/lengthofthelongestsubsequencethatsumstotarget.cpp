
// 2915. Length of the Longest Subsequence That Sums to Target
// https://leetcode.com/problems/length-of-the-longest-subsequence-that-sums-to-target/




/* alternative idea
 * sort nums asc
 * we only need to investigate nums up to nums[i] <= target
 * example nums = {1,1,1,3,4,12}, target = 13
 *    let current running sum be sum[0,5]
 *    let prev running sum be sum[0,4]
 *    if current running sum > target and current running sum - prev running sum < target, then
 *      no point in reducing the prev running sum to hit target
 * going through nums left to right and keeping a running sum
 *    if running sum is less than target and there is no more element -> no solution
 *    if running sum is less than target and the next element is greater than target -> no solution
 *    if running sum is less than target and the next element is equal target -> ans = 1
 *    if running sum + next == target, then that is the longest subsequence
 *    if running sum + next > target, the what?
 * example nums = {1,1,1,3,4,6}, target = 13
 *    ans = 5, longest subsequence = {1,1,1,4,6}
 * if we are over, then we need to find the shortest subsequence equalling the amount we are over
 */
class Solution {
private:
    int mem[1000][1001];

    int rec(vector<int>& nums, int n, int pos, int target) {
        if( target == 0 )
            return 0;

        if( pos == n && target != 0 )
            return -100000;

        if( mem[pos][target] != -200000 )
            return mem[pos][target];

        // we have a choice
        //    don't use the current element OR
        //    use the current element if less or equal target

        int ret = rec(nums,n,pos+1,target);

        if( nums[pos] <= target )
            ret = max(ret, 1 + rec(nums,n,pos+1,target-nums[pos]));

        return mem[pos][target] = ret;
    }



public:
    int lengthOfLongestSubsequence(vector<int>& nums, int target) {
        int n = nums.size();

        for(int i = 0; i < n; ++i)
            for(int j = 0; j <= target; ++j)
                mem[i][j] = -200000;

        int ans = rec(nums,n,0,target);
        return ans > 0 ? ans : -1;
    }
};
