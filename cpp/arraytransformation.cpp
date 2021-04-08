
// 1243. Array Transformation
// https://leetcode.com/problems/array-transformation/


class Solution {
public:
    vector<int> transformArray(vector<int>& arr) {
        int n = arr.size();
        vector<int> arr2(arr);

        while(true) {
            for(int i = 1; i < n-1; ++i) {
                if( arr[i] < arr[i-1] && arr[i] < arr[i+1] ) arr2[i] = arr[i]+1;
                else if( arr[i] > arr[i-1] && arr[i] > arr[i+1] ) arr2[i] = arr[i]-1;
            }
            if( arr == arr2 ) return arr;
            arr = arr2;
        }

        return {};
    }
};
