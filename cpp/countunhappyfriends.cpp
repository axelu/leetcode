
// Count Unhappy Friends
// https://leetcode.com/problems/count-unhappy-friends/




#include <iostream>
#include <cassert>

#include <vector>

using namespace std;

class Solution {
private:
    bool isUnhappy(int f, int p, vector<vector<int>>& rk, int n, vector<vector<int>>& pairs) {
            bool unhappy = false;
            int pref = rk[f][p];
            if( pref != n - 1 ) {
                // the friend's partner is not her prefered choice
                for(int j = 0; j < n; ++j) {
                    if( j == p ) continue;
                    if( rk[f][j] > pref ) {
                        // see if friends preference is shared
                        // preference of more preferred friend to our friend
                        int preftof = rk[j][f];

                        // preference of more preferred friend to preferred friend's partner
                        // find preferred friends partner in pairs by looking for j in pairs
                        int pfp; // preferred friends partner index
                        for(int k = 0; k < n/2; ++k) {
                            if( pairs[k][0] == j ) {
                                pfp = pairs[k][1];
                                break;
                            }
                            if( pairs[k][1] == j ) {
                                pfp = pairs[k][0];
                                break;
                            }
                        }
                        int preftop = rk[j][pfp];

                        // if friend's preferred friend likes friend
                        // over whoever she is partnererd with, that makes friend unhappy
                        if( preftof > preftop) {
                            unhappy = true;
                            break;
                        }
                    }
                }
            }
            return unhappy;
    }
public:
    int unhappyFriends(int n, vector<vector<int>>& preferences, vector<vector<int>>& pairs) {

        vector<vector<int>> rk(n, vector<int>(n, -1));
        for(int i = 0; i < n; ++i) {
            int p = n - 1;
            for(int j = 0; j < n - 1; ++j) {
                rk[i][preferences[i][j]] = p;
                --p;
            }
        }

        int r = 0;
        for(int k = 0; k < n/2; ++k) {
            int f = pairs[k][0]; // friend 0 in pair k -> friend
            int p = pairs[k][1]; // friend 1 in pair k -> partner
            // cout << "pair " << k << " friend " << f << " partner " << p << endl;

            // is friend unhappy?
            if( isUnhappy(f,p,rk,n,pairs) ) {
                // cout << "friend is unhappy " << endl;
                ++r;
            }

            // is partner unhappy?
            if( isUnhappy(p,f,rk,n,pairs) )  {
                // cout << "partner is unhappy " << endl;
                ++r;
            }
        }
        return r;
    }
};


int main() {
    Solution s;
    int n;
    vector<vector<int>> preferences;
    vector<vector<int>> pairs;
    int r;

    cout << endl << "example 1 " << endl;
    n = 4;
    preferences = {{1, 2, 3}, {3, 2, 0}, {3, 1, 0}, {1, 2, 0}};
    pairs = {{0, 1}, {2, 3}};
    r = s.unhappyFriends(n, preferences, pairs);
    cout << "result " << r << endl;
    assert(r == 2);

    cout << endl << "example 2 " << endl;
    n = 2;
    preferences = {{1}, {0}};
    pairs = {{1,0}};
    r = s.unhappyFriends(n, preferences, pairs);
    cout << "result " << r << endl;
    assert(r == 0);

    cout << endl << "example 3 " << endl;
    n = 4;
    preferences = {{1, 3, 2}, {2, 3, 0}, {1, 3, 0}, {0, 2, 1}};
    pairs = {{1, 3}, {0, 2}};
    r = s.unhappyFriends(n, preferences, pairs);
    cout << "result " << r << endl;
    assert(r == 4);

    // case 40 / 99 initialy from answer
    cout << endl << "example 4 " << endl;
    n = 4;
    preferences = {{1,3,2},{2,3,0},{1,0,3},{1,0,2}};
    pairs = {{2,1},{3,0}};
    r = s.unhappyFriends(n, preferences, pairs);
    cout << "result " << r << endl;
    assert(r == 0);


    return 0;
}
