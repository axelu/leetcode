
// 2369. Check if There is a Valid Partition For The Array
// https://leetcode.com/problems/check-if-there-is-a-valid-partition-for-the-array/



class Solution {
private:
    int n;
    int * equ;
    int * asc;
    int * mem;

    bool rec(int i) {
        if( i == n )
            return true;
        if( i == n-1 )
            return false;

        if( mem[i] != -1 )
            return mem[i];

        // at each position we have a choice
        //    if 2 (or 3) equal -> jump to idx i+2
        //    if 3 equal        -> jump to idx i+3
        //    if 3 ascending    -> jump to idx i+3

        bool f = false;

        if( equ[i] == 3 || asc[i] == 3 )
            f = rec(i+3);

        if( !f && equ[i] >= 2 )
            f = rec(i+2);

        return mem[i] = f;
    }

public:
    bool validPartition(vector<int>& nums) {
        n = nums.size();

        // number of equal elements to the right starting from i including i
        // if more than 3 then 3
        equ = new int[n];
        equ[n-1] = 1;

        // number of ascending by 1 elements to the right starting from i including i
        // if more than 3 then 3
        asc = new int[n];
        asc[n-1] = 1;

        for(int i = n-2; i >= 0; --i) {
            equ[i] = nums[i] == nums[i+1] ? min(3,equ[i+1] + 1) : 1;
            asc[i] = nums[i] == nums[i+1]-1 ? min(3,asc[i+1] + 1) : 1;
        }

        // debug
        /*
        for(int i = 0; i < n; ++i)
            cout << equ[i] << " ";
        cout << endl;
        for(int i = 0; i < n; ++i)
            cout << asc[i] << " ";
        cout << endl;
        */

        mem = new int[n];
        for(int i = 0; i < n; ++i)
            mem[i] = -1;

        return rec(0);
    }
};
