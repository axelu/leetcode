
// 1494. Parallel Courses II
// https://leetcode.com/problems/parallel-courses-ii/





class Solution {
private:
    // debug
    void printPrereq(int cntPrereq[], int n) {
        cout << "cntPrereq  ";
        for(int i = 1; i <= n; ++i)
           cout << i << ":" << cntPrereq[i] << " ";
        cout << endl;
    }

    // debug
    void printBitmask(int x, int n) {
        for(int i = 0; i < n; ++i) {
            cout << i+1 << ":";
            if( (x >> i) & 1 ) cout << "1 ";
            else cout << "0 ";
        }
        cout << endl;
    }

    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

    int mem[32768]; // 2^15

    pair<int,int> couldTake(vector<int> g[], int n, int taken) {
        // return bitmask where the bits for the courses we could take are set
        // we will also return the number of courses we could take

        // get prerequisite count for each course based on courses taken
        int cntPrereq[n]; memset(cntPrereq,0,sizeof cntPrereq);
        for(int i = 0; i < n; ++i) {
            if( (taken >> i) & 1 ) continue;
            for(int j = 0; j < g[i].size(); ++j)
                ++cntPrereq[g[i][j]];
        }

        int cnt = 0, res = 0;
        for(int i = 0; i < n; ++i) {
            if( cntPrereq[i] == 0 && !((taken >> i) & 1) ) {
                ++cnt;
                res |= 1 << i;
            }
        }

        return make_pair(cnt,res);
    }

    int dp(vector<int> g[], int n, int k, int taken) {
        // taken is a bitmask indidacting if we took a given course
        // e.g. right most bit indicates if we took course 0

        // have we taken all courses?
        if( taken == ((1 << n) - 1) ) return 0;

        if( mem[taken] != -1 ) return mem[taken];

        // get courses we could take
        pair<int,int> could = couldTake(g,n,taken);
        int couldTakeCnt  = could.first;
        int couldTakeMask = could.second;

        // there is a max of 15 courses and we could at least take 1 course per semester
        int res = 15;

        if( couldTakeCnt <= k ) {
            // the number of courses we could take is less or equal the number of courses
            // we are allowed to take in a given semester, so we will take them all (greedy)
            res = 1 + dp(g,n,k,taken|couldTakeMask);
        } else {
            // the number of courses we could take is greater than the number of courses
            // we are allowed to take in a given semester, so which combination of courses
            // should we take?

            int take;
            for(int i = couldTakeMask; i > 0; --i) {
                take = i & couldTakeMask;
                // how many courses are we taking in this combination?
                // greedily we want it to be the max number allowed
                if( countSetBits(take) != k ) continue;
                res = min(res,1 + dp(g,n,k,taken|take));
            }

        }
        return mem[taken] = res;
    }

public:
    int minNumberOfSemesters(int n, vector<vector<int>>& dependencies, int k) {
        // graph with n vertices from 1 to n, 1 <= n <= 15
        // graph is a directed acyclic graph (DAG) with one or more connected components
        // no connected component has a cycle

        // edge case: no dependencies
        if( dependencies.empty() )
            return n%k == 0 ? n/k : n/k+1;

        // graph
        // we will zero index the graph!
        vector<int> g[15];
        for(int i = 0; i < dependencies.size(); ++i)
            g[dependencies[i][0]-1].push_back(dependencies[i][1]-1);

        memset(mem,-1,sizeof mem);
        return dp(g,n,k,0);
    }
};
