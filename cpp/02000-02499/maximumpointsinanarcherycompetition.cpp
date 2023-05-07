
// 2212. Maximum Points in an Archery Competition
// https://leetcode.com/problems/maximum-points-in-an-archery-competition/




class Solution {
private:
    int bob_mx_score;
    vector<int> bob_mx_arrows;

    int calculate_bob_score(vector<int>& aliceArrows, vector<int>& bobArrows) {
        int bob_score = 0;
        for(int i = 0; i < 12; ++i)
            if( bobArrows[i] > aliceArrows[i] )
                bob_score += i;

        return bob_score;
    }

    void rec(vector<int>& aliceArrows, int i, int k, vector<int>& bobArrows) {
        /*
        cout << "rec i " << i << " k " << k << " " << endl;
        cout << "Alice ";
        for(int i = 0; i < 12; ++i)
            cout << i << ":" << aliceArrows[i] << " ";
        cout << endl;
        cout << "Bob   ";
        for(int i = 0; i < 12; ++i)
            cout << i << ":" << bobArrows[i] << " ";
        cout << endl;
        */

        if( k == 0 ) {
            // Bob is out of arrows
            // calculate Bob's score
            int bob_score = calculate_bob_score(aliceArrows,bobArrows);
            // cout << "Bob is out of arrows: bob_score " << bob_score << endl;
            if( bob_score > bob_mx_score ) {
                bob_mx_score = bob_score;
                bob_mx_arrows = bobArrows;
            }
            return;
        }

        if( i == -1 ) {
            // if Bob still has arrows, we can put them anywhere,
            // it won't change the score
            int t = bobArrows[0];
            bobArrows[0] += k;
            int bob_score = calculate_bob_score(aliceArrows,bobArrows);
            if( bob_score > bob_mx_score ) {
                bob_mx_score = bob_score;
                bob_mx_arrows = bobArrows;
            }
            bobArrows[0] = t; // backtrack
            return;
        }

        // we have a choice
        //   if Alice has no arrow in the current section,
        //     then it is always best that Bob puts one and only arrow in to harvest the points
        //   if Alice has some number arrows x in the current section,
        //     and Bob has at least x+1 arrows, then Bob puts x+1 arrows in the current section
        //     OR Bob puts 0 arrows in the current section

        if( aliceArrows[i] == 0 ) {
            bobArrows[i] = 1;
            rec(aliceArrows,i-1,k-1,bobArrows);
            bobArrows[i] = 0; // backtrack

        } else {
            if( k > aliceArrows[i] ) {
                bobArrows[i] = aliceArrows[i] + 1;
                rec(aliceArrows,i-1,k-(aliceArrows[i] + 1),bobArrows);
                bobArrows[i] = 0; // backtrack
            }

            rec(aliceArrows,i-1,k,bobArrows);
        }

    }

public:
    vector<int> maximumBobPoints(int numArrows, vector<int>& aliceArrows) {
        bob_mx_score = 0;

        vector<int> bobArrows(12,0);
        rec(aliceArrows,11,numArrows,bobArrows);

        /*
        int bob_nbr_arrows = 0;
        cout << "Alice ";
        for(int i = 0; i < 12; ++i)
            cout << i << ":" << aliceArrows[i] << " ";
        cout << endl;
        cout << "Bob   ";
        for(int i = 0; i < 12; ++i) {
            bob_nbr_arrows += bob_mx_arrows[i];
            cout << i << ":" << bob_mx_arrows[i] << " ";
        }
        cout << endl;
        cout << "bob_nbr_arrows " << bob_nbr_arrows << endl;
        cout << "bob_score " << bob_mx_score << endl;
        */

        return bob_mx_arrows;
    }
};
