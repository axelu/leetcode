
// 1424. Diagonal Traverse II
// https://leetcode.com/problems/diagonal-traverse-ii/




class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        int m = nums.size(); // rows


        // auto cmp = [nums](const array<int,2>& a, const array<int,2>& b) {
        auto cmp = [](const array<int,2>& a, const array<int,2>& b) {
            // cout << "cmp a " << nums[a[0]][a[1]] << " b " << nums[b[0]][b[1]] << endl;


            if( a[0] == b[0] ) { // same row
                if( a[1] < b[1] )
                    return true;
            }

            if( a[1] == b[1] ) { // same colum
                if( a[0] < b[0] )
                    return true;
            }

            if( b[0] > a[0] && b[1] > a[1] )
                return true;

            if( a[0] > b[0] && b[1] > a[1] ) {
                int colDiff = b[1]-a[1];
                int rowDiff = a[0]-b[0];
                if( colDiff >= rowDiff )
                    return true;
            }

            if( a[0] < b[0] && a[1] > b[1] ) {
                int colDiff = a[1]-b[1];
                int rowDiff = b[0]-a[0];
                if( rowDiff > colDiff )
                    return true;
            }

            // cout << "false" << endl;
            return false;
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq(cmp);

        int i,n;
        for(i = 0; i < m; ++i) {     // row
            n = nums[i].size();
            for(int j = 0; j < n; ++j) // col
                pq.push({i,j});
        }

        vector<int> ans(pq.size());
        i = pq.size()-1;
        while(!pq.empty()) {
            ans[i] = nums[pq.top()[0]][pq.top()[1]];
            pq.pop();
            --i;
        }

        return ans;
    }
};
