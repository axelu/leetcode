
// 2786. Visit Array Positions to Maximize Score
// https://leetcode.com/problems/visit-array-positions-to-maximize-score/




class Solution {
private:
    long long rec(vector<int>& nums, int n, int i, int same[], int different[], int x, long long mem[]) {
        if( i == n )
            return 0LL;

        if( mem[i] != -1 )
            return mem[i];

        long long a = nums[i] + rec(nums,n,same[i],same,different,x,mem);
        long long b = nums[i] + rec(nums,n,different[i],same,different,x,mem) - x;

        return mem[i] = max(a,b);
    }
public:
    long long maxScore(vector<int>& nums, int x) {
        int n = nums.size();

        // as all elements in nums are positive,
        // it is always most beneficial to go to next one w/ same parity OR
        // if there is a gap, to the next one (which will have different parity)

        int same[n];
        same[n-1] = n;
        int different[n];
        different[n-1] = n;

        int next_parity = nums[n-1] % 2;
        for(int i = n-2; i >= 0; --i) {
            int curr_parity = nums[i] % 2;
            if( curr_parity == 0 && next_parity == 0 ) {
                same[i] = i+1;
                different[i] = different[i+1];

            } else if( curr_parity == 0 && next_parity == 1 ) {
                same[i] = different[i+1];
                different[i] = i+1;

            } else if( curr_parity == 1 && next_parity == 0 ) {
                same[i] = different[i+1];
                different[i] = i+1;

            } else { // curr_parity == 1 && next_parity == 1
                same[i] = i+1;
                different[i] = different[i+1];

            }
            next_parity = curr_parity;
        }

        long long mem[n];memset(mem,-1,sizeof mem);
        return rec(nums,n,0,same,different,x,mem);
    }
};
