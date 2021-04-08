
// 1196. How Many Apples Can You Put into the Basket
// https://leetcode.com/problems/how-many-apples-can-you-put-into-the-basket/





class Solution {
public:
    int maxNumberOfApples(vector<int>& arr) {
        // 1 <= arr.length <= 10^3
        // 1 <= arr[i] <= 10^3
        int n = arr.size();
        if( n <= 5 ) return n;

        sort(arr.begin(),arr.end());
        int i = 0;
        int weight = 0;
        for(; i < n; ++i) {
            weight += arr[i];
            if( weight > 5000 ) break;
        }

        return i;
    }
};
