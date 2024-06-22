
// 2967. Minimum Cost to Make Array Equalindromic
// https://leetcode.com/problems/minimum-cost-to-make-array-equalindromic/




//    1234567
//    498
//    2001  -> 2002   -> 1991
//    201   -> 202    -> 191
//    43    -> 44     -> 33
//    100000 -> 100001 -> 100 -> 99999
//    2003 -> 2112
//    9780  -> 9779 -> 999000 -> 999999 -> 998899

class Solution {
private:

    int less_equal_palindrome(int x) {
        // returns greatest palindromic number less than x or equal x
        if( x == 10 )
            return 9;

        string str_x = to_string(x);
        int n = str_x.size();
        if( n == 1 )
            return x;

        string str_p(n,'#');
        for(int i = 0, j = n-1; i <= j; ++i,--j) {
            str_p[i] = str_x[i];
            str_p[j] = str_x[i];
        }
        int p = stoi(str_p);
        if( p <= x )
            return p;

        int t = n / 2;
        if( n % 2 )
            ++t;

        string s(t,'#');
        for(int i = 0; i < t; ++i)
            s[i] = str_x[i];
        int s_int = stoi(s);
        --s_int;
        s = to_string(s_int);
        if( s.size() < t ) {
            str_p.resize(n-1);
            for(int i = 0; i < n-1; ++i)
                str_p[i] = '9';
            p = stoi(str_p);
            return p;
        }

        for(int i = 0, j = n-1; i <= j; ++i,--j) {
            str_p[i] = s[i];
            str_p[j] = s[i];
        }
        p = stoi(str_p);

        return p;
    }

    int greater_equal_palindrome(int x) {
        // returns smallest palindromic number greater than x or equal x
        string str_x = to_string(x);
        int n = str_x.size();
        if( n == 1 )
            return x;

        string str_p(n,'#');
        for(int i = 0, j = n-1; i <= j; ++i,--j) {
            str_p[i] = str_x[i];
            str_p[j] = str_x[i];
        }
        int p = stoi(str_p);
        if( p >= x )
            return p;

        int t = n / 2;
        if( n % 2 )
            ++t;

        string s(t,'#');
        for(int i = 0; i < t; ++i)
            s[i] = str_x[i];
        int s_int = stoi(s);
        ++s_int;
        s = to_string(s_int);
        for(int i = 0, j = n-1; i <= j; ++i,--j) {
            str_p[i] = s[i];
            str_p[j] = s[i];
        }
        p = stoi(str_p);

        return p;
    }

    long long get_cost(vector<int>& nums, long long x) {
        long long cost = 0LL;
        for(long long i: nums)
            cost += abs(i - x);
        return cost;
    }

public:
    long long minimumCost(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(),nums.end());

        int mid = n/2;
        int median;
        if( n % 2 ) {
            median = nums[mid];
        } else {
            median = (nums[mid-1] + nums[mid])/2;
        }

        int a = less_equal_palindrome(median);
        int b = greater_equal_palindrome(median);

        return min(get_cost(nums,a), get_cost(nums,b));
    }
};
