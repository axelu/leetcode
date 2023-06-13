
// 1073. Adding Two Negabinary Numbers
// https://leetcode.com/problems/adding-two-negabinary-numbers/



/* even indicies are positive, odd indicies are negative
 * even index rules     2^even   2^even  2^even  2^even 2^odd 2^even
 *                         0        0       1                    1
 *                         0        1       0                    1
 * result                  0        1       1       1      1     0
 *
 * odd index rules      2^odd    2^odd   2^odd   2^odd 2^even 2^odd
 *                         0        0       1                    1
 *                         0        1       0                    1
 * result                  0        1       1       1      1     0
 */

class Solution {
public:
    vector<int> addNegabinary(vector<int>& arr1, vector<int>& arr2) {
        int n1 = arr1.size();
        int n2 = arr2.size();

        vector<int> carry{0,0};
        vector<int> result;

        int i1 = n1 - 1;
        int i2 = n2 - 1;

        for(int i = 0; ; ++i) {
            carry.push_back(0);

            int bit1 = 0;
            if( i1 >= 0 )
                bit1 = arr1[i1];
            --i1;

            int bit2 = 0;
            if( i2 >= 0 )
                bit2 = arr2[i2];
            --i2;

            int t = bit1 + bit2 + carry[i];
            if( t == 0 ) {
                result.push_back(0);

            } else if( t == 1 ) {
                result.push_back(1);

            } else if( t == 2 ) {
                // we need to look ahead
                // if there is one bit set, it would be neutralized
                // otherwise we need to carry at i+1 AND i+2
                bool neutralized = false;
                if( carry[i+1] ) {
                    carry[i+1] = 0;
                    neutralized = true;
                }
                if( !neutralized && i1 >= 0 && arr1[i1] ) {
                    arr1[i1] = 0;
                    neutralized = true;
                }
                if( !neutralized && i2 >= 0 && arr2[i2] ) {
                    arr2[i2] = 0;
                    neutralized = true;
                }
                if( !neutralized ) {
                    carry[i+1] = 1;
                    carry[i+2] = 1;
                }
                result.push_back(0);

            } else { // t == 3
                // we need to look ahead
                // if there is one bit set, it would be neutralized
                // otherwise we need to carry at i+1 AND i+2
                bool neutralized = false;
                if( carry[i+1] ) {
                    carry[i+1] = 0;
                    neutralized = true;
                }
                if( !neutralized && i1 >= 0 && arr1[i1] ) {
                    arr1[i1] = 0;
                    neutralized = true;
                }
                if( !neutralized && i2 >= 0 && arr2[i2] ) {
                    arr2[i2] = 0;
                    neutralized = true;
                }
                if( !neutralized ) {
                    carry[i+1] = 1;
                    carry[i+2] = 1;
                }
                result.push_back(1);
            }

            if( i1 < 0 && i2 < 0 && carry[i+1] == 0 && carry[i+2] == 0 )
                break;
        }

        // edge case
        while( result.size() > 1 && result.back() == 0 )
            result.pop_back();

        reverse(result.begin(),result.end());

        return result;
    }
};
