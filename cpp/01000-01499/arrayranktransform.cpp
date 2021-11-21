
// 1331. Rank Transform of an Array
// https://leetcode.com/problems/rank-transform-of-an-array/





class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        /*
        auto n = arr.size();
        if( n == 0 ) return {};
        if( n == 1 ) return {1};

        vector<vector<int>> a(n, vector<int>(2));
        for(int i = 0; i < n; ++i)
            a[i] = {arr[i],i};
        sort(begin(a),end(a));

        vector<int> r(n);
        int rank = 1;
        r[a[0][1]] = rank;
        for(int i = 1; i < n; ++i) {
            if( a[i-1][0] != a[i][0] ) ++rank;
            r[a[i][1]] = rank;
        }

        return r;
        */

        auto n = arr.size();
        if( n == 0 ) return {};
        if( n == 1 ) return {1};

        vector<array<int,2>> a;
        a.reserve(n);
        for(int i = 0; i < n; ++i)
            a.push_back({arr[i],i});
        make_heap(begin(a),end(a),greater<array<int,2>>()); // min heap

        vector<int> r(n);
        int rank = 1;

        // get 1st element
        pop_heap(begin(a),end(a),greater<array<int,2>>());  // move top element to back
        auto p = a.back();                                  // get 'former' top element
        a.pop_back();                                       // remove 'former' top element
        r[p[1]] = rank;

        int f = p[0]; // remember prior element
        for(int i = 1; i < n; ++i) {
            pop_heap(begin(a),end(a),greater<array<int,2>>());
            p = a.back();
            a.pop_back();
            if( f != p[0] ) ++rank;
            r[p[1]] = rank;
            f = p[0];
        }

        return r;
    }
};
