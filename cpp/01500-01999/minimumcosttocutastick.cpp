
// 1547. Minimum Cost to Cut a Stick
// https://leetcode.com/problems/minimum-cost-to-cut-a-stick/




class Solution {
private:
    int mem[103][103];
    map<int,int> m; // cuts[i],idx

    int rec(vector<int>& cuts, int s, int e) {
        // cout << "rec s " << s << " e " << e << endl;
        int i = m[s];
        int j = m[e];
        // cout << "rec i " << i << " j " << j << endl;

        // there cannot be any cuts anymore
        if( i+1 == j )
            return 0;

        if( mem[i][j] != -1 )
            return mem[i][j];

        // we have to make one cut
        // and regardless of where we make it
        // it will cost the same
        int a = e-s;

        // we have a choice
        // every one of the cuts between cuts[i] and cuts[j]
        // can be the 1st cut we make
        int ret = INT_MAX;
        int l,r; // cost of the cuts left and right of k
        for(int k = i+1; k < j; ++k) {
            l = rec(cuts,s,cuts[k-1]);
            r = rec(cuts,cuts[k-1],e);
            ret = min(ret,r+l);
        }

        return mem[i][j] = a + ret;
    }
public:
    int minCost(int n, vector<int>& cuts) {
        // 2 <= n <= 10^6
        // 1 <= cuts.length <= min(n - 1, 100)
        // 1 <= cuts[i] <= n - 1

        sort(cuts.begin(),cuts.end());

        // we will need a map of cuts[i] to index in our mem[101][101]
        int i = 0;
        m[0] = i;
        for(; i < cuts.size(); ++i)
            m[cuts[i]] = i+1;
        m[n] = i+1;

        memset(mem,-1,sizeof mem);

        return rec(cuts,0,n);
    }
};
