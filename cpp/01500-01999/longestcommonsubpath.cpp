
// 1923. Longest Common Subpath
// https://leetcode.com/problems/longest-common-subpath/



class Solution {
private:
    bool is_match(vector<int>& a, int i, vector<int>& b, int j, int l) {
        for(int k = 0; k < l; ++k) {
            if( a[i] != b[j] )
                return false;
            ++i;
            ++j;
        }
        return true;
    }

    bool solve(vector<vector<int>>& paths, int l) {
        // Rabin-Karp Algorithm
        // rolling hash

        long base = 100001;
        long mod = 1000000007;

        // hash, indicies at which a path of lenght l with the given hash starts
        unordered_map<int,vector<int>> hs;
        long hash = 0;
        long d = 1;     // power of base

        // calculate all hashes of length l for the 1st path in paths
        for(int j = 0; j < paths[0].size(); ++j) {
            hash = (hash * base + paths[0][j]) % mod;

            if( j >= l ) // remove the front element from the hash
                hash = (mod + hash - d * paths[0][j-l] % mod) % mod;
            else
                d = d * base % mod;

            if( j >= l-1 )
                hs[hash].push_back(j+1-l);
        }

        // calculate hashes of length l for each remaining path and see if they match the hashes found
        for(int i = 1; i < paths.size(); ++i) {
            // we will only carry forward the subpaths that we matched
            unordered_map<int,vector<int>> hs_new;

            hash = 0;
            d = 1;
            for(int j = 0; j < paths[i].size(); ++j) {
                hash = (hash * base + paths[i][j]) % mod;

                if( j >= l )
                    hash = (mod + hash - d * paths[i][j-l] % mod) % mod;
                else
                    d = d * base % mod;

                if( j >= l-1 && hs.count(hash) ) {
                    // we have a potential match
                    // we need to check if subpath matches (to exclude collisions)

                    int k = j+1-l;       // starting position in our current path
                    // hs_new[hash].push_back(k);

                    for(int s: hs[hash]) // starting position of the same hash in paths[i-1]
                        if( equal(paths[i-1].begin() + s, paths[i-1].begin() + s + l, paths[i].begin() + k) ) {
                        // if( is_match(paths[i-1],s,paths[i],k,l)) {
                            hs_new[hash].push_back(k);
                            break;
                        }

                }
            }
            if( hs_new.empty() )
                return false;
            swap(hs,hs_new);
        }

        return true;
    }

public:
    int longestCommonSubpath(int n, vector<vector<int>>& paths) {
        // our answer cannot be longer than the shortest path given
        // our answer is between [0,min(paths[i].size())] inclusive for all 0 <= i < path.size()

        int s = 0;
        int e = 100001;

        for(auto& v: paths)
            e = min(e,(int)v.size());

        int mid;
        while(s <= e) {
            mid = s + ((e-s)/2);
            bool f = solve(paths,mid);
            if( f )
                s = mid + 1;
            else
                e = mid - 1;
        }

        return e;

    }
};
