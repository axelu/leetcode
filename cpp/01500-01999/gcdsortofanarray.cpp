
// 1998. GCD Sort of an Array
// https://leetcode.com/problems/gcd-sort-of-an-array/

// see also https://calcworkshop.com/number-theory/greatest-common-divisor/

class Solution {
private:
    vector<int> parent;

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
    bool gcdSort(vector<int>& nums) {
        
        // see also solution for 
        // Largest Component Size by Common Factor
        // https://leetcode.com/problems/largest-component-size-by-common-factor/
        
        // get max element so we can initialize the vector<int> we will use to
        // keep track of the connectivity of our elements.  As the max element
        // could be a prime, the max element determines the size for the vector.
        int me = *max_element(nums.begin(), nums.end());

        // initialize the parent vector with every node connected to itself,
        // parent[k] = k
        for(int k = 0; k <= me; ++k) {
            parent.push_back(k);
        }

        // create connectivity between our elements based on their prime factors
        for (int k : nums) {
			int a = k;
			for (int i = 2; i * i <= k; ++i)
				if (k % i == 0) {
					while (k % i == 0)
						k /= i;
                    unite(i, a);
				}
			if (k > 1) {
				unite(k, a); // unite(p,c)
            }
		}
        
        /*
        for(int i = 0; i < parent.size(); ++i)
            cout << i << ":" << parent[i] << " ";
        cout << endl;
        
        for (int k : nums)
            cout << "root " << k << " " << findRoot(k) << endl;
        */
        
        vector<int> nums_sorted(nums);
        sort(begin(nums_sorted),end(nums_sorted));
        
        
        // needed if we would actually sort nums
        /*
        unordered_map<int,vector<int>> um; // value, positions of value in sorted array
        pair<unordered_map<int,vector<int>>::iterator,bool> p;
        for(int i = 0; i < nums.size(); ++i) {
            p = um.insert({nums_sorted[i],{i}});
            if( !p.second )
                p.first->second.push_back(i);
        }
        */
        
        
        for(int i = 0; i < nums.size(); ++i) {
            // we only need to see if we can swap whatever
            // occupies i in nums with what should occupy i in nums
            // the latter is the value in our sorted version of nums
            if( findRoot(nums[i]) != findRoot(nums_sorted[i]) )
                return false;
            
            
            // this would actually sort nums
            /*
            if( nums[i] == nums_sorted[i] )
                continue;
            
            // the value at position i in nums is wrong
            // if it cannot be swapped then nums cannot be sorted
            
            // swap till we get the right value
            while( nums[i] != nums_sorted[i] ) {
                // where should current nums[i] go
                auto f = um.find(nums[i]);
                int pos_new = f->second.back();
                if( findRoot(nums[i]) != findRoot(nums[pos_new]) )
                    return false;
                
                // swap
                int t = nums[i];
                nums[i] = nums[pos_new];
                nums[pos_new] = t;
                
                f->second.pop_back();
            }
            */
        }
        
        return true;
    }
};
