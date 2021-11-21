
// 372. Super Pow
// https://leetcode.com/problems/super-pow/






class Solution {
private:
    // adapted from problem 50. Pow(x, n)
    // https://leetcode.com/problems/powx-n/
    long mod = 1337;
    long rec(long x, long r, long f, long n) {
        // cout << "rec r " << r << " f " << f << " n " << n << endl;

        if( n == 1 ) {
            return r%mod;
        } else if( f * 2 == n ) {
            return ((r%mod)*(r%mod))%mod;
        } else if( f * 2 < n ) {
            return rec(x,((r%mod)*(r%mod))%mod,f*2,n);
        } else {
            return ((r%mod) * (rec(x,x,1,n-f)%mod))%mod;
        }
    }

    long div(int a, vector<int> b) {
        
        if( b.size() <= 10 ) {
            long n = 0;
            long f = pow(10,b.size()-1);
            for(int i = 0; i < b.size(); ++i) {
                n += b[i]*f;
                f /= 10;
            }
            return rec(a,a,1,n);   
        }
        
        // divide
        int n = b.size();
        bool isOdd = false;
        if( b[n-1]%2 == 1 ) {
            // odd
            isOdd = true;
            --b[n-1];
        }
        vector<int> v;
        int carry = 0,curr;
        for(int i = 0; i < n; ++i) {
            curr = b[i]+carry;
            carry = curr%2 == 1 ? 10 : 0;
            curr /= 2;
            if( i > 0 || curr > 0 )
                v.push_back(curr);
        }
        long t = div(a,v);
        
        // merge
        long ret = ((t%mod)*(t%mod))%mod;
        if( isOdd )
            ret = ((ret%mod)*(a%mod))%mod;
        
        return ret;        
    }
    
    
    
public:
    int superPow(int a, vector<int>& b) {
        if( a == 1 )
            return 1;
        
        a %= mod;
        
        int n = b.size();
        if( n == 1 && b[0] == 1 )
            return a;
        
        return div(a,b);
    }
};
