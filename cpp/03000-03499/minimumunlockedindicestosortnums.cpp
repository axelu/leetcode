
// 3431. Minimum Unlocked Indices to Sort Nums
// https://leetcode.com/problems/minimum-unlocked-indices-to-sort-nums/


class Solution {
public:
    int minUnlockedIndices(vector<int>& nums, vector<int>& locked) {
        int n = nums.size(); // nums.size() == locked.size()
        if( n == 1 )
            return 0;

        int firstone = -1, lastone = -1;
        int firsttwo = -1, lasttwo = -1;
        int firstthree = -1, lastthree = -1;
        int cnt[4]; memset(cnt,0,sizeof cnt);
        for(int i = 0; i < n; ++i) {
            if( nums[i] == 1 ) {
                ++cnt[1];
                if( firstone == -1 )
                    firstone = i;
                lastone = i;
            } else if( nums[i] == 2 ) {
                ++cnt[2];
                if( firsttwo == -1 )
                    firsttwo = i;
                lasttwo = i;
            } else { // nums[i] == 3
                ++cnt[3];
                if( firstthree == -1 )
                    firstthree = i;
                lastthree = i;
            }
        }
        // lastone  lastthree
        //    -1       -1      nums only contains 2s, it is already sorted
        //    -1      pos      solvable (if no 2s already sorted)
        //    pos      -1      solvable (if no 2s already sorted)
        //     a       b       a will be != b, if a > b not solvable 

        if( lastone == -1 && lastthree == -1 )
            return 0;
        if( lastone != -1 && lastthree != -1 && (lastone > lastthree || firstthree < firstone || firstthree < lastone) )
            return -1; 
        if( ((lastone == -1 && lastthree != -1) || (lastone != -1 && lastthree == -1)) && lasttwo == -1 )
            return 0;

        // only 1 or only 2 or only already covered
        // if we have only 1 and 3, it must be sorted
        // 1 and 3
        if( lasttwo == -1 )
            return 0;

        // that leaves 1 and 2, 2 and 3 OR 1, 2 and 3
        // 1 and 2
        if( lastthree == -1 ) {
            if( firsttwo == cnt[1] )
                return 0;

            // firsttwo to lastone - 1
            int ans = 0;
            for(int i = firsttwo; i < lastone; ++i)
                ans += locked[i];
            return ans;
        }
        // 2 and 3
        if( lastone == -1 ) {
            if( firstthree == cnt[2] )
                return 0;

            // firstthree to lasttwo - 1
            int ans = 0;
            for(int i = firstthree; i < lasttwo; ++i)
                ans += locked[i];
            return ans;
        }

        // 1, 2 and 3
        // sorted
        if( firsttwo == cnt[1] && firstthree == cnt[1] + cnt[2] )
            return 0;

        // if lastone == cnt[1]-1 -> 1's are sorted
        if( lastone == cnt[1]-1 ) {
            // firstthree to lasttwo-1
            int ans = 0;
            for(int i = firstthree; i < lasttwo; ++i)
                ans += locked[i];
            return ans;
        }
        // if firstthree == cnt[1] + cnt[2] -> 3's are sorted
        if( firstthree == cnt[1] + cnt[2] ) {
            // firsttwo to lastone - 1
            int ans = 0;
            for(int i = firsttwo; i < lastone; ++i)
                ans += locked[i];
            return ans;
        } 

        // firsttwo to last1-1 + firstthree to lasttwo-1
        int ret = 0;
        for(int i = firsttwo; i < lastone; ++i)
            ret += locked[i];
        for(int i = firstthree; i < lasttwo; ++i)
            ret += locked[i];

        return ret;
    }
};

/*


[1,2,1,2,3,2]
[1,0,1,1,0,1]
[1,2,1,1,3,2,2]
[1,0,1,1,0,1,0]
[1,2,1,2,3,2,1]
[0,0,0,0,0,0,0]
[2,2,2,2,2,2]
[1,1,1,1,1,1]
[2,2,3,2,1,2]
[0,0,0,0,0,0]
[1,1,1,1,1,1]
[1,1,1,1,1,1]
[2,2,2,2,2,2]
[1,1,1,1,1,1]
[3,3,3,3,3,3]
[1,1,1,1,1,1]
[1,1,1,3]
[1,1,1,1]
[1,1,2,2]
[1,1,1,1]
[2,2,1,1]
[0,1,0,1]
[3,3,2,2]
[0,1,0,1]
[1,1,3,1]
[0,0,0,0]
[1,1,1,2,2,3,3]
[1,1,1,1,1,1,1]
[1,1,2,3,2,3,2]
[1,1,1,0,0,1,0]
[2,1,2,2,2,3,3]
[1,1,1,0,0,1,0]
[2,2,1,2,2,3,2,3,2]
[1,0,1,0,1,0,1,0,1]
[2,2,1,2,2,2,3,2,2]
[1,0,1,0,1,0,1,0,1]
[3,1,3]
[0,0,0]
[1,1,1,1,3,1,3,1,3,3,3,3]
[0,0,0,0,0,0,0,0,0,0,0,0]

*/
