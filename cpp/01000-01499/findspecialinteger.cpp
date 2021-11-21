
// 1287. Find Special Integer
// https://leetcode.com/problems/element-appearing-more-than-25-in-sorted-array/


class Solution {
public:
    int findSpecialInteger(vector<int>& arr) {
        auto n = arr.size()/4;

        /*
        int a[100001]; memset(a,0,sizeof a);
        for(auto it = begin(arr); it != end(arr); ++it) {
            ++a[*it];
            if( a[*it] > n ) return *it;
        }
        return *(it-1);
        */

        int prev = -1;
        int count = 0;
        for(auto it = begin(arr); it != end(arr); ++it) {
            if( prev != *it ) {
                if( count > n ) return prev;
                prev = *it;
                count = 0;
            }
            ++count;
        }
        return prev;
    }
};
