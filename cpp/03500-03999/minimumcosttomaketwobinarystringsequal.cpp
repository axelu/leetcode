
// 3800. Minimum Cost to Make Two Binary Strings Equal
// https://leetcode.com/problems/minimum-cost-to-make-two-binary-strings-equal/

class Solution {
private:
    long long flipCost, swapCost, crossCost;

    unordered_map<long long, long long> mem;

    long long rec(int A, int B) {
        // cout << "rec A " << A << " B " << B << endl;

        long long AB = A + B;
        if( AB == 0LL )
            return 0LL;
        if( AB == 1LL )
            return (long long)flipCost;

        long long ret = AB * flipCost;        
        if( AB == 2LL ) {
            if( A == 1 && B == 1 )
                ret = min(ret, swapCost);
            else
                ret = min(ret, crossCost + swapCost);
            return ret;
        }

        long long key = ((long long)A<<17) + B;
        auto f = mem.find(key);
        if( f != mem.end() )
            return f->second;

        // we have a choice
        //    flip OR
        //    swap if we can OR
        //    cross+swap if we can

        if( A > 0 )
            ret = min(ret, flipCost + rec(A-1, B));
        if( B > 0 )
            ret = min(ret, flipCost + rec(A, B-1));
        if( A > 0 && B > 0 )
            ret = min(ret, swapCost + rec(A-1, B-1));
        if( A > 1 )
            ret = min(ret, crossCost + swapCost + rec(A-2, B));
        if( B > 1 )
            ret = min(ret, crossCost + swapCost + rec(A, B-2));

        return mem[key] = ret;
    }

public:
    long long minimumCost(string s, string t, int flipCost, int swapCost, int crossCost) {
        int n = s.size(); // 1 <= n <= 1e5; s.size() == t.size()

        // let us distinguish indices of two types A and B
        //   A B
        // s 1 0
        // t 0 1
        // we are only interested in indices where s[i] != t[i]
        // let us count indices of type A and B
        int A = 0, B = 0;
        for(int i = 0; i < n; ++i)
            if( s[i] == '1' && t[i] == '0' )
                ++A;
            else if( s[i] == '0' && t[i] == '1' )
                ++B;
        
        if( A + B == 0 )
            return 0LL;

        // cout << "A " << A << " B " << B << endl;

        //                                  net 
        // swap             --A     --B     -2
        // flip A           --A             -1
        // flip B                   --B     -1
        // cross            --A     ++B      0
        // cross            ++A     --B      0
        // a cross by itself has no net effect !!!
        // we always need to combine a cross with a swap
        //     combining a cross with a flip makes no sense !!!
        // cross            --A     ++B
        //      swap        --A     --B     -2  -2*A   
        // cross            ++A     --B
        //      swap        --A     --B     -2  -2*B   

        // this->flipCost = flipCost;
        // this->swapCost = swapCost;
        // this->crossCost = crossCost;
        // return rec(A, B);

        // greedy options
        // a option 1: apply flip operation to all
        // b option 2a: swap as many as we can (min(A,B)) + remaining flips
        // c option 2b: swap as many as we can (min(A,B)) + remaining / 2 (cross+swap) + flip (if odd)
        // d option 3a: cross+swap A, cross+swap B, flip rem A (if odd) + flip rem B (if odd)
        // e option 3b: cross+swap A, cross+swap B, swap rem A and rem B if both odd 
        // are there other options ???
        long long AB = A + B;

        long long a = AB * flipCost;
        
        long long b = min(A, B) * (long long)swapCost;
        b = b + abs(A-B) * (long long)flipCost;

        long long c = min(A, B) * (long long)swapCost;
        c = c + (long long)(abs(A-B)/2) * (long long)(crossCost+swapCost);
        if( abs(A-B) % 2 )
            c = c + (long long)flipCost;

        long long d = (long long)(A/2) * (long long)(crossCost+swapCost); 
        d = d + (long long)(B/2) * (long long)(crossCost+swapCost);
        if( A % 2 )
            d = d + (long long)flipCost;
        if( B % 2 )
            d = d + (long long)flipCost;

        long long e = (long long)(A/2) * (long long)(crossCost+swapCost); 
        e = e + (long long)(B/2) * (long long)(crossCost+swapCost);
        if( A % 2 && B % 2 )
            e = e + (long long)swapCost;
        else if( A % 2 || B % 2 )
            e = e + (long long)flipCost;
        
        // cout << "a " << a << " b " << b << " c " << c << " d " << d << " e " << e << endl;

        return min({a,b,c,d,e});
    }
};

// passes 703/783 test cases, then TLE as of 1/11/2026
// test case 704 runs in about ~1800ms returning correct result, but is obviously too slow


class Solution {
private:
    long long flipCost, swapCost, crossCost;

    unordered_map<long long, long long> mem;

    long long rec(int A, int B) {
        // cout << "rec A " << A << " B " << B << endl;

        long long AB = A + B;
        if( AB == 0LL )
            return 0LL;
        if( AB == 1LL )
            return (long long)flipCost;

        long long ret = AB * flipCost;
        if( AB == 2LL ) {
            if( A == 1 && B == 1 )
                ret = min(ret, swapCost);
            else
                ret = min(ret, crossCost + swapCost);
            return ret;
        }

        long long key = ((long long)A<<17) + B;
        auto f = mem.find(key);
        if( f != mem.end() )
            return f->second;

        // we have a choice
        //    flip OR
        //    swap if we can OR
        //    cross+swap if we can

        if( A > 0 )
            ret = min(ret, flipCost + rec(A-1, B));
        if( B > 0 )
            ret = min(ret, flipCost + rec(A, B-1));
        if( A > 0 && B > 0 )
            ret = min(ret, swapCost + rec(A-1, B-1));
        if( A > 1 )
            ret = min(ret, crossCost + swapCost + rec(A-2, B));
        if( B > 1 )
            ret = min(ret, crossCost + swapCost + rec(A, B-2));

        return mem[key] = ret;
    }

public:
    long long minimumCost(string s, string t, int flipCost, int swapCost, int crossCost) {
        int n = s.size(); // 1 <= n <= 1e5; s.size() == t.size()

        // let us distinguish indices of two types A and B
        //   A B
        // s 1 0
        // t 0 1
        // we are only interested in indices where s[i] != t[i]
        // let us count indices of type A and B
        int A = 0, B = 0;
        for(int i = 0; i < n; ++i)
            if( s[i] == '1' && t[i] == '0' )
                ++A;
            else if( s[i] == '0' && t[i] == '1' )
                ++B;

        if( A + B == 0 )
            return 0LL;

        // cout << "A " << A << " B " << B << endl;

        this->flipCost = flipCost;
        this->swapCost = swapCost;
        this->crossCost = crossCost;

        //                                  net
        // swap             --A     --B     -2
        // flip A           --A             -1
        // flip B                   --B     -1
        // cross            --A     ++B      0
        // cross            ++A     --B      0
        // a cross by itself has no net effect !!!
        // we always need to combine a cross with a swap
        //     combining a cross with a flip makes no sense !!!
        // cross            --A     ++B
        //      swap        --A     --B     -2  -2*A
        // cross            ++A     --B
        //      swap        --A     --B     -2  -2*B

        return rec(A, B);
    }
};
