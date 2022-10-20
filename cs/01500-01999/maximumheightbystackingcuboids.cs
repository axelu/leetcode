
// 1691. Maximum Height by Stacking Cuboids 
// https://leetcode.com/problems/maximum-height-by-stacking-cuboids/





public class Solution {
    int[,] mem;

    private int rec(int[][] cuboids, int n, int i, int lst_cuboid) {
        // lst_cuboid has offset of 1 !!!
        if( i == n )
            return 0;

        if( mem[i,lst_cuboid] != -1 )
            return mem[i,lst_cuboid];

        // at each cuboid we have a choice
        //    skip it
        //    take it if we can

        // skip
        int a = rec(cuboids,n,i+1,lst_cuboid);

        // take it if we can
        int b = 0;

        // no cuboid has been taken so far, so yes, we can take this one
        if( lst_cuboid == 0 ) {
            b = cuboids[i][2] + rec(cuboids,n,i+1,i+1);

        // we need to check if we can fit this cuboid onto the last cuboid taken
        } else if( cuboids[i][0] <= cuboids[lst_cuboid-1][0] &&
                   cuboids[i][1] <= cuboids[lst_cuboid-1][1] ) {

            b = cuboids[i][2] + rec(cuboids,n,i+1,i+1);
        }

        return mem[i,lst_cuboid] = Math.Max(a,b);
    }

    private int cmp(int[] a, int[] b) {
        if( a[2] > b[2] ) {
            return -1;
        } else if( a[2] == b[2] ) {
            if( a[1] > b[1] ) {
                return -1;
            } else if( a[1] == b[1] ) {
                if( a[0] > b[0] ) {
                    return -1;
                } else if( a[0] == b[0] ) {
                    return 0;
                }
            }
        }
        return 1;
    }

    public int MaxHeight(int[][] cuboids) {
        // sort the dimensions inside each cuboid
        foreach (int[] v in cuboids)
            Array.Sort(v);

        // now sort the cuboids
        Array.Sort(cuboids, (a, b) => cmp(a, b));

        int n = cuboids.Length;
        mem = new int[n,n+1];
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n+1; ++j)
                mem[i,j] = -1;

        return rec(cuboids,n,0,0);
    }
}
