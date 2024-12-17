
// 3385. Minimum Time to Break Locks II
// https://leetcode.com/problems/minimum-time-to-break-locks-ii/






/* hint states to use Hungarian algorithm
 * https://www.thinkautonomous.ai/blog/hungarian-algorithm/
 *
 * it is an assignment problem, the classical example uses jobs and workers
 * and the goal is to execute all jobs with minimal cost
 * in our example to goal is to minimize the time, that makes time our cost
 * think about it as the time we have to wait to open a lock in a given round,
 * knowing that our strength factor equals the round we are in
 * example: let the strength be needed to break a lock be 3
 *          then for us to break the lock in round 1, we have to wait 3 minutes
 *              X = 1 -> (strength be needed to break a lock / X) -> 3/1 = 3
 *          for us to break the lock in round 2, we have to wait 2 minutes
 *              X = 2 -> 3/2 ceiling = 2 (ceiling, because our energy has to be greater equal)
 *          and so on
 * the locks are our jobs
 * each round is a worker
 * with that we can construct our n x n cost matrix
 * example 1 [3,4,1]
 * cost matrix
 *                 locks = jobs
 *                 3 4 1
 * worker = round  2 2 1
 *                 1 2 1
 * if we follow the steps outlined in above web link
 * we end up with with the cost matrix as follows
 *                 2 2 0
 *                 1 0 0
 *                 0 0 0
 * we start assigment with the row with only one 0, so lock 1 in round 3
 * then, because round 3 is taken, row 2 has one 0 only, so lock 2 in round 2
 * that leaves us with lock 3 in round 1
 *
 * implementation https://cp-algorithms.com/graph/hungarian-algorithm.html
 */
class Solution {
private:
    int hungarian(vector<vector<int>>& A) {
        // matrix A comes with a dummy row zero and a dummy column 0

        int n = A.size()-1;
        int m = A[0].size()-1;
        int INF = 1000001; // based on problem constraint

        vector<int> u (n+1), v (m+1), p (m+1), way (m+1);
        for (int i=1; i<=n; ++i) {
            p[0] = i;
            int j0 = 0;
            vector<int> minv (m+1, INF);
            vector<bool> used (m+1, false);
            do {
                used[j0] = true;
                int i0 = p[j0],  delta = INF,  j1;
                for (int j=1; j<=m; ++j)
                    if (!used[j]) {
                        int cur = A[i0][j]-u[i0]-v[j];
                        if (cur < minv[j])
                            minv[j] = cur,  way[j] = j0;
                        if (minv[j] < delta)
                            delta = minv[j],  j1 = j;
                    }
                for (int j=0; j<=m; ++j)
                    if (used[j])
                        u[p[j]] += delta,  v[j] -= delta;
                    else
                        minv[j] -= delta;
                j0 = j1;
            } while (p[j0] != 0);
            do {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }

        // see above link on cp-algoritm on getting answer for each worker
        // and overall cost

        return -v[0];
    }
public:
    int findMinimumTime(vector<int>& strength) {
        int n = strength.size();

        // construct the cost matrix,
        // 1-based, so dummy row zero and dummy column zero

        vector<vector<int>> cost_matrix(n+1,vector<int>(n+1,0));
        for(int worker = 1; worker <= n; ++worker) {
            for(int job = 1; job <= n; ++job) {
                cost_matrix[worker][job] = ceil(strength[job-1]/(worker*1.0));
            }
        }
        /*
        // debug
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j)
                cout << cost_matrix[i][j] << " ";
            cout << endl;
        }
        */

        return hungarian(cost_matrix);
    }
};
