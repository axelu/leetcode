
// 3200. Maximum Height of a Triangle
// https://leetcode.com/problems/maximum-height-of-a-triangle/



class Solution {
private:
    int solve(int red, int blue) {
        int ret = 0;
        int take = 1;
        while( true ) {
            red -= take;
            if( red < 0 ) {
                break;
            }
            ++ret;
            ++take;
            blue -= take;
            if( blue < 0 ) {
                break;
            }
            ++ret;
            ++take;
        }
        return ret;
    }
public:
    int maxHeightOfTriangle(int red, int blue) {
        int a = solve(red,blue);
        int b = solve(blue,red);

        return max(a,b);
    }
};
