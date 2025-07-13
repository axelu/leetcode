
// 3516. Find Closest Person
// https://leetcode.com/problems/find-closest-person/




class Solution {
public:
    int findClosest(int x, int y, int z) {
        int dist13 = abs(x-z);
        int dist23 = abs(y-z);

        if( dist13 == dist23 )
            return 0;

        if( dist13 < dist23 )
            return 1;

        return 2;
    }
};
