
// 2117. Abbreviating the Product of a Range
// https://leetcode.com/problems/abbreviating-the-product-of-a-range/

/* based on approach given in the hints of the problem
 * trailing zeros (let it be C)
 *     number of trailing zeros C is the number of times the product is completely divisible by 10. 
 *     2 and 5 are the only prime factors of 10, C will be equal to the minimum number of times 
 *     2 or 5 appear in the prime factorization of the product.
 *     example left = 371, right = 375
 *         371 / 2 =   0 371 / 5 =   0    
 *         372 / 2 =   2 372 / 5 =   0     
 *         373 / 2 =   0 373 / 5 =   0    
 *         374 / 2 =   1 374 / 5 =   0     
 *         375 / 2 =   0 375 / 5 =   3    
 *                  ----           ----
 *                     3             3   min(3,3) = 3 = C
 * 
 * last five
 *    for integers from left to right:
 *    For every integer, keep dividing it by 2 as long as it is divisible by 2 and 
 *    C occurrences of 2 haven't been removed in total. 
 *    Repeat this process for 5. 
 *    Then  multiply the integer under modulo of 10^5 with the product obtained till now to obtain the last five digits.
 *    see implementation below in code
 *
 * first five
 *    The product P can be represented as P=10^(x+y) where x is the integral part and y is the fractional part of x+y. 
 *    Using the property "if S = A * B, then log(S) = log(A) + log(B)", 
 *    we can write x+y = log_10(P) = sum(log_10(i)) for each integer i in [left, right]. 
 *    Once we obtain the sum, the first five digits can be represented as floor(10^(y+4))
 *    see implementation below in code
 */
class Solution {
private:
    // prime factorization
    pair<int,int> primeFactors(int n) {
        // returns number of 2 and 5 as prime factors of n
        
        int twos = 0;
        int fives = 0;
        
        // the number of 2s that divide n
        while(n % 2 == 0) {
            // cout << 2 << " ";
            ++twos;
            n = n/2;
        }

        // n must be odd at this point.
        // skip one element (Note i = i +2)
        for(int i = 3; i <= sqrt(n); i = i + 2) {
            while(n % i == 0) {
                // cout << i << " ";
                if( i == 5 )
                    ++fives;
                n = n/i;
            }
        }

        // n is a prime number greater than 2
        if( n > 2 ) {
            // cout << n << " ";
            if( n == 5 )
                ++fives;
        }

        return {twos, fives};
    }
    
public:
    string abbreviateProduct(int left, int right) {
    
        // trailing zeros
        int twos = 0;
        int fives = 0;
        for(int i = left; i <= right; ++i) {
            auto p = primeFactors(i);
            twos += p.first;
            fives += p.second;
        }
        // cout << "twos " << twos << " fives " << fives << " C " << min(twos, fives) << endl;
        int C = min(twos, fives);
        
        // last five
        int k2 = C, k5 = C;
        const int modlastfive = 100000;
        int last_five = 1;
        bool has_more_than_5 = false;
            
        const long modlastten = 10000000000;
        long last_ten = 1L;
        bool has_more_than_10 = false;
        
        double ff = 1; // first five
        
        for(int i = left; i <= right; ++i) {
            long x = i;
            ff = ff * x;
            while( ff > 100000 ) {
                ff = ff / 10;
            }
            
            while( x && x % 2 == 0 && k2 > 0 ) {
                --k2;
                x /= 2;
            }
            while( x && x % 5 == 0 && k5 > 0 ) {
                --k5;
                x /= 5;
            }
            if( (last_five * x) / modlastfive > 0 )
                has_more_than_5 = true;
            last_five = (last_five * x) % modlastfive;
            
            if( (last_ten * x) / modlastten > 0 )
                has_more_than_10 = true;
            last_ten = (last_ten * x) % modlastten;
            
        }
        // cout << "last_five " << last_five << endl;
        // cout << "has_more_than_5 " << has_more_than_5 << endl;
        // cout << "last_10 " << last_ten << endl;
        // cout << "has_more_than_10 " << has_more_than_10 << endl;
        // cout << "ff " << (int)ff << endl;
        
        /*
        // first five
        double xy = 0.0;
        for(int i = left; i <= right; ++i) {
            xy += log10(i);
        }
        // cout << "xy " << xy << endl;
        double y = xy - (long long)xy;
        // cout << "y " << y << endl;
        // + 1e-7 to handle floating point precission
        // see https://leetcode.com/problems/abbreviating-the-product-of-a-range/discuss/1646596/Python-or-Use-Log-Value-explained
        // solution was failing on left right
        // 5179 5536
        // 4838 6186
        // 7169 8652
        // 981  3082
        int first_five = floor(powf(10,y+4+1e-7));
        // cout << "first_five " << first_five << endl;
        */
        
        string ans;
        if( !has_more_than_5 ) {
            ans = to_string(last_five) + "e" + to_string(C);
        } else if( !has_more_than_10 ) {
            ans = to_string(last_ten) + "e" + to_string(C);
        } else {
            //add leading zeros in last five
            string str_last_five = to_string(last_five);
            while( str_last_five.size() < 5 )
                str_last_five = "0" + str_last_five;
            
            // ans = to_string(first_five) + "..." + str_last_five + "e" + to_string(C);
            ans = to_string((int)ff) + "..." + str_last_five + "e" + to_string(C);
        }
        
        
        return ans;
    }
};
