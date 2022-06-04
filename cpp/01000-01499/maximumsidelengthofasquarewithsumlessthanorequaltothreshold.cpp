
// 1292. Maximum Side Length of a Square with Sum Less than or Equal to Threshold
// https://leetcode.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/



class Solution {
private:
    int **ps;

    // binary search
    int search(int i, int j, int s, int e, int threshold) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        int sum = ps[i+mid][j+mid] - ps[i][j+mid] - ps[i+mid][j] + ps[i][j];
        if( sum <= threshold ) {
            // can we do better?
            int t = search(i,j,mid+1,e,threshold);
            return t != -1 ? t : mid;
        } else {
            return search(i,j,s,mid-1,threshold);
        }
    }

public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int m = mat.size();    // rows
        int n = mat[0].size(); // cols

        int i,j,k;

        ps = new int *[m+1]; // 2D prefix sum
        for(i = 0; i <= m; ++i) {
            ps[i] = new int[n+1];
            for(j = 0; j <= n; ++j) {
                if( i == 0 || j == 0 ) {
                    ps[i][j] = 0;
                    continue;
                }
                ps[i][j] = ps[i][j-1] + ps[i-1][j] - ps[i-1][j-1] + mat[i-1][j-1];
            }
        }

        int ans = 0;
        for(i = 0; i < m; ++i) {
            for(j = 0; j < n; ++j ) {
                k = min(m-i,n-j);
                ans = max(ans,search(i,j,1,k,threshold));
            }
        }

        return ans;
    }
};
