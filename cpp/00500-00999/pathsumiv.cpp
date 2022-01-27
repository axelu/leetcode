
// 666. Path Sum IV
// https://leetcode.com/problems/path-sum-iv/






class Solution {
private:
    int ans;

    void dfs(map<array<int,2>,int>& mp, int depth, int pos, int sum) {
        int val = mp[{depth,pos}];

        sum += val;

        int t = (pos-1)*2;
        int l = t+1; // position of left child
        int r = t+2; // position of right child

        if( mp.find({depth+1,l}) == mp.end() && mp.find({depth+1,r}) == mp.end() ) {
            // leaf
            ans += sum;
        }

        // left
        if( mp.find({depth+1,l}) != mp.end() )
            dfs(mp,depth+1,l,sum);
        // right
        if( mp.find({depth+1,r}) != mp.end() )
            dfs(mp,depth+1,r,sum);


        // backtrack
        sum -= val;
    }

    array<int,3> int2digits(int x) {
        array<int,3> ret;
        ret[0] = x / 100;
        int rem = x % 100;
        ret[1] = rem / 10;
        ret[2] = rem % 10;

        return ret;
    }

public:
    int pathSum(vector<int>& nums) {
        int n = nums.size(); // 1 <= nums.length <= 15

        map<array<int,2>,int> mp; // key:depth,position value:val
        array<int,3> t;
        for(int i = 0; i < n; ++i) {
            t = int2digits(nums[i]);
            mp[{t[0],t[1]}] = t[2];
        }

        ans = 0;
        int sum = 0;
        dfs(mp,1,1,sum);

        return ans;
    }
};
