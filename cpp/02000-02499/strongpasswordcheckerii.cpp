
// 2299. Strong Password Checker II
// https://leetcode.com/problems/strong-password-checker-ii/



class Solution {
public:
    bool strongPasswordCheckerII(string password) {
        int n = password.size();
        if( n < 8 )
            return false;

        bool has_lower = false;
        bool has_upper = false;
        bool has_digit = false;
        bool has_special = false;
        unordered_set<char> special{'!','@','#','$','%','^','&','*','(',')','-','+'};

        for(int i = 0; i < n; ++i) {
            if( i > 0 && password[i-1] == password[i] )
                return false;

            if( islower(password[i]) )
                has_lower = true;
            if( isupper(password[i]) )
                has_upper = true;
            if( isdigit(password[i]) )
                has_digit = true;
            if( special.count(password[i]) )
                has_special = true;
        }

        return has_lower && has_upper && has_digit && has_special;
    }
};
