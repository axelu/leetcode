
// 1007. Minimum Domino Rotations For Equal Row
// day 19 October 2020 challenge
// https://leetcode.com/problems/minimum-domino-rotations-for-equal-row/


class Solution {
private:
    int rotateDominos(const vector<int>& A, const vector<int>& B, const int& n, const int& target) {
        int r = 0;
        for(int i = 0; i < n; ++i) {
            if( A[i] == target ) continue;
            if( B[i] == target ) {
                ++r;
            } else {
                r = 20001;
                break;
            }
        }
        return r;
    }
public:
    int minDominoRotations(vector<int>& A, vector<int>& B) {
        // 2 <= A.length == B.length <= 2 * 10e4
        // 1 <= A[i], B[i] <= 6

        auto n = A.size();

        // get unique numbers 1 to 6 in A and B
        int au = 0;
        int bu = 0;
        for(int i = 0; i < n; ++i) {
            au |= 1 << A[i];
            bu |= 1 << B[i];
        }

        // if all values in A or B are already the same return 0
        int ctA = 0;
        int ctB = 0;
        for(int i = 1; i < 7; ++i) {
            ctA += (au >> i) & 1;
            ctB += (bu >> i) & 1;
        }
        if( ctA == 1 || ctB == 1 ) return 0;

        // only if a number is in A and B do we have a chance of success
        // also: only those numbers do we need to try to get A or B to
        int possible = au & bu;
        if( !possible ) return -1;

        int moves = 20001;
        for(int i = 1; i < 7; ++i)
            if( (possible >> i) & 1 )
                moves = min({moves,rotateDominos(A,B,n,i),rotateDominos(B,A,n,i)});

        return moves == 20001 ? -1 : moves;
    }
};
