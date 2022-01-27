
// 878. Nth Magical Number
// https://leetcode.com/problems/nth-magical-number/

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
    
    // binary search
    long search(long s, long e, long n, long a, long b, long l) {
        if( s == e )
            return s;
        
        long mid = s + ((e-s)/2L);
        // count of numbers below mid that are divisible by a and b
        long x = mid/a + mid/b - mid/l;
        if( x < n ) {
            return search(mid+1,e,n,a,b,l);
        } else {
            return search(s,mid,n,a,b,l);
        }
    }
        

public:
    int nthMagicalNumber(int n, int a, int b) {
        
        long l = lcm(a,b);
        
        // binary search
        long s = 0L;
        long e = (long)min(a,b) * (long)n;
        
        return search(s,e,n,a,b,l) % 1000000007;
        
        long mid;
        long x; // count of numbers below mid that are divisible by a and b
        while(s < e) {
            mid = s + ((e-s)/2L);
            x = mid/a + mid/b - mid/l;
            if( x < n )
                s = mid + 1;
            else
                e = mid;
        }

        return s % 1000000007;
    }
};
