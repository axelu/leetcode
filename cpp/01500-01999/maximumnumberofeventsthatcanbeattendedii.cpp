
// 1751. Maximum Number of Events That Can Be Attended II
// https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended-ii/




class Solution {
private:
    // binary search lower bound equal greater
    int search(vector<vector<int>>& events, int s, int e, int target) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        if( events[mid][0] >= target ) {
            // can we do better?
            int t = search(events,s,mid-1,target);
            return t != -1 ? t : mid;
        } else {
            return search(events,mid+1,e,target);
        }
    }

public:
    int maxValue(vector<vector<int>>& events, int k) {
        // sort by start time
        sort(events.begin(),events.end(),[](const vector<int>& a, const vector<int>& b){
           return a[0] < b[0];
        });

        // debug
        /* for(auto& v : events)
            cout << v[0] << "," << v[1] << " ";
        cout << endl; */

        int n = events.size();

        int * nxt = new int[n];
        int t;
        for(int i = 0; i < n; i++) {
            t = search(events,i+1,n-1,events[i][1]+1);
            nxt[i] = t != -1 ? t : n;
        }


        int ** mem = new int *[n+1];
        for(int i = 0; i <= n; i++)
            mem[i] = new int[k+1];

        for(int i = 0; i <= k; ++i)
            mem[n][i] = 0;
        for(int i = 0; i <= n; ++i)
            mem[i][0] = 0;

        // bottom up
        for(int i = n-1; i >= 0; --i)
            for(int j = 1; j <= k; ++j)
                mem[i][j] = max(events[i][2]+mem[nxt[i]][j-1],mem[i+1][j]);

        return mem[0][k];
    }
};
