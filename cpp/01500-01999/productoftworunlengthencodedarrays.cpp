
// 1868. Product of Two Run-Length Encoded Arrays
// https://leetcode.com/problems/product-of-two-run-length-encoded-arrays/




/*
 * example
 * 1,1,1,2,2,2,2,2
 * 3,3,5,5,6,7,7,9
*/

class Solution {
public:
    vector<vector<int>> findRLEArray(vector<vector<int>>& encoded1, vector<vector<int>>& encoded2) {
        // expanded size of encoded1 == expanded size of encoded1
        int n1 = encoded1.size();
        int n2 = encoded2.size();

        // brute force approach would be:
        // 1 expand both encoded1 and encoded2 into the full arrays nums1 and nums2 respectively.
        // 2 create a new array prodNums of length nums1.length and set prodNums[i] = nums1[i] * nums2[i].
        // 3 compress prodNums into a run-length encoded array and return it.


        vector<vector<int>> ans;

        int i = 0, j = 0;           // index in encoded1 respectively in encoded2
        int i_rem = encoded1[0][1]; // remainder
        int j_rem = encoded2[0][1]; // remainder
        while( true ) {

            int prodNums = encoded1[i][0] * encoded2[j][0];
            if( i_rem < j_rem) {
                if( !ans.empty() && ans.back()[0] == prodNums )
                    ans.back()[1] += i_rem;
                else
                    ans.push_back({prodNums,i_rem});
                j_rem -= i_rem;
                ++i;
                i_rem = encoded1[i][1];
            } else if( j_rem < i_rem ) {
                if( !ans.empty() && ans.back()[0] == prodNums )
                    ans.back()[1] += j_rem;
                else
                    ans.push_back({prodNums,j_rem});
                i_rem -= j_rem;
                ++j;
                j_rem = encoded2[j][1];
            } else {
                // j_rem == i_rem
                if( !ans.empty() && ans.back()[0] == prodNums )
                    ans.back()[1] += j_rem;
                else
                    ans.push_back({prodNums,j_rem});
                ++i;
                if( i == n1 )
                    break;
                i_rem = encoded1[i][1];
                ++j;
                j_rem = encoded2[j][1];
            }
        }

        return ans;
    }
};
