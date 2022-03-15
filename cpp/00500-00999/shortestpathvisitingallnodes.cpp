
// 847. Shortest Path Visiting All Nodes
// https://leetcode.com/problems/shortest-path-visiting-all-nodes/


class Solution {
private:
    // debug
    void printBinary(int x) {
        for(int i = 11; i >= 0; --i) {
            if( x & (1 << i) ) cout << 1;
            else cout << 0;
        }
        // cout << endl;
    }
    
    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

public:
    int shortestPathLength(vector<vector<int>>& graph) {
        // undirected connected graph of n nodes labeled from 0 to n - 1
        int n = graph.size(); // 1 <= n <= 12
        
        // array<int,3> distance,current node, mask of visited nodes

        // min heap based on weight, respectively distance
        auto cmp = [&] (const array<int,3>& a, const array<int,3>& b) { 
            if( a[0] > b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( countSetBits(a[2]) < countSetBits(b[2]) )
                    return true;
            }
            return false;
        };
        priority_queue<array<int,3>,vector<array<int,3>>,decltype(cmp)> pq(cmp);

        // seen
        // bits from the left 0-11 mask, 12-15 u, 16-31 distance
        // that gives us a distance of 65535
        unordered_set<int> seen;

        // push our source vertex into priority queue with a distance of 0
        // we are starting from every vertex 0 to n-1
        // set distance to our source vertex itself to 0
        int mask,t;
        for(int i = 0; i < n; ++i) {
            mask = 0 ^ (1 << i); // set the ith bit = mark our source vertex as visited
            pq.push({0,i,mask});
            
            t = mask + (i<<12);
            seen.insert(t);
        }

        
        int all = pow(2,n) - 1;
        
        int d,u,v,mask_v;
        while(!pq.empty()) {

            d    = pq.top()[0]; // distance that got us here
            u    = pq.top()[1]; // current node
            mask = pq.top()[2]; // mask of visited nodes
            pq.pop();
            // cout << "d " << d << " u " << u << " mask "; printBinary(mask); cout << endl;
            
            if( mask == all )
                return d;
            
            // from our current node, we can go to any other node
            // that we have an edge to, including nodes we have
            // already visited
            
            for(int i = 0; i < graph[u].size(); ++i) {
                v = graph[u][i];
                mask_v = 0 ^ (1 << v);
                t = (mask|mask_v) + (v<<12) + (d<<16);
                if( seen.count(t) )
                    continue;
                seen.insert(t);
                pq.push({d+1,v,mask|mask_v});
            }
            
        }
        
        // satisfy compiler
        return 99;
    }
};


// below passed 7/14/2021, but too slow when new test was added,
// so failed with TLE 2/25/2022

class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        // undirected connected graph of n nodes labeled from 0 to n - 1
        int n = graph.size(); // 1 <= n <= 12


        // Dijkstra's algorithm
        // shortest path adapted


        // distances[node][bitmask] stores the shortest path to get to node
        // after visiting some nodes.  The visited nodes are encoded in
        // the bitmask, e.g. if node 0 and 1 had been visited, the mask
        // would look like this for a graph with 12 nodes: 000000000011
        // initial length is infinity, except length to get started is zero
        map<array<int,2>,int> A; // key: node,bitmask


        // min heap based on weight, respectively distance
        auto cmp = [A] (const array<int,2>& a, const array<int,2>& b) mutable {
            return A[{a[0],a[1]}] > A[{b[0],b[1]}];
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq(cmp);


        // push our source vertex into priority queue with a distance of 0
        // we are starting from every vertex 0 to n-1
        // set distance to our source vertex itself to 0
        int mask;
        for(int i = 0; i < n; ++i) {
            mask = 0 ^ (1 << i); // set the ith bit = mark our source vertex as visited
            A[{i,mask}] = 0;
            pq.push({i,mask});
        }

        int u,v,mask_v;
        while(!pq.empty()) {

            u    = pq.top()[0];
            mask = pq.top()[1];
            pq.pop();

            // distance it took us to get here
            // A[{u,mask}];


            vector<int>::iterator it;
            for(it = graph[u].begin(); it != graph[u].end(); ++it) {
                v = *it;
                mask_v = 0 ^ (1 << v);

                // lazy insert
                if( !A.count({v,mask|mask_v}) )
                    A[{v,mask|mask_v}] = INT_MAX;

                //  If there is shorter path to v through u.
                if( A[{v,mask|mask_v}] > A[{u,mask}] + 1 ) { // each edge has lenght of 1
                    // Updating distance of v
                    A[{v,mask|mask_v}] = A[{u,mask}] + 1;
                    pq.push({v,mask|mask_v});
                }

            }
        }

        int ans = INT_MAX;
        mask = pow(2,n)-1; // mask when all nodes visted
        for(int i = 0; i < n; ++i) {
            // cout << "i:" << i << " " << A[{i,mask}] << " " << endl;
            ans = min(ans,A[{i,mask}]);
        }
        return ans;
    }
};
