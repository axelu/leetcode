
// 1605. Find Valid Matrix Given Row and Column Sums
// https://leetcode.com/problems/find-valid-matrix-given-row-and-column-sums/



class Solution {
private:
    int findMinGreaterZero(vector<int>& v, size_t n) {
        int pos = -1;
        int mn = 100000001;
        int ii;
        for(int i = 0; i < n; ++i) {
            ii = v[i];
            if( ii > 0 && ii < mn ) {
                mn = v[i];
                pos = i;
            }
        }
        return pos;
    }
public:
    vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum) {
        auto n = rowSum.size();
        auto m = colSum.size();

        vector<vector<int>> r(n, vector<int>(m,0));
        int rowMinIdx,colMinIdx,x;
        while(true) {
            rowMinIdx = findMinGreaterZero(rowSum,n);
            if( rowMinIdx == -1 ) break; // this works because of sum(rows) == sum(columns)
            colMinIdx = findMinGreaterZero(colSum,m);
            x = rowSum[rowMinIdx] < colSum[colMinIdx] ? rowSum[rowMinIdx] : colSum[colMinIdx];
            r[rowMinIdx][colMinIdx] = x;
            rowSum[rowMinIdx] -= x;
            colSum[colMinIdx] -= x;
        }
        return r;
    }
};
