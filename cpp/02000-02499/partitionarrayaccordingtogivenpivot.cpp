
// 2161. Partition Array According to Given Pivot
// https://leetcode.com/problems/partition-array-according-to-given-pivot/



class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        vector<int> lp,p,gp;

        for(int x: nums)
            if( x < pivot )
                lp.push_back(x);
            else if( x == pivot )
                p.push_back(x);
            else
                gp.push_back(x);

        lp.insert(end(lp),begin(p),end(p));
        lp.insert(end(lp),begin(gp),end(gp));

        return lp;
    }
};
