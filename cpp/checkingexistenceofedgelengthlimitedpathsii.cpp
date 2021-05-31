
// 1724. Checking Existence of Edge Length Limited Paths II
// https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths-ii/





class DistanceLimitedPathsExist {
private:
    int N;
    vector<vector<int>> * G;

public:
    DistanceLimitedPathsExist(int n, vector<vector<int>>& edgeList) {
        N = n;
        G = new vector<vector<int>>[n]; // unidirected graph of n nodes

        // edgeList[i] = [ui, vi, disi]

        for(int i = 0; i < edgeList.size(); ++i) {
           G[edgeList[i][0]].push_back({edgeList[i][1],edgeList[i][2]});
           G[edgeList[i][1]].push_back({edgeList[i][0],edgeList[i][2]});
        }
    }

    bool query(int p, int q, int limit) {

        // cout << "query p " << p << " q " << q << " limit " << limit << endl;

        // BFS shortest path
        int seen[N];memset(seen,0,sizeof seen);

        queue<int> qu;
        qu.push(p);
        seen[p] = 1;
        int curr,i;
        while(!qu.empty()) {
            curr = qu.front();
            qu.pop();
            for(i = 0; i < G[curr].size(); ++i) {
                // cout << "src " << curr << " edge to " << G[curr][i][0] << " dist " << G[curr][i][1] << endl;
                if( G[curr][i][1] < limit ) {
                    if( G[curr][i][0] == q ) return true;
                    if( !seen[G[curr][i][0]] ) {
                        seen[G[curr][i][0]] = 1;
                        qu.push(G[curr][i][0]);
                    }
                }
            }
        }
        return false;
    }
};

/**
 * Your DistanceLimitedPathsExist object will be instantiated and called as such:
 * DistanceLimitedPathsExist* obj = new DistanceLimitedPathsExist(n, edgeList);
 * bool param_1 = obj->query(p,q,limit);
 */
