
// 973. K Closest Points to Origin
// https://leetcode.com/problems/k-closest-points-to-origin/




class Solution {
private:
    struct T {
        int distToZero;
        vector<int> p;
        T(int d, vector<int> P) : distToZero(d), p(P) {}
    };
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        auto cmp = [](const T* a, const T* b){return a->distToZero < b->distToZero;};
        priority_queue<T*,vector<T*>,decltype(cmp)> pq(cmp);
        int x,y,dist;
        T* t;
        for(int i = points.size()-1; i >= 0 ; --i) {
            x = points[i][0];
            y = points[i][1];
            dist = x*x+y*y; // squared Euclidean distance
            t = new T(dist,points[i]);
            pq.push(t);
            if( pq.size() > K ) pq.pop();
        }

        vector<vector<int>> ans(K);
        int i = 0;
        while( !pq.empty() ) {
            ans[i] = pq.top()->p;
            pq.pop();
            ++i;
        }

        return ans;
    }
};
