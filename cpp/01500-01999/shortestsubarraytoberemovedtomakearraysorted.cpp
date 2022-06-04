
// 1574. Shortest Subarray to be Removed to Make Array Sorted
// https://leetcode.com/problems/shortest-subarray-to-be-removed-to-make-array-sorted/


class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
        int n = arr.size();
        if( n == 1 )
            return 0;
        if( n == 2 )
            return arr[1] < arr[0] ? 1 : 0;

        // we can remove one subarray to make the remaing elements in arr non-decreasing
        // - from the front OR
        // - from the beginning OR
        // - in the middle OR
        // - the entire arr*
        // except 1 element, which by itself is non-decreasing


        // iterator pointing to left element of non-decreasing subarray ending at idx n-1
        auto b = arr.begin();
        for(auto it = next(arr.begin()); it != arr.end(); ++it)
            if( *prev(it) > *it)
                b = it;

        if( b == arr.begin() ) // arr already non-decreasing
            return 0;

        auto d = distance(arr.begin(),b);
        for(auto it = arr.begin(); it != arr.end(); ++it) {
            if( it != arr.begin() && *prev(it) > *it )
                break;

            auto f = lower_bound(b,arr.end(),*it);
            if( f != arr.end() )
                d = min(d,f - it - 1);
            else
                d = min(d,distance(it,prev(arr.end())));
        }

        return d;
    }
};
