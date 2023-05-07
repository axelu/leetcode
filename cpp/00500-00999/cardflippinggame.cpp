
// 822. Card Flipping Game
// https://leetcode.com/problems/card-flipping-game/



class Solution {
public:
    int flipgame(vector<int>& fronts, vector<int>& backs) {
        int n = fronts.size(); // fronts.size() == backs.size()

        // let a be the set of numbers, where fronts[i] == backs[i]
        // any number in a is NOT the solution
        // answer: smallest number that is not in a

        unordered_set<int> a;
        for(int i = 0; i < n; ++i)
            if( fronts[i] == backs[i] )
                a.insert(fronts[i]);

        sort(fronts.begin(),fronts.end());
        sort(backs.begin(),backs.end());

        int i = 0, j = 0;
        while( i < n && j < n ) {
            if( fronts[i] < backs[j] ) {
                if( a.find(fronts[i]) == a.end() )
                    return fronts[i];
                ++i;
            } else if( backs[j] < fronts[i] ) {
                if( a.find(backs[j]) == a.end() )
                    return backs[j];
                ++j;
            } else { // fronts[i] < backs[j]
                if( a.find(fronts[i]) == a.end() )
                    return fronts[i];
                ++i;
                ++j;
            }
        }
        while( i < n ) {
           if( a.find(fronts[i]) == a.end() )
                return fronts[i];
            ++i;
        }
        while( j < n ) {
            if( a.find(backs[j]) == a.end() )
                return backs[j];
            ++j;
        }

        return 0;
    }
};
