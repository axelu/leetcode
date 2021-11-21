
// 2076. Process Restricted Friend Requests
// https://leetcode.com/problems/process-restricted-friend-requests/



class Solution {
private:
    int * parent;

    // disjoint-set union-find
    int findRoot(int i) {
		// chase parent of current element until it reaches root

        while(parent[i] != i) {
            // path compression
            // set each i to point to its grandparent
            // (thereby halving the path length), where i
            // is the node which comes in between path,
            // while computing root
            parent[i] = parent[parent[i]] ;
            i = parent[i];
        }
		return i;
	}

	void unite(int p, int c) {
		p = findRoot(p);
		c = findRoot(c);
        if( p == c ) return;
		parent[c] = p;
	}

public:
    vector<bool> friendRequests(int n, vector<vector<int>>& restrictions, vector<vector<int>>& requests) {

        int _parent[n]; parent = _parent;
        for(int i = 0; i < n; ++i)
            parent[i] = i; // initially each node is connected to itself only

        unordered_set<int> _restrictions[n];
        for(int i = 0; i < restrictions.size(); ++i) {
            int x = restrictions[i][0];
            int y = restrictions[i][1];
            _restrictions[x].insert(y);
            _restrictions[y].insert(x);
        }


        int rqsz = requests.size();
        vector<bool> ans(rqsz,false);
        for(int i = 0; i < rqsz; ++i) {
            int u = requests[i][0];
            int v = requests[i][1];
            // cout << "processing friend request " << i << " u " << u << " v " << v << endl;

            // can u and v be friends?
            auto f = _restrictions[u].find(v);
            if( f != _restrictions[u].end() )
                continue;

            // are u and v already friends indirectly?
            int rootU = findRoot(u);
            int rootV = findRoot(v);
            // cout << "rootU " << rootU << " rootV " << rootV << endl;
            if( rootU == rootV ) {
                ans[i] = true;
                continue;
            }

            // if we make u and v friends,
            // would it violate a transitory restriction?
            bool flag = true;
            for(int j = 0; j < restrictions.size(); ++j) {
                int x = restrictions[j][0];
                int y = restrictions[j][1];
                int rootX = findRoot(x);
                int rootY = findRoot(y);
                if( (rootU == rootX && rootV == rootY) ||
                    (rootV == rootX && rootU == rootY) ) {
                    flag = false;
                    break;
                }
            }
            if( flag ) {
                // cout << "uniting u " << u << " v " << v << endl;
                unite(u,v);
                ans[i] = true;
            }
        }

        return ans;
    }
};
