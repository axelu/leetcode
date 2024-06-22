
// 3024. Type of Triangle II
// https://leetcode.com/problems/type-of-triangle-ii/





class Solution {
public:
    string triangleType(vector<int>& nums) {
        // nums.size() == 3
        // A triangle is called equilateral if it has all sides of equal length.
        // A triangle is called isosceles if it has exactly two sides of equal length.
        // A triangle is called scalene if all its sides are of different lengths.
        int a = nums[0];
        int b = nums[1];
        int c = nums[2];

        if( a == b && a == c ) {
                return "equilateral";
        } else if( a + b > c && a + c > b && b + c > a ) { // can we make a triangle?
            if( a == b || a == c || b == c ) {
                return "isosceles";
            } else if( a != b && a != c && b != c ) {
                    return"scalene";
            }
        }
        return "none";
    }
};
