
// 1691. Maximum Height by Stacking Cuboids 
// https://leetcode.com/problems/maximum-height-by-stacking-cuboids/





/*
 * each cuboids has three sides, and because we can rotate them, we can come through 6 different permutations for each:
 * let L, W, H be the length of each side:
 * initial (L,W,H), (W,L,H), (L,H,W), (W,H,L), (H,L,W) and (H,W,L)
 * we need to optimize height, so an ideal rotation of a cube would have the largest dimension as the height
 * note that we may not be able to use all cuboids, example:
 *    [[1,3,5],[2,4,3]]  <- we can only use cuboid 0 to get to optimal answer of 5
 *
 */
class Solution {
private:
    int mem[100][101];

    int rec(vector<vector<int>>& cuboids, int n, int i, int lst_cuboid) {
        // lst_cuboid has offset of 1 !!!

        if( i == n )
            return 0;

        if( mem[i][lst_cuboid] != -1 )
            return mem[i][lst_cuboid];

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

        return mem[i][lst_cuboid] = max(a,b);
    }

public:
    int maxHeight(vector<vector<int>>& cuboids) {
        // sort the dimensions inside each cuboid
        for(auto& v: cuboids)
            sort(v.begin(),v.end());

        // now sort the cuboids
        sort(cuboids.begin(),cuboids.end(),[](const auto& a, const auto& b) {
            if( a[2] > b[2] ) {
                return true;
            } else if( a[2] == b[2] ) {
                if( a[1] > b[1] ) {
                    return true;
                } else if( a[1] == b[1] ) {
                    if( a[0] > b[0] ) {
                        return true;
                    }
                }
            }
            return false;
        });

        memset(mem,-1,sizeof mem);
        return rec(cuboids,cuboids.size(),0,0);
    }
};
