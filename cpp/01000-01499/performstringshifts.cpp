
// 1427. Perform String Shifts
// https://leetcode.com/problems/perform-string-shifts/



class Solution {
public:
    string stringShift(string s, vector<vector<int>>& shift) {
        int n = s.size();
        if( n == 1 ) return s;
        int amount = 0;
        for(int i = 0; i < shift.size(); ++i) {
            if( shift[i][0] == 0 )
                amount -= shift[i][1];
            else
                amount += shift[i][1];
        }
        amount = amount % n;
        if( amount == 0 ) return s;
        if( amount < 0 ) // rotate left
            rotate(s.begin(),s.begin()-amount,s.end());
        else             // rotate right
            rotate(s.rbegin(),s.rbegin()+amount,s.rend());
        return s;
    }
};
