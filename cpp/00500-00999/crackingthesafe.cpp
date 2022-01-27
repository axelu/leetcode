
// 753. Cracking the Safe
// https://leetcode.com/problems/cracking-the-safe/





// https://jlmartin.ku.edu/courses/math105-F11/Lectures/chapter5-part2.pdf
// https://johnkyon.github.io/2018/08/30/leetcode753/
// Eulerian path Eulerian cycle Hierholzer's Algorithm
class Solution {
private:
    // postorder traversal
    void dfs(string u, int k, string& ans, unordered_set<string>& seen) {
        string v;
        for(int i = 0; i < k; ++i) {
            v = u + (char)(i+'0');
            if( seen.find(v) == seen.end() ) {
                seen.insert(v);
                dfs(v.substr(1),k,ans,seen);
                ans += (i+'0');
            }
        }
    }

public:
    string crackSafe(int n, int k) {
        string ans = "";

        // edge cases
        if( k == 1) {
            for(int i = 0; i < n; ++i) ans += '0';
            return ans;
        }
        if( n == 1 ) {
            for(int i = 0; i < k; ++i) ans += i+'0';
            return ans;
        }


        // idea: we are moving a sliding window of length n over our answer string,
        // and at each step, what is in the sliding window is a new permutation
        // of said n elements from a set of k distinct objects.

        // each node in the graph that we will walk is a permutation. We start with n-1 0's.
        // our first call to dfs will add the 0, to make it n 0's, which is our 1st node.

        int i;
        string start = "";
        for(i = 0; i < n-1; ++i) start += '0';

        unordered_set<string> seen;
        dfs(start,k,ans,seen);
        ans += start;
        return ans;
    }
};
