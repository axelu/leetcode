
// 3695. Maximize Alternating Sum Using Swaps
// https://leetcode.com/problems/maximize-alternating-sum-using-swaps/




class Solution {
private:
    vector<int> parent;

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
    long long maxAlternatingSum(vector<int>& nums, vector<vector<int>>& swaps) {
        int n = nums.size();

        // base case aka sum to beat: no swaps
        long long sum = 0LL;
        if( swaps.empty() ) {
            for(int i = 0; i < n; ++i) {
                if( i % 2 == 0 )
                    sum += (long long)nums[i];
                else
                    sum -= (long long)nums[i];
            }
            return sum;
        }

        // idea
        // indices involved in a swap can assume any position
        // swaps can be connected forming a connected component
        // for each connected component we count the even and odd indices
        // we sort (desc) the elements in each connected component
        // even indices we add (largest) and odds we subtract (smallest)

        parent.resize(n);
        for(int i = 0; i < n; ++i)
            parent[i] = i; // initially each node is connected to itself only

        int swap_sz = swaps.size();
        for(int i = 0; i < swap_sz; ++i) {
            int p = swaps[i][0];
            int q = swaps[i][1];
            if( findRoot(p) != findRoot(q) ) {
                // cout << "uniting p " << p << " and q " << q << endl;
                unite(p, q);
            }
        }

        map<int,vector<int>> ccs; // key: parent idx; value: list of idxs in cc
        for(int i = 0; i < n; ++i) {
            int root = findRoot(i); // cout << "parent of " << i << " is " << root << endl;
            ccs[root].push_back(i);
        }

        for(auto& p: ccs) {
            // TODO instead of using a new vector vals,
            // we could sort the indices in p.second by value desc
            vector<int> vals;
            int evens = 0;
            for(int i = 0; i < p.second.size(); ++i) {
                if( p.second[i] % 2 == 0 )
                    ++evens;
                vals.push_back(nums[p.second[i]]);
            }

            sort(vals.begin(), vals.end(), greater<int>());
            for(int i = 0; i < p.second.size(); ++i)
                if( i < evens )
                    sum += (long long)vals[i];
                else
                    sum -= (long long)vals[i];
        }

        return sum;
    }
};
