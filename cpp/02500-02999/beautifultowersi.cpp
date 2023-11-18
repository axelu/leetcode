
// 2865. Beautiful Towers I
// https://leetcode.com/problems/beautiful-towers-i/



class Solution {
public:
    long long maximumSumOfHeights(vector<int>& maxHeights) {
        int n = maxHeights.size();
        if( n == 1 )
            return maxHeights[0];

        // pre-process left to right
        long long l2r[n];memset(l2r,0,sizeof l2r);
        stack<pair<int,int>> stck; // monotonic increasing stack
        for(int i = 0; i < n; ++i) {
            long long max_height = maxHeights[i];

            while( !stck.empty() && stck.top().first > max_height )
                stck.pop();

            if( !stck.empty() )
                l2r[i] = l2r[stck.top().second] + ((i - stck.top().second) * max_height);
            else
                l2r[i] = (i+1) * max_height;

            stck.push({maxHeights[i],i});
        }
        /*
        // debug
        for(int i = 0; i < n; ++i)
            cout << i << ":" << l2r[i] << " ";
        cout << endl;
        */

        // pre-process right to left
        long long r2l[n];memset(r2l,0,sizeof r2l);
        // stack<pair<int,int>> stck; // monotonic increasing stack
        while( !stck.empty() )
            stck.pop();

        for(int i = n-1; i >= 0; --i) {
            long long max_height = maxHeights[i];

            while( !stck.empty() && stck.top().first > max_height )
                stck.pop();

            if( !stck.empty() )
                r2l[i] = r2l[stck.top().second] + ((stck.top().second - i) * max_height);
            else
                r2l[i] = (n-i) * max_height;

            stck.push({maxHeights[i],i});
        }
        /*
        // debug
        for(int i = 0; i < n; ++i)
            cout << i << ":" << r2l[i] << " ";
        cout << endl;
        */

        // find max
        long long ans = 0;
        for(int i = 0; i < n-1; ++i)
            ans = max(ans, l2r[i] + r2l[i+1]);

        return ans;
    }
};
