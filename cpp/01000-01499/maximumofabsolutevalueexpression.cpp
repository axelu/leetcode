
// 1131. Maximum of Absolute Value Expression
// https://leetcode.com/problems/maximum-of-absolute-value-expression/




/* from the hint:   abs(A) + abs(B) = max(A+B, A-B, -A+B, -A-B)
 * let A = abs(arr1[i] - arr1[j])
 * let B = abs(arr2[i] - arr2[j])
 *
 *       abs(A)           +         abs(B)         = max(A+B, A-B, -A+B, -A-B)
 * ----------------------   ----------------------
 * abs(arr1[i] - arr1[j])   abs(arr2[i] - arr2[j]) =
 *                  A                     B                a         b          c        d
 *          -----------------     -----------------
 *  A + B   arr1[i] - arr1[j]  +  arr2[i] - arr2[j]  =>  arr1[i] + arr2[i] - arr1[j] - arr2[j]
 *  A - B   arr1[i] - arr1[j]  - (arr2[i] - arr2[j])
 *          arr1[i] - arr1[j]  -  arr2[i] + arr2[j]  =>  arr1[i] - arr2[i] - arr1[j] + arr2[j]
 * -A + B -(arr1[i] - arr1[j]) +  arr2[i] - arr2[j]
 *         -arr1[i] + arr1[j]  +  arr2[i] - arr2[j]  => -arr1[i] + arr2[i] + arr1[j] - arr2[j]
 * -A - B -(arr1[i] - arr1[j]) - (arr2[i] - arr2[j])
 *         -arr1[i] + arr1[j]  -  arr2[i] + arr2[j]  => -arr1[i] - arr2[i] + arr1[j] + arr2[j]
 *
 * if we take above four cases and bring the |i - j| into it additionally
 * and we assume i < j (i left index, j right index)
 * then we get four equations of which the max is our answer:
 *    int tt1 = ( arr1[i] + arr2[i]) + (-arr1[j] - arr2[j]) + j - i;
 *    int tt2 = ( arr1[i] - arr2[i]) + (-arr1[j] + arr2[j]) + j - i;
 *    int tt3 = (-arr1[i] + arr2[i]) + ( arr1[j] - arr2[j]) + j - i;
 *    int tt4 = (-arr1[i] - arr2[i]) + ( arr1[j] + arr2[j]) + j - i;
 * we can further transform into:
 *    int tt1 = ( arr1[i] + arr2[i]) - i + (-arr1[j] - arr2[j]) + j;
 *    int tt2 = ( arr1[i] - arr2[i]) - i + (-arr1[j] + arr2[j]) + j;
 *    int tt3 = (-arr1[i] + arr2[i]) - i + ( arr1[j] - arr2[j]) + j;
 *    int tt4 = (-arr1[i] - arr2[i]) - i + ( arr1[j] + arr2[j]) + j;
 */
class Solution {
public:
    int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2) {
        int n = arr1.size();  // arr1.size() == arr2.size()

        // return the max of the follwoing value expression
        // |arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|

        int mx = INT_MIN;

        int t[n][4];

        for(int i = 0; i < n; ++i) {
            t[i][0] =  arr1[i] + arr2[i] - i;
            t[i][1] =  arr1[i] - arr2[i] - i;
            t[i][2] = -arr1[i] + arr2[i] - i;
            t[i][3] = -arr1[i] - arr2[i] - i;
        }

        // tt1
        int maxi = t[0][0];
        for(int j = 1; j < n; ++j) {
            int valj = -arr1[j] - arr2[j] + j;
            mx = max(mx, maxi + valj);
            maxi = max(maxi,t[j][0]);
        }

        // tt2
        maxi = t[0][1];
        for(int j = 1; j < n; ++j) {
            int valj = -arr1[j] + arr2[j] + j;
            mx = max(mx, maxi + valj);
            maxi = max(maxi,t[j][1]);
        }

        // tt3
        maxi = t[0][2];
        for(int j = 1; j < n; ++j) {
            int valj = arr1[j] - arr2[j] + j;
            mx = max(mx, maxi + valj);
            maxi = max(maxi,t[j][2]);
        }

        // tt4
        maxi = t[0][3];
        for(int j = 1; j < n; ++j) {
            int valj = arr1[j] + arr2[j] + j;
            mx = max(mx, maxi + valj);
            maxi = max(maxi,t[j][3]);
        }


        return mx;
    }
};
