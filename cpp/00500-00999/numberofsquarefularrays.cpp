
// 996. Number of Squareful Arrays
// https://leetcode.com/problems/number-of-squareful-arrays/



class Solution {
private:
    int n;
    int * _nums;
    int end;
    int g[12][12];
    int seen[12][4096];

    int rec(int pos, int mask) {
        // when we come to pos, we already checked
        // that from where we come here makes sum with
        // nums[pos] that is a square

        if( seen[pos][mask] != -1 )
            return seen[pos][mask];

        int ret = 0;

        mask |= 1 << pos;
        if( mask == end ) {
            ret = 1;
        } else {
            unordered_set<int> seen; // don't connect from us to a dup
            for(int i = 0; i < n; ++i) {
                if( i == pos )
                    continue;
                if( (mask >> i) & 1 )
                    continue;
                if( !g[pos][i] )
                    continue;
                if( !seen.insert(_nums[i]).second )
                    continue;

                ret += rec(i,mask);
            }
        }
        // backtrack
        mask &= ~(1 << pos);

        return seen[pos][mask] = ret;
    }


public:
    int numSquarefulPerms(vector<int>& nums) {
        n = nums.size();
        memset(g,0,sizeof g);

        sort(nums.begin(),nums.end());

        int vidx = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = i+1; j < n; ++j) {
                int t = nums[i] + nums[j];
                int rt = sqrt(t);
                if( rt * rt == t ) {
                    if( nums[i] == nums[j] ) {
                        if( i+1 == j ) {
                            g[i][j] = 1;
                        }
                    } else {
                        g[i][j] = 1;
                        g[j][i] = 1;
                    }
                }
            }
        }

        int ans = 0;

        end = pow(2,n)-1;
        memset(seen,-1,sizeof seen);
        _nums = nums.data();
        int pre = -1;
        for(int i = 0; i < n; ++i)
            if( nums[i] != pre ) {
                int t = rec(i,0);
                ans += t;
                pre = nums[i];
            }

        return ans;
    }
};
