
// 2007. Find Original Array From Doubled Array
// https://leetcode.com/problems/find-original-array-from-doubled-array/




class Solution {
public:
    vector<int> findOriginalArray(vector<int>& changed) {
        int n = changed.size();
        if( n%2 != 0 )
            return {};

        int cnt[100001];memset(cnt,0,sizeof cnt);

        int mn = INT_MAX;
        int mx = INT_MIN;
        for(int i = 0; i < n; ++i) {
            ++cnt[changed[i]];
            if( changed[i] > 0 )
                mn = min(mn,changed[i]);
            mx = max(mx,changed[i]);
        }

        vector<int> ans(n/2,0);

        int k = 0;
        if( cnt[0] != 0 ) {
            int rem = cnt[0]%2;
            if( rem )
                return {};
            k = (cnt[0]/2);
        }

        for(int i = mn; i <= mx/2; ++i) {
            // cout << "i " << i << endl;
            if( cnt[i] != 0 ) {
                int twice = i*2;
                if( cnt[twice] < cnt[i] )
                    return {};
                int k_new = k+cnt[i];
                for(; k < k_new; ++k)
                    ans[k] = i;
                cnt[twice] -= cnt[i];
            }
        }

        if( k == n/2 )
            return ans;

        return {};
    }
};
