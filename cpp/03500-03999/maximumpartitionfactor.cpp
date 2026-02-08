
// 3710. Maximum Partition Factor
// https://leetcode.com/problems/maximum-partition-factor/

/* https://brilliant.org/wiki/distinct-objects-into-identical-bins/
 * for our scenario we have 2 identical bins, hence
 * 2^(n−1) − 1 => example n = 4, then 7 possibilties
 * worst case 500 points => brute force not feasible even if only
 * testing distances selected by binary search
 * as we aer splitting the pints into two groups, we can look at
 * https://en.wikipedia.org/wiki/Bipartite_graph
 * https://cp-algorithms.com/graph/bipartite-check.html
 * see 785. Is Graph Bipartite? https://leetcode.com/problems/is-graph-bipartite/
 */
class Solution {
private:
    bool is_bipartite(vector<pair<int,int>> g[], int n, int d) {
        vector<int> side(n, -1);
        bool f = true;
        queue<int> q;
        for (int st = 0; st < n; ++st) {
            if (side[st] == -1) {
                q.push(st);
                side[st] = 0;
                while (!q.empty()) {
                    int v = q.front();
                    q.pop();
                    for (auto p: g[v]) {
                        int dist = p.first;
                        int u = p.second;
                        if( dist >= d ) // only connect dist le d
                            break;
                        if (side[u] == -1) {
                            side[u] = side[v] ^ 1;
                            q.push(u);
                        } else {
                            f &= side[u] != side[v];
                        }
                    }
                }
            }
        }
        return f;
    }

public:
    int maxPartitionFactor(vector<vector<int>>& points) {
        int n = points.size(); // 2 <= points.length <= 500
        if( n == 2 )
            return 0;

        // formula number of pairs n * (n-1)/2
        // worst case n = 500 => 124,750 pairs

        sort(begin(points), end(points));

        vector<pair<int,int>> g[500];
        unordered_set<int> unique_distances;
        for(int i = 0; i < n; ++i) {
            int xi = points[i][0];
            int yi = points[i][1];
            for(int j = i+1; j < n; ++j) {
                int xj = points[j][0];
                int yj = points[j][1];
                int manhattan = abs(xi - xj) + abs(yi - yj);
                g[i].push_back({manhattan, j});
                g[j].push_back({manhattan, i});
                unique_distances.insert(manhattan);
            }
        }

        vector<int> d(unique_distances.begin(), unique_distances.end());
        sort(d.begin(), d.end());
        if( n == 3 )
            return d.back();

        for(int i = 0; i < n; ++i)
            sort(begin(g[i]), end(g[i]));

        // our unique distances have smallest...largest
        // we know smallest will be a solution, hence
        // shifting unique distances one up
        d.push_back(INT_MAX); // sentinel

        // binary search
        int s = 0;
        int e = d.size(); // n = nums.size()
        int mid;
        bool f;
        while(s <= e) {
            mid = s + ((e-s)/2);
            f = is_bipartite(g, n, d[mid]);
            if( !f )
                e = mid-1;
            else
                s = mid+1;
        }

        return d[e];
    }
};


/* test cases used

[[0,0],[0,2],[2,0],[2,2]]
[[0,0],[0,1],[10,0]]
[[0,0],[0,0],[0,0],[10,0]]
[[-66397,-34995],[-2453,-42401],[20537,-8704],[22668,-62907]]
[[-53835,-36443],[-86846,-61445],[99645,-14741],[52934,58464]]
[[30702,-7721],[-90231,22039],[-46052,-81802],[65846,47479],[-80036,-72416],[62952,-16129],[-86171,70581],[-88227,-34551],[-12657,23608],[84923,79051],[14794,87489],[2576,-16670],[76295,88970],[-72355,19476],[28372,54296],[63232,-75527],[-49737,-56955],[-41523,91235],[64082,-41362],[4972,-51837],[65310,80700],[66558,-39073],[12306,88019],[12143,4598],[-25125,53747],[84849,-22326],[-73555,-29731],[-36415,-35279],[-30872,-47374]]
*/

// passes 485/741 test cases, then TLE
// case 486 runs in about ~900ms returning correct result, but obviously too slow


/* https://brilliant.org/wiki/distinct-objects-into-identical-bins/
 * for our scenario we have 2 identical bins, hence
 * 2^(n−1) − 1 => example n = 4, then 7 possibilties
 * worst case 500 points => brute force not feasible
 */
class Solution {
private:
    int distances[500][500];
    int A[500];
    int B[500];

    int n;
    int d[124750]; // unique sorted distances

    // recursive
    bool solve(int i, int mn_dist) {
        if( i == n )
            return true;

        bool ret;

        // can we push point i into group A
        bool f = true;
        int k = 0;
        for(; k < n && A[k] != -1; ++k) {
            if( distances[i][A[k]] < mn_dist ) {
                f = false;
                break;
            }
        }
        if( f ) {
            A[k] = i;
            ret = solve(i+1, mn_dist);
            A[k] = -1; // backtrack
            if( ret )
                return true;
        }
        // can we push point i into group B
        f = true;
        k = 0;
        for(; k < n && B[k] != -1; ++k) {
            if( distances[i][B[k]] < mn_dist ) {
                f = false;
                break;
            }
        }
        if( !f )
            return false;
        B[k] = i;
        ret = solve(i+1, mn_dist);
        B[k] = -1; // backtrack
        return ret;
    }


    // binary search
    int search(int s, int e) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        bool f = solve(0, d[mid]);
        if( f ) {
            // can we do better?
            int t = search(mid+1, e);
            return t != -1 ? t : mid;
        }

        return search(s, mid-1);
    }

public:
    int maxPartitionFactor(vector<vector<int>>& points) {
        n = points.size(); // 2 <= points.length <= 500
        if( n == 2 )
            return 0;

        // note: points can be dups, so we need to dedup
        sort(begin(points), end(points));
        for(auto it = next(points.begin()); it != points.end(); ) {
            if( *prev(it) == *it )
                it = points.erase(it);
            else
                ++it;
        }
        n = points.size();
        if( n <= 2 )
            return 0;

        // idea
        //      collect all unique manhattan distances between all point pairs
        //          in sorted order
        //      if there is only one, that is our answer
        //      if there are two, the smaller one is our answer
        //      arbitrarily assign a point to group A, let us just use point 0
        //      binary search
        //      pick one of the unique distances
        //      move an additional point

        // formula number of pairs n * (n-1)/2
        // worst case n = 500 => 124,750 pairs

        // set default to infinity ???
        // memset(distances,0,sizeof distances);
        unordered_set<int> unique_distances;
        for(int i = 0; i < n-1; ++i) {
            int xi = points[i][0];
            int yi = points[i][1];
            for(int j = i+1; j < n; ++j) {
                int xj = points[j][0];
                int yj = points[j][1];
                int manhattan = abs(xi - xj) + abs(yi - yj);
                // put into our matrix
                distances[i][j] = manhattan;
                distances[j][i] = manhattan;
                unique_distances.insert(manhattan);
            }
        }

        int didx = 0;
        for(int ud: unique_distances)
            d[didx++] = ud;
        sort(d,d+didx);
        // for(int i = 0; i < didx; ++i)
        //     cout << d[i] << " ";
        // cout << endl;




        if( n == 3 )
            return d[didx-1];

        memset(A,-1,sizeof A);
        memset(B,-1,sizeof B);
        return d[search(0, didx-1)];
    }
};
