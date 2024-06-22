
// 656. Coin Path
// https://leetcode.com/problems/coin-path/





class Solution {
private:
    bool cmp(vector<int>& a, vector<int>& b) {
        // returns true if vector<int> a is lexicographically less than vector<int> b
        // it is guaranteed that a and b are different

        // A string s is lexicographically greater than a string t,
        // if in the first position where s and t differ,
        // string s has a letter that appears later in the alphabet than
        // the corresponding letter in t.
        // If the first min(s.length, t.length) characters do not differ,
        // then the longer string is the lexicographically greater one.

        int a_sz = a.size();
        int b_sz = b.size();
        for(int i = 0; i < min(a_sz,b_sz); ++i)
            if( a[i] != b[i] )
                return a[i] < b[i];

        return a_sz < b_sz;
    }


    // Dijkstra's algorithm
    vector<int> shortestPath(vector<int>& coins, int n, int maxJump) {

        int distances[n];
        int parent[n];
        for(int i = 0; i < n; ++i) {
            distances[i] = 1000000;
            parent[i] =    1000000;
        }

        // min heap distance, source, node
        priority_queue<array<int,3>,vector<array<int,3>>,greater<array<int,3>>> pq;

        // start is 0, end is n-1
        int s = 0;
        // but note that the output asks for coins to be 1-indexed

        // push our source vertex into priority queue
        pq.push({0,-1,s});
        // set distance to our source vertex itself to 0
        distances[s] = 0;
        parent[0] = -1;

        int u,v,weight;
        while(!pq.empty()) {

            u = pq.top()[2];
            pq.pop();

            for(int v = u + 1; v <= min(n-1,u+maxJump); ++v) {
                if( coins[v] == -1 )
                    continue;

                int weight = coins[v];
                if( distances[u] + weight < distances[v] ) { // smaller distance path
                    distances[v] = distances[u] + weight;
                    parent[v] = u;
                    pq.push({distances[v],u,v});

                } else if( distances[u] + weight == distances[v] ) {
                    // construct current path to v
                    vector<int> cur_path;
                    cur_path.push_back(v+1);
                    int _parent = parent[v];
                    while( _parent >= 0 ) {
                        cur_path.push_back(_parent+1);  // the path is asked to be 1-indexed
                        _parent = parent[_parent];
                    }
                    reverse(cur_path.begin(),cur_path.end());

                    // construct new path to v
                    vector<int> new_path;
                    new_path.push_back(v+1);
                    new_path.push_back(u);
                    _parent = parent[u];
                    while( _parent >= 0 ) {
                        new_path.push_back(_parent+1);  // the path is asked to be 1-indexed
                        _parent = parent[_parent];
                    }
                    reverse(new_path.begin(),new_path.end());

                    // is current path lexicographically smaller?
                    bool f = cmp(new_path,cur_path);
                    if( f ) {
                        // lexicographically smaller path
                        parent[v] = u;
                        pq.push({distances[v],u,v});
                    }
                }
            }
        }

        vector<int> path;
        path.push_back(n);              // the path is asked to be 1-indexed
        int _parent = parent[n-1];
        while( _parent >= 0 ) {
            path.push_back(_parent+1);  // the path is asked to be 1-indexed
            _parent = parent[_parent];
        }

        reverse(path.begin(),path.end());
        return path;
    }


public:
    vector<int> cheapestJump(vector<int>& coins, int maxJump) {
        int n = coins.size();
        if( n == 1 )
            return {1};
        if( coins[n-1] == -1 )
            return {};
        // let blocked be the maximum number of consecutive -1s
        // if blocked >= maxJump, then there is no solution
        int blocked = 0;
        int cnt = 0;
        for(int i = 0; i < n; ++i) {
            if( coins[i] == -1 ) {
                ++cnt;
            } else {
                blocked = max(blocked,cnt);
                cnt = 0;
            }
        }
        blocked == max(blocked,cnt);
        if( blocked >= maxJump )
            return {};

        return shortestPath(coins,n,maxJump);
    }
};
