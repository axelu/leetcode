
// 646. Maximum Length of Pair Chain
// https://leetcode.com/problems/maximum-length-of-pair-chain/


class Solution {
private:
    int rec(vector<vector<int>>& pairs, int& n, int prev, int i, int mem[]) {
        if( prev >= pairs[i][0] )
            return 0;

        if( mem[i] != -1 )
            return mem[i];

        int t = 0;
        for(int k = i+1; k < n; ++k)
            t = max(t,rec(pairs,n,pairs[i][1],k,mem));

        return mem[i] = 1+t;
    }
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        int n = pairs.size();
        if( n == 1 )
            return 1;

        sort(pairs.begin(),pairs.end(),[](const vector<int>& a, const vector<int>& b){
            if( a[1] < b[1] ) {
                return true;
            } else if( a[1] == b[1] ) {
                if( a[0] < b[0] )
                    return true;
            }
            return false;
        });

        /*
        // debug
        for(auto v : pairs)
            cout << v[0] << "," << v[1] << " ";
        cout << endl;
        */

        int mem[n];memset(mem,-1,sizeof mem);
        return rec(pairs,n,-1001,0,mem);
    }
};
