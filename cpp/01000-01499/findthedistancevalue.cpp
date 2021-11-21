
// 1385. Find the Distance Value Between Two Arrays
// https://leetcode.com/problems/find-the-distance-value-between-two-arrays/



class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        sort(begin(arr2),end(arr2));

        auto n = arr1.size();
        auto m = arr2.size();
        int a,j;
        int r = n; // init result
        for(int i = 0; i < n; ++i) {
            a = arr1[i];
            j = 0;
            for(; j < m; ++j)
                if( abs(a-arr2[j]) <= d ) {
                    --r;
                    break; // bail because we sorted arr2
                }
        }

        return r;
    }
};
