
// 3488. Closest Equal Element Queries
// https://leetcode.com/problems/closest-equal-element-queries/





class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        int n = nums.size(); // 1 <= n <= 1e5; 1 <= nums[i] <= 1e6
        if( n == 1 )
            return {-1};

        // pass 1
        vector<pair<int,int>> mnmx(1000001, {-1,-1});
        for(int i = 0; i < n;++i) {
            int x = nums[i];
            if( mnmx[x].first == -1 )
                mnmx[x].first = i;
            mnmx[x].second = i;
        }

        // pass 2
        // last seen to our left
        int lastseen[1000001];memset(lastseen,-1,sizeof lastseen);
        int lastseenleft[100000];memset(lastseenleft,-1,sizeof lastseenleft);
        for(int i = 0; i < n; ++i) {
            int x = nums[i];
            if( mnmx[x].first == mnmx[x].second )
                continue;

            if( lastseen[x] == -1 ) {
                lastseenleft[i] = mnmx[x].second;
                lastseen[x] = i;
            } else {
                lastseenleft[i] = lastseen[x];
                lastseen[x] = i;
            }
        }

        // pass 3
        // last seen to our right
        memset(lastseen,-1,sizeof lastseen);
        int lastseenright[100000];memset(lastseenright,-1,sizeof lastseenright);
        for(int i = n-1; i >= 0; --i) {
            int x = nums[i];
            if( mnmx[x].first == mnmx[x].second )
                continue;

            if( lastseen[x] == -1 ) {
                lastseenright[i] = mnmx[x].first;
                lastseen[x] = i;
            } else {
                lastseenright[i] = lastseen[x];
                lastseen[x] = i;
            }
        }

        // process queries
        int q_sz = queries.size();
        vector<int> ans(q_sz, -1);
        for(int k = 0; k < q_sz; ++k) {
            int idx = queries[k];
            int x = nums[idx];
            if( mnmx[x].first == mnmx[x].second )
                continue;

            // cout << "q idx " << k << "  idx " << idx << " x " << x << " lastleft " << lastseenleft[idx] << " lastright " << lastseenright[idx] << endl;

            int dist = INT_MAX;

            if( lastseenleft[idx] < idx )
                dist = min(dist, idx - lastseenleft[idx]);
            else
                dist = min(dist, idx + (n - lastseenleft[idx]));

            if( lastseenright[idx] > idx )
                dist = min(dist, lastseenright[idx] - idx);
            else
                dist = min(dist, (n - idx) + lastseenright[idx]);

            ans[k] = dist;
        }

        return ans;
    }
};
