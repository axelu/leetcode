
// 1899. Merge Triplets to Form Target Triplet
// https://leetcode.com/problems/merge-triplets-to-form-target-triplet/





// cases
//     abc
//     ---
// 1 1 x
// 1 2  x
// 1 3   x
//     ---
// 2 1 xx
// 2 2  xx
// 2 3 x x
//     ---
// 3   xxx

class Solution {
public:
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {
        int x = target[0], y = target[1], z = target[2];

        int a,b,c;
        bool case11 = false, case12 = false, case13 = false;
        bool case21 = false, case22 = false, case23 = false;
        for(int i = 0; i < triplets.size(); ++i) {
            a = triplets[i][0];
            b = triplets[i][1];
            c = triplets[i][2];

            if( a == x && b == y && c == z )
                return true;
            else if( a == x && b < y && c < z )
                case11 = true;
            else if( a < x && b == y && c < z )
                case12 = true;
            else if( a < x && b < y && c == z )
                case13 = true;
            else if( a == x && b == y && c < z )
                case21 = true;
            else if( a < x && b == y && c == z )
                case22 = true;
            else if( a == x && b < y && c == z )
                case23 = true;
        }

        if( (case11 && case12 && case13) ||
            (case11 && case22) ||
            (case12 && case23) ||
            (case13 && case21) ||
            (case21 && (case22 || case23)) ||
            (case22 && (case21 || case23)) ||
            (case23 && (case21 || case22)) ||
            (case11 && case21 && case23) ||
            (case12 && case21 && case22) ||
            (case13 && case22 && case23) )
            return true;


        return false;
    }
};
