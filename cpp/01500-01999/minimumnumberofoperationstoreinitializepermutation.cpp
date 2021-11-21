
// 1806. Minimum Number of Operations to Reinitialize a Permutation
// https://leetcode.com/problems/minimum-number-of-operations-to-reinitialize-a-permutation/




class Solution {
private:
    bool isInitialState(int arr[], int n) {
        for(int i = 0; i < n; ++i)
            if( arr[i] != i ) return false;
        return true;
    }
public:
    int reinitializePermutation(int n) {
        int arr1[n];
        int arr2[n];
        int i;
        for(i = 0; i < n; ++i) {
            arr1[i] = i%2 == 0 ? i/2 : n/2+(i-1)/2;
            arr2[i] = i;
        }

        int ans = 1;

        int * perm = arr1;
        int * arr  = arr2;
        while( !isInitialState(perm,n) ) {
           for(i = 0; i < n; ++i)
               arr[i] = i%2 == 0 ? perm[i/2] : perm[n/2+(i-1)/2];
            swap(perm,arr);
            ++ans;
        }
        return ans;
    }
};
