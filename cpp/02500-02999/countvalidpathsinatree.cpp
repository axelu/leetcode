
// 2867. Count Valid Paths in a Tree
// https://leetcode.com/problems/count-valid-paths-in-a-tree/





// initialize ones
class T {
public:
    const static bool* primes;
};

bool* SieveOfEratosthenes(int n) {
    bool* arr = new bool[n+1]();
    for(int i = 2; i <= n; ++i)
        arr[i] = true;
    for(int p = 2; p * p <= n; ++p) {
        if( arr[p] == true ) {
            // update all multiples of p greater than or
            // equal to the square of it
            // numbers which are multiple of p and are less than p^2 are
            // already been marked.
            for(int i = p * p; i <= n; i += p)
                arr[i] = false;
        }
    }
    return arr;
}
const bool* T::primes = SieveOfEratosthenes(100000);


class Solution {
private:
    long long ans;

    pair<long long,long long> dfs(vector<int> g[], int u, int src) {
        // returns pair.first:  nbr of path starting from u to child nodes containing no prime and
        //         pair.second: nbr of path starting from u to child nodes containing one prime


        // for each child, let us collect
        // the number of paths starting from child that do NOT contain a prime and
        // the number of paths starting from child that do contain one prime
        vector<long long> paths_no_prime;
        vector<long long> paths_one_prime;
        for(int v: g[u]) {
            if( v == src )
                continue;
            auto const[p0,p1] = dfs(g,v,u);
            paths_no_prime.push_back(p0);
            paths_one_prime.push_back(p1);
        }

        // sum the paths from our children
        long long sum_p0 = accumulate(paths_no_prime.begin(),paths_no_prime.end(),0L);
        long long sum_p1 = accumulate(paths_one_prime.begin(),paths_one_prime.end(),0L);

        long long ret_p0, ret_p1;

        if( T::primes[u] ) {
            // current node is a prime
            // all paths ending at our node u will have at least 1 prime, as the current node is a prime
            ret_p0 = 0LL;
            // all paths from our children with 0 primes ending at our node u, will have one prime
            ret_p1 = sum_p0 + 1LL;

            // update our overall answer

            // any child path with no prime ending at our node u is a valid path, as the current node is a prime
            ans += sum_p0;

            // additionally, any path from some node in our subtree -> u -> some other node in our subtree
            // that traverses u, meaning u is the lowest common ancestor LCA, we can combine
            // any child path with no prime
            long long t = 0;
            for(auto a: paths_no_prime)
                t += (a * (sum_p0 - a)); // combine two no prime paths from different children
            // /2 don't double count, because when we combine child x with y,
            // we will come around again when we get to y and combine it with x
            ans += t/2LL;

        } else {
            // current node is NOT a prime
            // all paths ending at our node u will have no prime, if the child path had no prime
            ret_p0 = sum_p0 + 1LL;
            // all paths ending at our node u will have one prime, if the the child path contained one prime
            ret_p1 = sum_p1;

            // update our overall answer

            // child path with one prime ending at our node u is a valid path, as the current node is NOT a prime
            ans += sum_p1;

            // additionally, any path from some node in our subtree -> u -> some other node in our subtree
            // that traverses u, meaning u is the lowest common ancestor LCA, we can combine
            // any child path with one prime with any child path with no prime
            long long t = 0LL;
            int p_sz = paths_no_prime.size(); // = paths_one_prime.size()
            for(int i = 0; i < p_sz; ++i) {
                long long t0 = paths_no_prime[i];
                long long t1 = paths_one_prime[i];
                t += (t0 * (sum_p1 - t1)) + (t1 * (sum_p0 - t0));
            }
            // /2 see above, don't double count
            ans += t/2LL;
        }

        return {ret_p0,ret_p1};
    }

public:
    long long countPaths(int n, vector<vector<int>>& edges) {
        // undirected tree with n nodes labeled from 1 to n
        // edges.length == n - 1

        vector<int> g[n+1];
        for(auto& edge: edges) {
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
        }

        ans = 0LL;

        // arbitrarily root the graph at node 1
        dfs(g,1,-1);

        return ans;
    }
};
