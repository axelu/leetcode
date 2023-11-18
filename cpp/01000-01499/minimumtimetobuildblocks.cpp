
// 1199. Minimum Time to Build Blocks
// https://leetcode.com/problems/minimum-time-to-build-blocks/





class Solution {
private:
    int mem[1000][1000];

    int rec(vector<int>& blocks, int n, int pos, int workers, int split, int mx[]) {
        // cout << "rec pos " << pos << " workers " << workers << endl;
        if( pos == n )
            return 0;

        if( workers == 0 )
            return INT_MAX;

        // if we have enough workers to build the remaining blocks including
        // the block at our pos, then we don't need to split more workers
        int rem = n - pos; // blocks remaining including our block
        if( workers >= rem )
            return mx[pos];

        if( mem[pos][workers] != -1 )
            return mem[pos][workers];

        // we have a choice
        //    built the block at pos OR
        //    split workers and then built the block at pos

        int ret = max(blocks[pos],rec(blocks,n,pos+1,workers-1,split,mx));

        int t = 0;
        int workers_new = workers;
        while( workers_new < rem ) {

            // perform a split
            t += split;
            workers_new *= 2;

            int result = t + max(blocks[pos], rec(blocks,n,pos+1,workers_new-1,split,mx));
            ret = min(ret, result);

        }

        return mem[pos][workers] = ret;
    }

public:
    int minBuildTime(vector<int>& blocks, int split) {
        int n = blocks.size();
        // cout << "n " << n << endl;
        sort(blocks.begin(),blocks.end(),greater<int>());

        int mx[n]; // max blocks i to n-1
        mx[n-1] = blocks[n-1];
        for(int i = n-2; i >= 0; --i)
            mx[i] = max(mx[i+1],blocks[i]);

        memset(mem,-1,sizeof mem);
        return rec(blocks,n,0,1,split,mx);
    }
};
