
// 2359. Find Closest Node to Given Two Nodes
// https://leetcode.com/problems/find-closest-node-to-given-two-nodes/




class Solution {
private:

    void calc_distances(vector<int>& edges, int node, int dist[], int steps) {
        if( node == -1 || dist[node] != -1 )
            return;

        dist[node] = steps;
        calc_distances(edges,edges[node],dist,steps+1);

        return;
    }

public:
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        if( node1 == node2 )
            return node1;

        int n = edges.size();

        int d1[n];memset(d1,-1,sizeof d1);
        calc_distances(edges,node1,d1,0);
        /*
        cout << "node1 " << node1 << " ";
        for(int i = 0; i < n; ++i)
            cout << i << ":" << d1[i] << " ";
        cout << endl;
        */

        int d2[n];memset(d2,-1,sizeof d2);
        calc_distances(edges,node2,d2,0);
        /*
        cout << "node2 " << node2 << " ";
        for(int i = 0; i < n; ++i)
            cout << i << ":" << d2[i] << " ";
        cout << endl;
        */

        int mn_mx_dist = 100001;
        int ans = -1;

        for(int i = 0; i < n; ++i)
            if( d1[i] != -1 && d2[i] != -1 ) {
                // cout << "node " << i << " d1 " << d1[i] << " d2 " << d2[i] << endl;
                // node i is reachable from node1 and node2

                int mx = max(d1[i],d2[i]);
                if( mx < mn_mx_dist ) {
                    mn_mx_dist = mx;
                    ans = i;
                }
            }

        return ans;
    }
};
