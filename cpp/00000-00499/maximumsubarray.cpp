#include <iostream>
#include <cassert>

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// 53. Maximum Subarray
// https://leetcode.com/problems/maximum-subarray/
// Divide and Conquer approach 
// help at https://www.geeksforgeeks.org/maximum-subarray-sum-using-divide-and-conquer-algorithm/
// Kadane’s Algorithm
// https://medium.com/@rsinghal757/kadanes-algorithm-dynamic-programming-how-and-why-does-it-work-3fd8849ed73d


class Solution {
private:
    int maxSubArray(vector<int>::iterator first, vector<int>::iterator last) {

        if ( first == last ) return *first;

        // divide
        auto middle = first + (( last - first ) / 2);

        // conquer left side, right side and cross
        return max({maxSubArray(first, middle),
                    maxSubArray(middle + 1, last),
                    maxCross(first, middle, last)});
    }

    int maxCross(vector<int>::iterator first, vector<int>::iterator middle, 
            vector<int>::iterator last) {
  
        // to the left from the middle!!!
        int tmp = 0;
        int lsum = INT_MIN;
        for (auto it = middle; it >= first; --it) {
            tmp += *it;
            if (tmp > lsum) lsum = tmp;
        }

        // to the right from the middle!!!
        tmp = 0;
        int rsum = INT_MIN;
        for (auto it = middle + 1; it <= last; ++it) {
            tmp += *it;
            if (tmp > rsum) rsum = tmp;
        }

        return max({lsum + rsum, lsum, rsum});
    }
    
public:
    int maxSubArray(vector<int>& nums) {
        /*
        // Kadane’s Algorithm	
        
	    int n = nums.size();
	    int local_max = 0;
	    int global_max = INT_MIN;

	    for(int i = 0; i < n; ++i) {
		    local_max = max(nums[i], nums[i] + local_max);
		    if( local_max > global_max )
			    global_max = local_max;
	    }
	
	    return global_max;
        */
        
        
        // divide and conquer
        
        if ( nums.empty() ) return INT_MIN;
        if ( nums.size() == 1 ) return nums[0];

        return maxSubArray(nums.begin(), nums.end() - 1);
        
    }
};

int main() {

    Solution s;

    vector<int> v;

    v = {-2,1,-3,4,-1,2,1,-5,4};
    cout << s.maxSubArray(v) << endl;
    assert(s.maxSubArray(v) == 6);


    return 0;
}
