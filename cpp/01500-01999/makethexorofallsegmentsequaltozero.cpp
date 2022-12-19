
// 1787. Make the XOR of All Segments Equal to Zero
// https://leetcode.com/problems/make-the-xor-of-all-segments-equal-to-zero/




class Solution {
private:
    int n, K;
    int * _nums;
    unordered_map<int,unordered_set<int>> umus;

    int mem1[1024][2000];
    int mem2[1024][2000];

    int solve(int x, int i) {
        if( mem2[x][i] != -1 )
            return mem2[x][i];

        int ret = 0;
        for(int j = i; j < n; j = j + K)
            if( _nums[j] != x )
                ++ret;

        return mem2[x][i] = ret;
    }

    int rec(int _xor, int i) {
        if( i == K-1 ) {
            // we must change nums[k-1] to make
            // XOR [0,k-1] = 0;
            int t = solve(_xor,i+K);
            return _nums[i] != _xor ? 1 + t : t;
        }

        if( mem1[_xor][i] != -1 )
            return mem1[_xor][i] ;

        // we have a choice
        //     keep nums[i] as is
        //     change nums[i] ( 0 <= nums[i] < 1024 )

        int ret = 2001;

        for(auto it = umus[i].begin(); it != umus[i].end(); ++it) {
            int t1 = solve(*it,i+K);
            int t2 = rec(_xor^*it,i+1);
            int t3 = *it != _nums[i] ? 1 : 0;
            ret = min(ret,t1+t2+t3);
        }
        /*for(int j = 0; j < 1024; ++j) {
            int t1 = solve(j,i+K);
            int t2 = rec(_xor^j,i+1);
            int t3 = j != _nums[i] ? 1 : 0;
            ret = min(ret,t1+t2+t3);
        }*/


        return mem1[_xor][i] = ret;
    }


public:
    int minChanges(vector<int>& nums, int k) {
        // contstraints
        //     1 <= k <= nums.length <= 2000
        //     0 <= nums[i] < 2^10 = 1024
        // from the hints
        //     Let's note that for the XOR of all segments with size K to be equal to zeros,
        //     nums[i] has to be equal to nums[i+k]
        //     Basically, we need to make the first K elements have XOR = 0 and then modify them.

        int ans = 0;

        // edge case
        // if k == 1 we have to change all non zero elements to 0
        if( k == 1 ) {
            for(auto x: nums)
                if( x != 0 )
                    ++ans;
            return ans;
        }

        // edge case
        // if k == n
        //     if XOR of all elements == 0 => 0
        //     if XOR of all elements != 0 => 1
        n = nums.size();
        if( k == n ) {
            int t = nums[0];
            for(int i = 1; i < n; ++i)
                t ^= nums[i];
            return t == 0 ? 0 : 1;
        }

        K = k;
        _nums = nums.data();

        // optimization 1
        // only consider numbers that exist at given index
        for(int i = 0; i < n; ++i) {
            int idx = i % k;
            umus[idx].insert(nums[i]);
        }

        memset(mem1,-1,sizeof mem1);
        memset(mem2,-1,sizeof mem2);
        ans = 2001;
        /*for(auto it = umus[0].begin(); it != umus[0].end(); ++it) {
            int t = solve(*it,k) + rec(*it,1);
            if( *it != nums[0] )
                ++t;
            ans = min(ans,t);
        }*/
        for(int j = 0; j < 1024; ++j) {
            int t = solve(j,k) + rec(j,1);
            if( j != nums[0] )
                ++t;
            ans = min(ans,t);
        }


        return ans;
    }
};
