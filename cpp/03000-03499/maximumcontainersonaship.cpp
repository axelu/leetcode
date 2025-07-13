
// 3492. Maximum Containers on a Ship
// https://leetcode.com/problems/maximum-containers-on-a-ship/



class Solution {
public:
    int maxContainers(int n, int w, int maxWeight) {
        int number_cells = n * n;
        if( number_cells * w <= maxWeight )
            return number_cells;
        else
            return maxWeight / w;
    }
};
