

// 3129. Find All Possible Stable Binary Arrays I
// https://leetcode.com/problems/find-all-possible-stable-binary-arrays-i/

class Solution {
private:
    int limit;
    long mod = 1000000007;
    
    long mem[201][201][2];
    
    // puts 0s in even buckets and 1s in odd buckets
    long reca(int zero, int one, int parity) {
        // parity 0 -> bucket for 0s, 1 -> bucket for 1s 
        
        // we will put k items in the current bucket, with 1 <= k <= limit
        
        if( zero == 0 && one == 0 )
            return 1L;
        else if( zero == 0 )
            return one <= limit ? 1L : 0L;
        else if( one == 0 )
            return zero <= limit ? 1L : 0L;
        
        // Are we at a bucket for 0s but don't have any more zero's?
        if( parity == 0 && zero == 0 )
            return 0L;
        // Are we at a bucket for 1s but don't have any more one's?
        if( parity == 1 && one == 0 )
            return 0L;
        
        if( mem[zero][one][parity] != -1L )
            return mem[zero][one][parity];
        
        long ret = 0L;

        if( parity == 0 ) {
            for(int i = 1; i <= min(limit,zero); ++i)
                ret = (ret + reca(zero - i, one, 1)) % mod;
        } else {
            for(int i = 1; i <= min(limit,one); ++i)
                ret = (ret + reca(zero, one - i, 0)) % mod;
        }
            
        return mem[zero][one][parity] = ret;
    }
    
    // puts 1s in even buckets and 0s in odd buckets
    long recb(int zero, int one, int parity) {
        // parity 0 -> bucket for 1s, 1 -> bucket for 0s 
        
        // we will put k items in the current bucket, with 1 <= k <= limit
        
        if( zero == 0 && one == 0 )
            return 1L;
        else if( zero == 0 )
            return one <= limit ? 1L : 0L;
        else if( one == 0 )
            return zero <= limit ? 1L : 0L;
        
        // Are we at a bucket for 0s but don't have any more zero's?
        if( parity == 1 && zero == 0 )
            return 0L;
        // Are we at a bucket for 1s but don't have any more one's?
        if( parity == 0 && one == 0 )
            return 0L;
        
        if( mem[zero][one][parity] != -1L )
            return mem[zero][one][parity];

        long ret = 0L;

        if( parity == 1 ) {
            for(int i = 1; i <= min(limit,zero); ++i)
                ret = (ret + recb(zero - i, one, 0)) % mod;
        } else {
            for(int i = 1; i <= min(limit,one); ++i)
                ret = (ret + recb(zero, one - i, 1)) % mod;
        }
            
        return mem[zero][one][parity] = ret;
    }

public:
    int numberOfStableArrays(int zero, int one, int limit) {
        this->limit = limit;
        
        memset(mem,-1,sizeof mem);
        long a = reca(zero, one, 0); // cout << "a " << a << endl;
        memset(mem,-1,sizeof mem);
        long b = recb(zero, one, 0); // cout << "b " << b << endl;
        
        return (a + b) % mod;
    }
};

