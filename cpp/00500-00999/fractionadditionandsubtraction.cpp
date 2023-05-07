
// 592. Fraction Addition and Subtraction
// https://leetcode.com/problems/fraction-addition-and-subtraction/





class Solution {
private:
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



    tuple<char,long,long> solve(char a_sign, long a_numerator, long a_denominator, char op, long b_numerator, long b_denominator) {
        // get the least common denominator
        long lcd = lcm(a_denominator,b_denominator);

        a_numerator = a_numerator * (lcd/a_denominator);
        if( a_sign == '-' )
            a_numerator *= -1;

        b_numerator = b_numerator * (lcd/b_denominator);
        if( op == '-' )
            b_numerator *= -1;

        long numerator = a_numerator + b_numerator;
        char sign = '+';
        if( numerator < 0 ) {
            sign = '-';
            numerator *= -1;
        }

        long _gcd = gcd(numerator,lcd);

        numerator /= _gcd;
        lcd /= _gcd;

        return {sign,numerator,lcd};
    }

public:
    string fractionAddition(string expression) {

        char pre_op = '#'; // sentinel
        long pre_numerator;
        long pre_denominator;

        int n = expression.size();
        char curr_op = '#';
        long curr_numerator = -1;
        long curr_denominator = -1;

        for(int i = 0; i < n; ++i) {
            if( i == 0 ) {
                if( isdigit(expression[0]) )
                    curr_op = '+';
            }

            if( curr_op == '#' ) {
                // our current char must be the op
                curr_op = expression[i];
                continue;
            }

            if( curr_numerator == -1 ) {
                long t = 0;
                while( isdigit(expression[i]) ) {
                    t = (t * 10) + (expression[i]-'0');
                    ++i;
                }
                curr_numerator = t;
                continue;
            }

             if( curr_denominator == -1 ) {
                long t = 0;
                while( i < n && isdigit(expression[i]) ) {
                    t = (t * 10) + (expression[i]-'0');
                    ++i;
                }
                curr_denominator = t;

                // we have the current op, current the numerator and current denominator
                // cout << "curr op " << curr_op << " curr numerator " << curr_numerator << " curr denominator " << curr_denominator << endl;
                if( pre_op == '#' ) {
                    // this was our 1st fraction
                    pre_op = curr_op;
                    pre_numerator = curr_numerator;
                    pre_denominator = curr_denominator;

                    if( i < n )
                        curr_op = expression[i];
                    curr_numerator = -1;
                    curr_denominator = -1;

                    continue;
                }

                // lets do math
                tie(pre_op,pre_numerator,pre_denominator) = solve(pre_op,pre_numerator,pre_denominator,curr_op,curr_numerator,curr_denominator);

                if( i < n )
                    curr_op = expression[i];
                curr_numerator = -1;
                curr_denominator = -1;
            }
        }

        string ans = "";
        if( pre_op == '-' )
            ans = ans + '-';
        ans = ans + to_string(pre_numerator) + '/' + to_string(pre_denominator);

        return ans;
    }
};
