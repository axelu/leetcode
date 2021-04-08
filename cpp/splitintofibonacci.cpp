
// 842. Split Array into Fibonacci Sequence
// https://leetcode.com/problems/split-array-into-fibonacci-sequence/



class Solution {
private:
    bool done;
    string * pS;
    size_t n;
    vector<int> F;

    void splitIntoFibonacci(int pos) {
        if( pos == n ) {
            if( F.size() >= 3 ) done = true;
            return;
        }

        if( done ) return;

        size_t l = F.size();

        // leading zeroes are not allowed
        if( pS->at(pos) == '0' ) {
            if( l <= 1 || ( F[l-2] == 0 && F[l-1] == 0 ) ) {
                F.push_back(0);
                splitIntoFibonacci(pos+1);
                if( !done )
                    F.pop_back();
            }
            return;
        }

        int Fi,Fi1,Fi2;
        string s;
        for(int i = 1; i <= n-pos; ++i) {

            if( i == 11 ) break;
            s = pS->substr(pos,i);
            if( i == 10 && s > "2147483647" ) break;

            Fi2 = stoi(s);

            if( l >= 2 ) {
                Fi  = F[l-2];
                Fi1 = F[l-1];
                if( Fi > INT_MAX - Fi1 || Fi + Fi1 != Fi2 )
                    continue;
            }

            F.push_back(Fi2);
            splitIntoFibonacci(pos+i);
            if( done )
                break;
            else
                F.pop_back();
        }
    }

public:
    vector<int> splitIntoFibonacci(string& S) {
        n = S.size();
        F = {};
        if( n < 3 ) return F;

        done == false;
        pS = &S;
        splitIntoFibonacci(0);

        return F;
    }
};
