
// 2525. Categorize Box According to Criteria
// https://leetcode.com/problems/categorize-box-according-to-criteria/



class Solution {
public:
    string categorizeBox(long l, long w, long h, int m) {

        bool is_bulky = false;
        bool is_heavy = false;
        string category = "Neither";

        if( l >= 1e4 || w >= 1e4 || h >= 1e4 || l*w*h >= 1e9 )
            is_bulky = true;
        if( m >= 1e2 )
            is_heavy = true;

        if( is_bulky && is_heavy )
            category = "Both";
        else if( is_bulky )
            category = "Bulky";
        else if( is_heavy )
            category = "Heavy";

        return category;
    }
};
