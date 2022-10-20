
// 2305. Fair Distribution of Cookies
// https://leetcode.com/problems/fair-distribution-of-cookies/




class Solution {
private:
    int ans;

    void rec(vector<int>& cookies, int n, int k, int bag, int s[]) {
        if( bag == n ) {
            int mx = 0;
            for(int i = 0; i < k; ++i)        // child
                mx = max(mx,s[i]);

            ans = min(ans,mx);

            return;
        }

        for(int i = 0; i < k; ++i) {
            // give the current bag to the ith (0-indexed) child

            s[i] += cookies[bag];
            if( s[i] <= ans )
                rec(cookies,n,k,bag+1,s);

            // backtrack
            s[i] -= cookies[bag];
        }
    }

public:
    int distributeCookies(vector<int>& cookies, int k) {
        int n = cookies.size();
        if( n == k )
            return *max_element(cookies.begin(),cookies.end());

        ans = INT_MAX;

        int s[k];memset(s,0,sizeof s);
        rec(cookies,n,k,0,s);

        return ans;
    }
};
