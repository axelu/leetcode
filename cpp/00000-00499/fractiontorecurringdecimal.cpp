
// 166. Fraction to Recurring Decimal
// https://leetcode.com/problems/fraction-to-recurring-decimal/




// https://www.mathsisfun.com/long_division3.html
// try like 1/333, 1/6, 1/2133333332

class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        // -2^31 <= numerator, denominator <= 2^31 - 1
        // numerator is the top number of a fraction, denominator the bottom
        // denominator != 0
        // fraction = numerator / denominator
        // in the context of division: quotient = dividend / divisor

        if( numerator == 0 )
            return "0";

        if( denominator == 1 )
            return to_string(numerator);

        // sign
        long num = numerator,den = denominator;
        string sign = "";
        if( numerator < 0 && denominator > 0) {
            num *= -1;
            sign = "-";
        } else if(numerator > 0 && denominator < 0 ) {
            den *= -1;
            sign = "-";
        }

        long d = num/den;
        // d is part before the decimal place in case we have a remainder
        string ans = sign + to_string(d);
        long rem = num % den;
        if( rem == 0 )
            return ans;

        ans = ans + '.';
        int offset = ans.size();

        // round 0
        num = num - (den * d);
        num = num * 10; // basically the remainder
        d = num / den;

        unordered_map<long,int> seen; // num, position
        seen[num] = 0;
        pair<unordered_map<long,int>::iterator,bool> p;
        for(int i = 0; i <= 10000; ++i) { // from contraint: answer.size() < 10^4 for all the given inputs
            // cout << "i " << i << " num " << num << endl;

            ans.push_back('0'+d);
            num = num - (den * d);
            if (num == 0)
                break;
            num = num * 10;
            p = seen.insert({num,i+1});
            if( !p.second ) { // break if we have seen this 'remainder' before
                ans.insert(offset +p.first->second,1,'(');
                ans.push_back(')');
                break;
            }
            d = num / den;
        }

        return ans;
    }
};
