
// 403. Frog Jump
// https://leetcode.com/problems/frog-jump/




class Solution {
private:
    int n;
    int * _stones;
    unordered_map<int,int> um; // stone position, stone index (0-indexed)
    int ** mem;

    bool rec(int i, int k) {
        // cout << "rec i " << i << " k " << k << endl;
        if( i == n-1 )
            return true;

        // we have a choice to jump to a stone at j with j > i
        // where stones[j] == k-1 OR stones[j] == k OR stones[j] = k+1;

        if( mem[i][k] != -1 )
            return mem[i][k];

        bool flag = false;

        auto f = um.find(_stones[i]+k-1);
        if( f != um.end() && f->second > i )
            flag = rec(f->second,k-1);

        if( !flag ) {
            f = um.find(_stones[i]+k);
            if( f != um.end() && f->second > i )
                flag = rec(f->second,k);
        }

        if( !flag ) {
            f = um.find(_stones[i]+k+1);
            if( f != um.end() && f->second > i )
                flag = rec(f->second,k+1);
        }

        return mem[i][k] = flag;
    }

public:
    bool canCross(vector<int>& stones) {
        // example showing that frog can skip positions
        //         i 0  1  2  3  4  5
        // stones[i] 0  1  3  6  7  8 => answer is true, frog jumps from stone 3 to 5

        // 2 <= stones.length <= 2000
        // stones[0] == 0
        // first jump must be 1 unit => stones[1] == 1;
        if( stones[1] != 1 )
            return false;
        // also next valid would be either [0,1,2] or [0,1,3]

        /*
        // possible k max => stones[2000]
        int tt1[2001];
        tt1[0] = 0;
        int k = 1;
        for(int i = 1; i <= 2000; ++i) {
           if( i > 1000 )
                cout << "i " << i << " k " << k;
            tt1[i] = tt1[i-1] + k;
            if( i > 1000 )
                cout << " tt1[i] " << tt1[i] << endl;
            k = k+1;
        }
        // output i 2000 k 2000 tt1[i] 2001000
        */

        n = stones.size();

        for(int i = 0; i < n; ++i)
            um[stones[i]] = i;
        _stones = stones.data();

        mem = new int *[n+1];
        for(int i = 0; i <= n; ++i) {
            mem[i] = new int[n+1];
            for(int j = 0; j <= n; ++j)
                mem[i][j] = -1;
        }

        return rec(1,1);
    }
};
