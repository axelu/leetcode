
// 679. 24 Game
// https://leetcode.com/problems/24-game/



/* 24 prime factorization: 2 2 2 3
 *
 * example 1 [4,1,8,7]
 *                4     8      7  1
 * prime factors  2 2   2 2 2  7  1
 * ans expression (8-4) * (7-1)
 * so in essence we are creating the prime factors of 24
 *                 (   8   -  4  ) * (7-1)
 *                 (   8   -  4  ) * ( 6 )
 *                 ((2*2*2)-(2*2)) * (2*3)
 *                 (      2*2    ) * (2*3)
 */
class Solution {
private:
    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

    // recursive function to return gcd of a and b
    long long gcd(long long int a, long long int b) {
        if( b == 0 )
            return a;
        return gcd(b,a % b);
    }

    // function to return Least Common Multiple (LCM) of two numbers
    // LCM definition:
    // LCM of two numbers is the smallest number which can be divided by both numbers
    long long lcm(long a, long b) {
        return (a / gcd(a,b)) * b;
    }

    void ops(int op1, int op2, int mask, vector<vector<int>>& out) {
        int q,d;
        // op1 + op2 (= op2 + op1)
        q = op1 + op2;
        d = 1;
        out.push_back({q,d,mask});
        // op1 - op2
        q = op1 - op2;
        d = 1;
        out.push_back({q,d,mask});
        // op2 - op1
        q = op2 - op1;
        d = 1;
        out.push_back({q,d,mask});
        // op1 * op2 (= op2 * op1)
        q = op1 * op2;
        d = 1;
        out.push_back({q,d,mask});
        int _gcd = gcd(op1,op2);
        // op1 / op2
        q = op1/_gcd;
        d = op2/_gcd;
        out.push_back({q,d,mask});
        // op2 / op1
        q = op2/_gcd;
        d = op1/_gcd;
        out.push_back({q,d,mask});
    }

    void ops(int q1, int d1, int op2, int mask, vector<vector<int>>& out) {
        int q,d;
        int q2 = op2;
        int d2 = 1;

        // op1 + op2 (= op2 + op1)
        q = q1 + (op2 * d1);
        d = d1;
        out.push_back({q,d,mask});
        // op1 - op2
        q = q1 - (op2 * d1);
        d = d1;
        out.push_back({q,d,mask});
        // op2 - op1
        q = (op2 * d1) - q1;
        d = d1;
        out.push_back({q,d,mask});
        // op1 * op2 (= op2 * op1)
        q = q1 * op2;
        d = d1;
        out.push_back({q,d,mask});
        // op1 / op2
        q = q1;
        d = d1 * op2;
        out.push_back({q,d,mask});
        // op2 / op1
        q = op2 * d1;
        d = q1;
        out.push_back({q,d,mask});
    }

    vector<vector<int>> base(vector<int>& cards) {
        vector<vector<int>> ret;
        for(int i = 1; i < 16; ++i) { // mask
            if( countSetBits(i) == 2 ) {
                int op1 = -1, op2;
                for(int k = 0; k < 4; ++k) {
                    if( (1<<k) & i ) {
                        if( op1 == -1 )
                            op1 = cards[k];
                        else
                            op2 = cards[k];
                    }
                }
                // cout << "op1 " << op1 << " op2 " << op2 << endl;
                ops(op1,op2,i,ret);
            }
        }

        return ret;
    }

    bool solve(int q1, int d1, int q2, int d2) {
        // op1 = q1/d1;
        // op2 = q2/d2;

        if( d1 == 0 || d2 == 0 )
            return false;

        int _lcm = lcm(d1,d2);
        // op1 + op2 (= op2 + op1)
        int t = (q1 * (_lcm/d1)) + (q2 * (_lcm/d2));
        if( (t / _lcm == 24) && (t % _lcm == 0) )
            return true;

        // op1 - op2
        t = (q1 * (_lcm/d1)) - (q2 * (_lcm/d2));
        if( (t / _lcm == 24) && (t % _lcm == 0) )
            return true;

        // op2 - op1
        t = (q2 * (_lcm/d2)) - (q1 * (_lcm/d1));
        if( (t / _lcm == 24) && (t % _lcm == 0) )
            return true;

        // op1 * op2 (= op2 * op1)
        int q = q1 * q2;
        int d = d1 * d2;
        if( d != 0 && (q / d == 24) && (q % d == 0) )
            return true;

        // op1 / op2
        q = q1 * d2;
        d = d1 * q2;
        if( d != 0 && (q / d == 24) && (q % d == 0) )
            return true;

        // op2 / op1
        q = q2 * d1;
        d = d2 * q1;
        if( d != 0 && (q / d == 24) && (q % d == 0) )
            return true;

        return false;
    }

    bool solve2ops(vector<vector<int>>& twoops, vector<int>& cards) {

        for(auto v: twoops) {
            int q1 = v[0];
            int d1 = v[1];
            int mask = v[2];
            // get the two unused operands
            int op1 = -1, op2;
            for(int k = 0; k < 4; ++k) {
                if( !((1<<k) & mask) ) {
                    if( op1 == -1 )
                        op1 = cards[k];
                    else
                        op2 = cards[k];
                }
            }
            // cout << "op1 " << op1 << " op2 " << op2 << endl;
            // get ops
            vector<vector<int>> othertwoops;
            ops(op1,op2,-1,othertwoops);
            // solve
            for(auto vo: othertwoops) {
                int q2 = vo[0];
                int d2 = vo[1];
                if( solve(q1,d1,q2,d2) )
                    return true;
            }
        }

        return false;
    }

    bool solve3ops(vector<vector<int>>& twoops, vector<int>& cards) {

        for(auto v: twoops) {
            int q1 = v[0];
            int d1 = v[1];
            int mask = v[2];
            // get the two unused operands
            int op1 = -1, op2;
            for(int k = 0; k < 4; ++k) {
                if( !((1<<k) & mask) ) {
                    if( op1 == -1 )
                        op1 = cards[k];
                    else
                        op2 = cards[k];
                }
            }
            // cout << "op1 " << op1 << " op2 " << op2 << endl;

            // combine twoops with op1
            vector<vector<int>> vop1;
            ops(q1,d1,op1,-1,vop1);
            // solve
            for(auto vvop1: vop1) {
                if( solve(vvop1[0],vvop1[1],op2,1) )
                    return true;
            }

            // combine twoops with op2
            vector<vector<int>> vop2;
            ops(q1,d1,op2,-1,vop2);
            // solve
            for(auto vvop2: vop2) {
                if( solve(vvop2[0],vvop2[1],op1,1) )
                    return true;
            }
        }

        return false;
    }

public:
    bool judgePoint24(vector<int>& cards) {

        // brute force

        vector<vector<int>> _base = base(cards);
        if( solve2ops(_base,cards) )
            return true;

        if( solve3ops(_base,cards) )
            return true;

        return false;
    }
};
