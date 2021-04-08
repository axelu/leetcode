
// 498. Diagonal Traverse
// https://leetcode.com/problems/diagonal-traverse/
// day 26 December 2020 challenge
// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/572/week-4-december-22nd-december-28th/3580/


class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        size_t M = matrix.size();
        if( M == 0 ) return {};
        size_t N = matrix[0].size();

        vector<int> ans(M*N);

        queue<array<int,2>> q;
        q.push({0,0});
        int idx = 0, n;
        bool forward = true;
        array<int,2> qe; // row,column
        while(!q.empty()) {
            n = q.size();
            for(int i = 0; i < n; ++i) {
                qe = q.front();
                q.pop();

                int pos = idx + (forward ? n - i - 1 : i);
                ans[pos] = matrix[qe[0]][qe[1]];

                // cell to the right
                if( qe[1] < N - 1 )
                    q.push({qe[0],qe[1]+1});
                // cell bellow
                if( qe[1] == 0 && qe[0] < M - 1 )
                    q.push({qe[0]+1,qe[1]});
            }

            idx += n;
            forward = !forward; // change direction
        }

        return ans;
    }
};
