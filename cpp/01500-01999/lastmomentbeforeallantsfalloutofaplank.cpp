
// 1503. Last Moment Before All Ants Fall Out of a Plank
// https://leetcode.com/problems/last-moment-before-all-ants-fall-out-of-a-plank/



class Solution {
public:
    int getLastMoment(int n, vector<int>& left, vector<int>& right) {

        // observation:
        // when an ant meets another ant, it is just as if both ants
        // would continue in the original direction

        // get max distance of ants traveling left to 0
        int t_lft = 0;
        if( !left.empty() ) {
            int mx_lft = *max_element(left.begin(),left.end());
            t_lft = mx_lft;
        }

        // get max discance of ants traveling right to n
        int t_rgt = 0;
        if( !right.empty() ) {
            int mn_rgt = *min_element(right.begin(),right.end());
            t_rgt = n - mn_rgt;
        }

        return max(t_lft,t_rgt);
    }
};
