
// 474. Ones and Zeroes
// https://leetcode.com/problems/ones-and-zeroes/
// day 2 April 2021 challenge
// https://leetcode.com/explore/featured/card/april-leetcoding-challenge-2021/593/week-1-april-1st-april-7th/3694/



class Solution {
private:
    int l,M,N,ans;
    // int mem[10201][601]; // m,n,l

    int dp(array<int,3> strsp[], int idx, int m, int n, int mem[], int depth) {
        // cout << idx << " " << m << " " << n << endl;
        if( m <= M && n <= N ) ans = max(ans,depth);
        if( idx >= l ) return 0;
        if( m == M && n == N ) return 0;

        // have we been here before?
        int i = (m*N+n)*l+idx;
        if( mem[i] != -1 ) return mem[i];

        // choice: select the current element or not.
        int a = 0,b;

        // can we select the current element?
        if( strsp[idx][0]+m <= M && strsp[idx][1]+n <= N ) {
            a = 1 + dp(strsp,idx+1,strsp[idx][0]+m,strsp[idx][1]+n,mem,depth+1);
        }
        b = dp(strsp,idx+1,m,n,mem,depth); // skip current element

        int res = max(a,b);
        // cout << idx << " " << m << " " << n << " return " << res << endl;
        return mem[i] = res;
    }

public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        l = strs.size();
        M = m;
        N = n;

        array<int,3> strsp[l]; // nbr zero's, nbr 1's
        int i,j,cnt0,cnt1,lgth;
        for(i = 0; i < l; ++i) {
            cnt0 = 0, cnt1 = 0;
            lgth = strs[i].size();
            for(j = 0; j < lgth; ++j)
                if( strs[i][j] == '0' ) ++cnt0;
                else ++cnt1;
            strsp[i] = {cnt0,cnt1,lgth};
        }
        sort(strsp,strsp+l,[](array<int,3>& a, array<int,3>& b){
            return a[2]<b[2];
        });

        int x = (m+1)*(n+1)*l;
        int mem[x]; // m,n,l
        for(i = 0; i < x; ++i)
            mem[i] = -1;

        ans = 0;
        dp(strsp,0,0,0,mem,0);
        return ans;
    }
};
