
// day 1 September 2020 challenge
// 949. Largest Time for Given Digits
// https://leetcode.com/explore/challenge/card/september-leetcoding-challenge/554/week-1-september-1st-september-7th/3445/
// https://leetcode.com/problems/largest-time-for-given-digits/

class Solution {
public:
    string largestTimeFromDigits(vector<int>& A) {
        // largets 23:59, smallest 00:00
        // 1st digit <=2
        // 2nd digit <=3 if 1st digit is 2, else <=9
        // 3rd digit <=5
        // 4th digit <=9

        string r;
        for(int i = 2; i >= 0; --i) {
            r = _getTime(A, i);
            if( r.size() == 5 ) break;
        }
        return ( r.size() == 5 ) ? r : "";
    }
private:
    string _getTime(vector<int> A, int d) {
        string r = "";

        auto it = find(A.begin(), A.end(), d);
        if ( it != A.end() ) {
            r.append(to_string(d));
            A.erase(it);
            sort(A.begin(), A.end(),[](int a, int b){ return a > b; });

            for(int i = 0; i < 2; ++i) {
                if( i == 1 ) r.append(":");

                vector<int>::iterator it;
                if( i == 0 ) {
                    it = ( d == 2 ) ? _getDigit(A, 3) : _getDigit(A, 9);
                } else if ( i == 1 ) {
                    it = _getDigit(A, 5);
                }

                if( it == A.end() ) {
                    break;
                } else {
                    r.append(to_string(*it));
                    A.erase(it);
                }
            }
            r.append(to_string(A[0]));
        }

        return r;
    }

    vector<int>::iterator _getDigit(vector<int>& A, int d) {
        auto it = A.begin();
        for(; it != A.end(); ++it) {
            if( *it <= d ) break;
        }
        return it;
    }
};
