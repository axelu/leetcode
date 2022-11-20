
// 1388. Pizza With 3n Slices
// https://leetcode.com/problems/pizza-with-3n-slices/



class Solution {
private:
    int n,n3;
    int * _slices;

    int mem[2][500][1500];

    int rec(int zero, int count, int i) {

        if( count == n )
            return 0;

        if( i >= n3 || ( i == n3-1 && zero ) )
            return INT_MIN;

        if( mem[zero][count][i] != -1 )
            return mem[zero][count][i];

        // at each slice i we have a choice
        //     skip the slice
        //     pick the slice

        // skip
        int a = rec(zero,count,i+1);

        // pick
        if( i == 0 )
            zero = 1;
        int b = _slices[i] + rec(zero,count+1,i+2);

        return mem[zero][count][i] = max(a,b);
    }

public:
    int maxSizeSlices(vector<int>& slices) {
        n3 = slices.size(); // n is a multiple of 3, 3 <= n <= 498
        // edge case
        if( n3 == 3 )
            return max({slices[0],slices[1],slices[2]});

        n = n3/3;
        _slices = slices.data();

        memset(mem,-1,sizeof mem);
        return rec(0,0,0);
    }
};
