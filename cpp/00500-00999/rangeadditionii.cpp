
// 598. Range Addition II
// https://leetcode.com/problems/range-addition-ii/



class Solution {
private:
    int maxIdx(int arr[], int n) {
        int mxCnt = arr[n-1];
        int mxIdx = n-1;
        for(int i = n-2; i > 0; --i) {
            arr[i] += arr[i+1];
            if(arr[i] > mxCnt ) {
                mxCnt = arr[i];
                mxIdx = i;
            }
        }
        return mxIdx;
    }

public:
    int maxCount(int m, int n, vector<vector<int>>& ops) {

        int rowCnt[m+1]; memset(rowCnt,0,sizeof rowCnt);
        int colCnt[n+1]; memset(colCnt,0,sizeof colCnt);
        for(int i = 0; i < ops.size(); ++i) {
            ++rowCnt[ops[i][0]];
            ++colCnt[ops[i][1]];
        }

        int mxRowIdx = maxIdx(rowCnt,m+1);
        int mxColIdx = maxIdx(colCnt,n+1);

        return mxRowIdx * mxColIdx;
    }
};
