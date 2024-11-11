
// 3224. Minimum Array Changes to Make Differences Equal
// https://leetcode.com/problems/minimum-array-changes-to-make-differences-equal/



/* 0123456789
 * xxxxxx  n = 6
 * *       i = 0 -> n - i - 1 -> 6 - 0 - 1 = 5
 *  *      i = 1 -> n - i - 1 -> 6 - 1 - 1 = 4
 *   *     i = 2 -> n - i - 1 -> 6 - 2 - 1 = 3
 *    *    i = 3 -> n - i - 1 -> 6 - 3 - 1 = 2
 *     *   i = 4 -> n - i - 1 -> 6 - 4 - 1 = 1
 *      *  i = 5 -> n - i - 1 -> 6 - 5 - 1 = 0
 * example 1 k = 4
 * initial 1 0 1 2 4 3
 * final   1 2 1 3 4 3
 *           -   -     we replaced pos 1 and pos 3 for the cost of 2 ops
 *         3 4 3 1 2 1 final backwards
 *  X      2 2 2 2 2 2
 *
 * case k = 5
 * nums[i]  nums[n - i - 1]
 *    25         10         initial diff 15                                   cost 0 ops
 * we can change 10 to 0, 1, 2, 3, 4, 5 getting diffs 25, 24, 23, 22, 21, 20  cost 1 ops
 * we can change 25 to 0, 1, 2, 3, 4, 5 getting diffs 10,  9,  8,  7,  6,  5  cost 1 ops
 * we can change both 10 and 25 getting diffs          0,  1,  2,  3,  4,  5  cost 2 ops
 * Note that we should only mark the 5 once with the cost of 1
 * Note that we cannot reach 19 - 11 inclusive
 *
 * example 1 k = 4
 * initial 1 0 1 2 4 3
 * ->      3 4 2
 *              ------ we fold nums and only worry about that
 * diff    2 4 1
 * matrix diff/pos value cost
 *          pos
 *    diff 0 1 2   sum
 *      0  1 1 1   3
 *      1  1 1 0   2
 *      2  0 1 1   2
 *      3  1 1 1   3
 *      4  2 0 2   4         1 0 1 2 4 3
 * possible solutions: X = 1 1 0 1 2 1 2
 *                     X = 2 1 2 1 3 4 3
 *
 * we are looking for the number X that is reachable in all positiions with the minimal cast
 */
class Solution {
private:
    void add(int idx, int val, int bit[], int n) {
        for (++idx; idx < n; idx += idx & -idx)
            bit[idx] += val;
    }

    void range_add(int l, int r, int val, int bit[], int n) {
        add(l, val, bit, n);
        add(r + 1, -val, bit, n);
    }

    int point_query(int idx, int bit[]) {
        int ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            ret += bit[idx];
        return ret;
    }

    void get_ranges(int k, int i, int d, vector<vector<int>>& ranges) {
        int l, r;
        if( k <= i ) {
            // i-k ... i
            l = i - k;
            r = i;
        } else { // k > i
            if( k <= 2 * i ) {
                // 0 ... i
                l = 0;
                r = i;
            } else {
                // 0 ... k - i
                l = 0;
                r = k - i;
            }
        }

        if( l == r ) {
            if( d != r )
                ranges.push_back({l, r}); // l == r
        } else if( r - l == 1 ) {
            if( d == l ) {
                ranges.push_back({r, r});
            } else if( d == r ) {
                ranges.push_back({l, l});
            } else {
                ranges.push_back({l, r});
            }
        } else {
            if( d == l ) {
                ranges.push_back({l+1, r});
            } else if( d == r ) {
                ranges.push_back({l, r-1});
            } else {
                // d is somewhere in the middle
                ranges.push_back({l, d-1});
                ranges.push_back({d+1, r});
            }
        }

        return;
    }

    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        size_t n = intervals.size();
        if( n <= 1 ) return intervals;

