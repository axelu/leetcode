
// 1738. Find Kth Largest XOR Coordinate Value
// https://leetcode.com/problems/find-kth-largest-xor-coordinate-value/


class Solution {
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
        // value of coordinate (a, b) of the matrix
        // is the XOR of all matrix[i][j]
        // where 0 <= i <= a < m and 0 <= j <= b < n (0-indexed)

        int m = matrix.size();
        int n = matrix[0].size();

        // xor by column
        vector<vector<int>> xorc(m,vector<int>(n));
        xorc[0] = matrix[0];
        for(int i = 1; i < m; ++i)
            for(int j = 0; j < n; ++j)
                xorc[i][j] = xorc[i-1][j] ^ matrix[i][j];

        multiset<int> st;

        // reuse the existing matrix
        // process 1st row
        st.insert(matrix[0][0]);
        for(int j = 1; j < n; ++j) {
            matrix[0][j] = matrix[0][j-1] ^ matrix[0][j];
            st.insert(matrix[0][j]);
        }
        // process the remaining rows
        for(int i = 1; i < m; ++i) {
            matrix[i][0] = xorc[i-1][0] ^ matrix[i][0];
            st.insert(matrix[i][0]);
            for(int j = 1; j < n; ++j) {
                matrix[i][j] = matrix[i][j-1] ^ xorc[i-1][j] ^ matrix[i][j];
                st.insert(matrix[i][j]);
            }
        }

        /*
        for(auto it = st.rbegin(); it != st.rend(); ++it)
            cout << *it << " ";
        cout << endl;
        */

        int i = 0;
        for(auto it = st.rbegin(); it != st.rend(); ++it)
            if( ++i == k )
                return *it;

        return -1;
    }
};
