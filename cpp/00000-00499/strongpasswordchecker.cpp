
// 420. Strong Password Checker
// https://leetcode.com/problems/strong-password-checker/


class Solution {
private:
    int numberRulesMet(string password) {
        int hasLower = 0, hasUpper = 0, hasDigit = 0;
        for(char c : password)
            if( islower(c) )
                hasLower = 1;
            else if( isupper(c) )
                hasUpper = 1;
            else if( isdigit(c) )
                hasDigit = 1;
        return hasLower + hasUpper +hasDigit;
    }

    int maxInRow(string password) {
        int ret = 0;
        char prev = '#';
        int cnt = 1;
        for(char c : password) {
            if( c == prev )
                ret = max(ret,++cnt);
            else
                cnt = 1;
            prev = c;
        }
        return ret;
    }

public:
    int strongPasswordChecker(string password) {
        int n = password.size();
        // cout << "n " << n << endl;

        // length rule: has at least 6 chars and at most 20 chars
        // rules besides length rule:
        // #1 contains at least one lowercase char
        // #2 contains at least one uppercase char
        // #3 contains at least one digit
        // #4 does not contain three repeating chars in a row

        // case: n < 6
        // we have to at least add 6-n chars
        //   if n <= 2 it cannot violate rule #4 and
        //       we can add chars to meet rules 1,2,3 -> ans = 4
        //   if n == 3
        //       it could violate rule #4, but we can break it
        //       by inserting -> ans = 3
        //   if n == 4
        //       we can meet 2 out of the three 1st rules
        //       by adding 2 char, we could also break repeating
        //       chars, but we need to see if we have rule 1-3 met
        //       if at least one met -> ans = 2 else ans = 3
        //   if n == 5
        //       if we have 4 or less in a row, the answer
        //       depends of how many of the rules 1-3 we already meet
        //       none -> ans = 3, one -> ans = 2, two+ -> ans = 1
        //       if we have 5 in a row, we cannot break up by inserting
        //       so we replace 1, then the answer depends
        //       of how many of the rules 1-3 we already meet
        //       none -> ans = 3 else 2
        if( n <= 2 )
            return 6-n;
        if( n == 3 )
            return 3;

        int r = numberRulesMet(password);
        // cout << "rules met " << r << endl;

        if( n == 4 )
            return r >= 1 ? 2 : 3;

        int m = maxInRow(password);
        // cout << "max in row " << m << endl;

        if( n == 5 ) {
            if( m <= 4 ) {
                if( r == 0 )
                    return 3;
                else if( r == 1 )
                    return 2;
                else
                    return 1;
            } else {
                return r == 0 ? 3 : 2;
            }
        }


        // if n > 20 go through and delete repeats,
        // break if we get to n == 20
        // this would not impact the number of rules we met
        // these deletion need to be prioritized by remainder of 3
        // with remainder 0 having the highest priority

        auto cmp = [](int a, int b) { return a%3 > b%3; };
        priority_queue<int,vector<int>,decltype(cmp)> pq(cmp);
        char prev = '#';
        int cnt = 1;
        for(char c : password) {
            if( c == prev ) {
                ++cnt;
            } else {
                if( cnt > 2 )
                    pq.push(cnt);
                cnt = 1;
            }
            prev = c;
        }
        // finish up
        if( cnt > 2 )
            pq.push(cnt);


        int base = 0; // deletions we performed
        while( !pq.empty() && n > 20 ) {
            int t = pq.top();
            pq.pop();
            ++base;
            --n;
            --t;
            if( t >= 3 )
                pq.push(t);
        }


        // if 6 < n <= 20 the question becomes:
        // how many rules are met and how many repeating
        // chars we need to break up
        // example
        // 01234567890123456789
        // ...!!!...!!!...!!!..
        // to break up repeating chars 3-5: 1, 6-8: 2, 9-11: 3, 12-14: 4, 15-17: 5, 18-20: 6
        // if the number of chars we need to break up
        // repeating chars is greater equal 3, than that is the answer, otherwise
        // it depends on number of rules met
        if( n <= 20 ) {
            int t = 0;
            while( !pq.empty() ) {
                t += pq.top() / 3;
                pq.pop();
            }
            // cout << "t " << t << endl;
            if( t >= 3 ) {
                return base + t;
            } else if( t == 2 ) {
                return r == 0 ? base + 3 : base + 2;
            } else if( t == 1 ) {
                if( r >= 2 )
                    return base + 1;
                else if( r == 1 )
                    return base + 2;
                else
                    return base + 3;
            } else {
                return base + (3-r);
            }
        }

        // if length is greater 20 we have to at least
        // remove n-20 char, the question becomes:
        // is there a subsequence of length 20 that meets
        // all other rules? or which of those 20char long
        // subsets needs the least steps to meet all rules
        return base + (n-20) + (3-r);
    }
};
