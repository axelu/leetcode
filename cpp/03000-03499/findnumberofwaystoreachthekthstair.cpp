
// 3154. Find Number of Ways to Reach the K-th Stair
// https://leetcode.com/problems/find-number-of-ways-to-reach-the-k-th-stair/





class Solution {
private:
    unordered_map<long,int> mem;


    int solve(int pos, int jump, const int k) {
        // cout << "solve pos " << pos << " jump " << jump << endl;
        if( pos > k && pos - k > 1 )
            return 0;

        long key = ((long)pos<<30) + jump;
        auto f = mem.find(key);
        if( f != mem.end() )
            return f->second;

        // we can go backward 1 and then jump OR
        // we can jump

        // are we at k?
        int ret = pos == k ? 1 : 0;

        // back 1 then jump
        if( pos > 0 ) {
            if( pos - 1 == k )
                ++ret;

            ret += solve( pos - 1 + pow(2,jump), jump + 1, k);
        }

        ret += solve( pos + pow(2,jump), jump + 1, k);

        return mem[key] = ret;
    }

public:
    int waysToReachStair(int k) {
        if( k == 0 )
            return 2;
        if( k == 1 )
            return 4;


        return solve(1, 0, k);
    }
};
