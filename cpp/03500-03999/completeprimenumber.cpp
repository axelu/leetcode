
// 3765. Complete Prime Number
// https://leetcode.com/problems/complete-prime-number/




class Solution {
private:
    bool isPrime(int n) {
        if( n == 2 || n == 3 )
            return true;

        if( n <= 1 || n % 2 == 0 || n % 3 == 0  )
            return false;

        for(int i = 5; i * i <= n; i += 6 ) {
            if( n % i == 0 || n % (i + 2) == 0 )
                return false;
        }

        return true;
    }

public:
    bool completePrime(int num) {
        if( !isPrime(num) )
            return false;

        string s = to_string(num);
        int s_sz = s.size();
        if( s_sz == 1 )
            return true;

        string prefix = s.substr(0,1); // cout << "initial prefix " << prefix << endl;
        string suffix = s.substr(1); // cout << "initial suffix " << suffix << endl;
        for(int i = 1; i <= s_sz - 1; ++i) {
            int n = stoi(prefix);
            if( !isPrime(n) )
                return false;
            n = stoi(suffix);
            if( !isPrime(n) )
                return false;

            prefix.push_back(s[i]);
            suffix.erase(suffix.begin());
        }

        return true;
    }
};
