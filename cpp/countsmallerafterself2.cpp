
// 315. Count of Smaller Numbers After Self
// https://leetcode.com/problems/count-of-smaller-numbers-after-self/
// day 26 June 2021 challenge
// https://leetcode.com/explore/challenge/card/june-leetcoding-challenge-2021/606/week-4-june-22nd-june-28th/3792/




class Solution {
private:
    // Binary Indexed Tree BIT
    int t[20002];
    int l = 20002;

    void update(int x, int val) {
        // initialize the current index as x+1
        int i = x+1;
        while( i < l ) {
            // add the val to BITree[index]
            t[i] += val;
            // go to parent
            // parent obtained by incrementing the last set bit of the current index
            i = i + (i & (-i));
        }
    }

    int get(int i) {
        int ret = 0;
        while( i > 0 ) {
            ret += t[i];
            i = i - (i & (-i));
        }
        return ret;
    }

public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        if( n == 0 ) return {};
        if( n == 1 ) return {0};

        vector<int> ans(n,0);


        memset(t,0,sizeof t);
        update(nums[n-1]+10000,1);
        for(int i = n - 2; i >= 0; --i) {
            ans[i] = get(nums[i]+10000);
            update(nums[i]+10000,1);
        }


        return ans;
    }

};
