
// 587. Erect the Fence
// https://leetcode.com/problems/erect-the-fence/
// day 3 September 2021 challenge
// https://leetcode.com/explore/challenge/card/september-leetcoding-challenge-2021/636/week-1-september-1st-september-7th/3962/





// solution approach #1 Jarvis convex hull algorithm
class Solution {
private:
    int orientation(vector<int>& p, vector<int>& q, vector<int>& r) {
        return (q[1] - p[1]) * (r[0] - q[0]) - (q[0] - p[0]) * (r[1] - q[1]);
    }

    bool inBetween(vector<int>& p, vector<int>& i, vector<int>& q) {
        bool a = i[0] >= p[0] && i[0] <= q[0] || i[0] <= p[0] && i[0] >= q[0];
        bool b = i[1] >= p[1] && i[1] <= q[1] || i[1] <= p[1] && i[1] >= q[1];
        return a && b;
    }

public:
    vector<vector<int>> outerTrees(vector<vector<int>>& trees) {
        int n = trees.size();

        if( n < 4 )
            return trees;


        // determine index of left most tree
        sort(trees.begin(),trees.end());
        int left_most = 0;
        for(int i = 0; i < n; ++i)
            if( trees[i][0] < trees[left_most][0])
                left_most = i;


        set<vector<int>> hull;

        int p = left_most;
        while(true) {

            // determine the most counterclockwise relative to p
            int q = (p + 1) % n;
            for(int i = 0; i < n; ++i) {
                if( orientation(trees[p],trees[i],trees[q]) < 0 ) {
                    q = i;
                }
            }


            for( int i = 0; i < n; ++i ) {
                if( i != p && i != q &&
                    orientation(trees[p],trees[i],trees[q]) == 0 &&
                    inBetween(trees[p],trees[i],trees[q]) ) {
                    hull.insert(trees[i]);
                }
            }
            hull.insert(trees[q]);
            p = q;


            // when we arrived at the point where we started, we break
            if( p == left_most )
                break;
        }

        vector<vector<int>> ans(hull.begin(),hull.end());

        return ans;

    }
};
