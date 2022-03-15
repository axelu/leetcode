
// 2052. Minimum Cost to Separate Sentence Into Rows
// https://leetcode.com/problems/minimum-cost-to-separate-sentence-into-rows/


class Solution {
private:
    int rec(vector<int>& nums, int nums_sz, int pos, int k, int mem[]) {
        if( pos == nums_sz-1 )  // last word will fit on last row
            return 0;           // last row has no cost

        if( mem[pos] != -1 )
            return mem[pos];

        // we have a choice to put one or more words
        // on the current row as long as char count <= k
        // including whitespaces separating words

        int n  = 0;         // chars on current row
        int mn = INT_MAX;   // cost
        for(int i = pos; i < nums_sz; ++i) {
            if( i == pos )
                n += nums[i];
            else
                n += 1 + nums[i]; // +1 for separating whitespace

            if( n <= k ) {
                if( i == nums_sz-1 ) {
                    // we fit all words on the 'last' row
                    // last row has no cost
                    mn = 0;
                    break;
                }
                int curr_row_cost = (k-n)*(k-n);
                mn = min(mn, curr_row_cost + rec(nums,nums_sz,i+1,k,mem));
            } else {
                break;
            }
        }

        return mem[pos] = mn;
    }

public:
    int minimumCost(string sentence, int k) {
        vector<int> nums;

        int i = 0;
        for(char c : sentence)
            if( c == ' ' ) {
                nums.push_back(i);
                i = 0;
            } else {
                ++i;
            }
        nums.push_back(i); // finish up

        int nums_sz = nums.size();
        int mem[nums_sz];memset(mem,-1,sizeof mem);
        return rec(nums,nums_sz,0,k,mem);
    }
};
