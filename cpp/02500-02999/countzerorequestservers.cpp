
// 2747. Count Zero Request Servers
// https://leetcode.com/problems/count-zero-request-servers/




class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        int q_sz = queries.size();
        vector<int> ans(q_sz,n);

        //  sort logs by time
        sort(logs.begin(),logs.end(),[](const vector<int>& a, const vector<int>& b){
            return a[1] < b[1];
        });
        // debug
        // for(int i = 0; i < log_sz; ++i)
        //    cout << "time:" << logs[i][1] << ":server:" << logs[i][0] << " " << endl;


        vector<array<int,2>> _queries(q_sz); // original index i, queries[i]
        for(int i = 0; i < q_sz; ++i)
            _queries[i] = {i,queries[i]};
        // sort queries by time
        sort(_queries.begin(),_queries.end(),[](const array<int,2>& a, const array<int,2>& b){
           return a[1] < b[1];
        });

        // sliding window
        int cnt = 0; // number of unique servers w/ request in window
        int req_cnt[n+1];memset(req_cnt,0,sizeof req_cnt); // req cnt per server in window
        int log_sz = logs.size();
        int i = 0;                      // left index in logs
        int j = -1;                     // right index in logs
        for(int k = 0; k < q_sz; ++k) { // index in _queries
            int qs = _queries[k][1] - x;
            if( qs > logs[log_sz-1][1] )
                continue;
            int qe = _queries[k][1];
            if( qe < logs[0][1] )
                continue;

            // advance j
            while( j < log_sz - 1 && logs[j+1][1] <= qe ) {
                ++j;
                ++req_cnt[logs[j][0]];
                if( req_cnt[logs[j][0]] == 1 )
                    ++cnt;
            }
            // advance i
            while( i < log_sz && logs[i][1] < qs ) {
                --req_cnt[logs[i][0]];
                if( req_cnt[logs[i][0]] == 0 )
                    --cnt;
                ++i;
            }

            ans[_queries[k][0]] = n - cnt;
        };

        return ans;
    }
};
