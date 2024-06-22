
// 2157. Groups of Strings
// https://leetcode.com/problems/groups-of-strings/


class Solution {
private:
    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }
    
    int * parent;
    int * size;
    int mx_size;

    // disjoint-set union-find, tracks size of component also
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

	int unite(int p, int c) {
		p = findRoot(p);
		c = findRoot(c);
        if( p == c ) return 0;
		parent[c] = p;
        size[p] += size[c]; // add size of child to parent
        mx_size = max(mx_size, size[p]);
        return 1;
	}
    
    void dounite(unordered_map<int,deque<int>>& freq, int i, int t, int& cc) {
                for(auto it = freq[t].begin(); it != freq[t].end(); ++it) {
                    int j = *it;
                    cc -= unite(i, j);
                }
        return;
    }    

public:
    vector<int> groupStrings(vector<string>& words) {
        int n = words.size(); // 1 <= words.length <= 2 * 1e4
        if( n == 1 )
            return {1,1};
        
        // TODO we need to find a quick way to check if a string is 'connected' to another string
        sort(words.begin(),words.end(),[](string& a, string& b){
            return a.size() < b.size();
        });
        
        int nums[n];
        unordered_map<int,deque<int>> freq;
        for(int i = 0; i < n; ++i) {
            int t = 0;
            for(char c: words[i])
                t |= 1<<(c-'a');
            nums[i] = t;
            freq[t].push_front(i);
        }
                        
        int _parent[n]; parent = _parent;
        int _size[n]; size = _size;
        for(int i = 0; i < n; ++i) {
            parent[i] = i;  // initially each node is connected to itself only
            size[i] = 1;    // initially each set has a size of one
        }
        
        mx_size = 1;
        int cc = n;
        
        unordered_set<int> seen;
        
        for(int i = 0; i < n-1; ++i) {
            freq[nums[i]].pop_back();
            if( freq[nums[i]].empty() )
                freq.erase(nums[i]);
            
            auto p = seen.insert(nums[i]);
            if( !p.second )
                continue;
                        
            // unite myself with all the same ones
            for(auto it = freq[nums[i]].begin(); it != freq[nums[i]].end(); ++it) {
                int j = *it;
                cc -= unite(i, j);
            }
            
            // unite myself with all that I have 1 set bit difference
            for(int k = 0; k < 26; ++k) {
                int mask = 1<<k;
                if( nums[i] & mask )
                    continue;
                int t = nums[i] + mask;
                if( freq.find(t) == freq.end() )
                    continue;
                for(auto it = freq[t].begin(); it != freq[t].end(); ++it) {
                    int j = *it;
                    cc -= unite(i, j);
                }
            }
            
            // unite myselft with all that I have 2 set bit difference
            for(int k = 0; k < 26; ++k) {
                if( !(nums[i] & (1<<k)) )
                    continue;
                
                int mask = nums[i];
                mask &= ~(1<<k);
                for(int l = 0; l < 26; ++l) {
                    if( l == k )
                        continue;
                    if( nums[i] & (1<<l) )
                        continue;
                    int t = mask + (1<<l);
                    if( freq.find(t) == freq.end() )
                        continue;
                    for(auto it = freq[t].begin(); it != freq[t].end(); ++it) {
                        int j = *it;
                        cc -= unite(i, j);
                    }
                }
                
            }
            
        }
        
        return {cc,mx_size};
    }
};





// passes 95/97 test cases as of 3/5/2024, then TLE

class Solution {
private:
    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

    int * parent;
    int * size;
    int mx_size;

    // disjoint-set union-find, tracks size of component also
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

	int unite(int p, int c) {
		p = findRoot(p);
		c = findRoot(c);
        if( p == c ) return 0;
		parent[c] = p;
        size[p] += size[c]; // add size of child to parent
        mx_size = max(mx_size, size[p]);
        return 1;
	}

public:
    vector<int> groupStrings(vector<string>& words) {
        int n = words.size(); // 1 <= words.length <= 2 * 1e4
        if( n == 1 )
            return {1,1};

        // TODO we need to find a quick way to check if a string is 'connected' to another string
        sort(words.begin(),words.end(),[](string& a, string& b){
            return a.size() < b.size();
        });

        int nums[n];
        for(int i = 0; i < n; ++i) {
            int t = 0;
            for(char c: words[i])
                t |= 1<<(c-'a');
            nums[i] = t;
        }

        int _parent[n]; parent = _parent;
        int _size[n]; size = _size;
        for(int i = 0; i < n; ++i) {
            parent[i] = i;  // initially each node is connected to itself only
            size[i] = 1;    // initially each set has a size of one
        }

        mx_size = 1;
        int cc = n;

        for(int i = 0; i < n-1; ++i) {
            for(int j = i+1; j < n; ++j) {
                // cout << "analyzing " << words[i] << " " << words[j] << endl;
                if( words[j].size() - words[i].size() > 1 )
                    break;
                int setbits = countSetBits(nums[i] ^ nums[j]);
                if( setbits <= 2 ) {
                    // cout << "unite " << words[i] << " " << words[j] << endl;
                    cc -= unite(i, j);
                    // break;
                }
            }
        }

        return {cc,mx_size};
    }
};
