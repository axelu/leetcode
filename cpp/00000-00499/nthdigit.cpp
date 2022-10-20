
// 400. Nth Digit
// https://leetcode.com/problems/nth-digit/



class Solution {
private:
    long solve(long n) {
        // 1 digit  2 digits    3 digits      ...
        // 1 * 9  , 2 * (99-9), 3 * (999-99), ...
        
        long mult = 1;
        long addt = 9;
        long res  = 0;
        while(true) {
            long a = addt > n ? n : addt;
            long b = addt/10;
            a -= b;
            
            res += mult * a;
            
            if( addt >= n )
                break;
            
            ++mult;
            addt = addt*10 + 9;
        }
        
        return res;
    }
    
    // binary search lower bound
    int search(int s, int e, long target) {
        // cout << "search s " << s << " e " << e << endl;
        if( s > e )
            return -1;
        
        int mid = s + ((e-s)/2);
        long n = solve(mid);
        if ( n >= target ) {
            // can we do better?
            int t = search(s,mid-1,target);
            return t != -1 ? t : mid;
        }
        return search(mid+1,e,target);
    }
    
public:
    int findNthDigit(int n) {
        // trial and error determined that 1,2,3,...,300000000
        // results in 2479149774 digits using our solve function
        //  1 <= n <= 2147483647 ( = 2^31 - 1 = INT_MAX)
        // hence we could use 300000000 as our upper bound
        
        int a = search(1,300000000,n);
        long t = solve(a);
        
        string s = to_string(a);
        
        char c = s[s.size()-1 - (t-n)];
        return c - 48;
    }
};
