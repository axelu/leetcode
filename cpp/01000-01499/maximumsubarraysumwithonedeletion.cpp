
// 1186. Maximum Subarray Sum with One Deletion
// https://leetcode.com/problems/maximum-subarray-sum-with-one-deletion/



class Solution {
public:
    int maximumSum(vector<int>& arr) {
        int n = arr.size();
        if( n == 1 )
            return arr[0];
        if( n == 2 )
            return max({arr[0],arr[1],arr[0]+arr[1]});

        // Kadene gives us max subarray ending at i
        // reverse will give us max subarray begining at i

        // forward
	    int e[n]; // max subarray ending at i
        e[0] = arr[0];
	    int global_max = INT_MIN;
	    for(int i = 1; i < n; ++i) {
		    e[i] = max(arr[i], arr[i] + e[i-1]);
		    if(  e[i] > global_max )
			    global_max =  e[i];
	    }

        // backward
        int b[n]; // max subarray beginning at i
        b[n-1] = arr[n-1];
	    for(int i = n-2; i >= 0; --i)
		    b[i] = max(arr[i], arr[i] + b[i+1]);


        // global_max is maximum subarray sum w/o a deletion
        // now lets try with a deletion
        for(int i = 1; i < n-1; ++i)
            global_max = max(global_max,e[i-1]+b[i+1]);

        return global_max;
    }
};
