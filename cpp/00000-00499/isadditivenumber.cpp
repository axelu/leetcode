
// 306. Additive Number
// https://leetcode.com/problems/additive-number/




class Solution {
private:
    bool done;
    string * pS;
    size_t n;
    vector<long long> F;

    void splitIntoFibonacci(int pos) {
        if( pos == n ) {
            if( F.size() >= 3 ) done = true;
            return;
        }

        if( done ) return;

        size_t l = F.size();

        // leading zeroes are not allowed
        if( pS->at(pos) == '0' ) {
            if( l <= 1 || ( F[l-2] == 0LL && F[l-1] == 0LL ) ) {
                F.push_back(0LL);
                splitIntoFibonacci(pos+1);
                if( !done )
                    F.pop_back();
            }
            return;
        }

        long long Fi,Fi1,Fi2;
        string s;
        for(int i = 1; i <= n-pos; ++i) {

            if( i == 20 ) break;
            s = pS->substr(pos,i);
            if( i == 19 && s > "9223372036854775807" ) break;

            Fi2 = stoll(s);

            if( l >= 2 ) {
                Fi  = F[l-2];
                Fi1 = F[l-1];
                if( Fi > LLONG_MAX - Fi1 || Fi + Fi1 != Fi2 )
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
    bool isAdditiveNumber(string& S) {
        n = S.size();
        if( n < 3 ) return false;

        done == false;
        F = {};
        pS = &S;
        splitIntoFibonacci(0);

        return done;
    }
};