        sort(begin(intervals),end(intervals));

        vector<vector<int>> r;
        r.push_back(intervals[0]);
        int i = 0;
        for(int j = 1; j < n; ++j) {
            if( intervals[j].front() > r[i].back() ) {
                r.push_back(intervals[j]);
                ++i;
            } else if( intervals[j].front() == r[i].back() ) {
                r[i].back() = intervals[j].back();
            } else if( intervals[j].back() > r[i].back() ) {
                // r[i].front() <= intervals[j].front() < r[i].back()
                r[i].back() = intervals[j].back();
            }
        }
        return r;
    }


public:
    int minChanges(vector<int>& nums, int k) {
        int n = nums.size();

        // 0 <= nums[i] <= k <= 1e5
        // consider figuring out max possible diff to not have to cover up to 1e5
        int cnt[100002]; memset(cnt, 0, sizeof cnt); // binary indexed tree fenwick tree
        int cst[100002]; memset(cst, 0, sizeof cst); // binary indexed tree fenwick tree

        for(int i = 0; i < n/2; ++i) {
            int a = nums[i];
            int b = nums[n - i - 1];

            if( b > a )
                swap(a, b);

            // the original diff aka X: cost 0 op
            int d = a - b; // cout << "i " << i << " diff " << d << endl;
            range_add(d, d, 1, cnt, 100002);

            vector<vector<int>> ranges;

            // which Xs can we achieve if we change b to [0,k]? cost 1 op
            // consider simplifying: just get ranges and add to cost, then subtract 1 for d
            get_ranges(k, a, d, ranges);

            // which Xs can we achieve if we change a to [0,k]? cost 1 op
            get_ranges(k, b, d, ranges);

            ranges = merge(ranges);
            for(auto& v: ranges) {
                range_add(v[0], v[1], 1, cnt, 100002);
                range_add(v[0], v[1], 1, cst, 100002); // cost 1 op
            }

            // which Xs can we achieve if we change a and b to [0,k]? cost 2 ops
            // 0 <= X <= k
            // we need to count ONLY what has not been covered so far
            vector<vector<int>> op2;
            for(int j = 0; j < ranges.size(); ++j) {
                if( j == 0 ) {
                    if( ranges[0][0] > 0 ) {
                        op2.push_back({0, min(k, ranges[0][0] - 1)});
                    }

                }
                if( j > 0 && j < ranges.size() - 1) {
                    if( ranges[j-1][1] < k ) {
                        op2.push_back({ranges[j-1][1]+1, min(k, ranges[j][0] - 1)});
                    }

                }
                if( j == ranges.size() - 1 ) {
                    if( ranges[j][1] < k ) {
                        op2.push_back({ranges[j][1]+1, k});
                    }
                }
            }
            // don't doublecount our original diff d
            vector<vector<int>> op2f;
            for(auto it = op2.begin(); it != op2.end(); ++it) {
                int l = it->front();
                int r = it->back();
                if( l > d || r < d ) {
                    op2f.push_back({l, r});
                } else {
                    if( r - l == 0 ) {
                        // do nothing
                    } else if( r - l == 1 ) {
                        if( l == d )
                            op2f.push_back({r, r});
                        else
                            op2f.push_back({l, l});
                    } else {
                        op2f.push_back({l, d-1});
                        op2f.push_back({d+1, r});
                    }
                }
            }
            for(auto& v: op2f) {
                range_add(v[0], v[1], 1, cnt, 100002);
                range_add(v[0], v[1], 2, cst, 100002); // cost 2 op
            }
        }

        int ans = 2 * n; // worst case

        for(int X = 0; X <= 100000; ++X) {
            // could we make X n times? meaning at each position
            int freq = point_query(X, cnt);
            // cout << "X " << X << " count " << freq << endl;
            if( freq < n/2 )
                continue;

            int cost = point_query(X, cst);
            ans = min(ans,cost);
        }

        return ans;
    }
};
