
// 3646. Next Special Palindrome Number
// https://leetcode.com/problems/next-special-palindrome-number/





// initialize once
set<long long> st;
bool init = false;

class Solution {
private:

    long long INF = 2666888888886662LL;

    void rec(int i, string s) {
        // cout << "rec i " << i << " s " << s << endl;

        int l = s.size();
        if( l > 8 )
            return;


        int lead_digit = s[l-1]-'0';

        // build the special palindrome number from s and insert
        int k = lead_digit % 2 ? s.size()-2 : s.size()-1;
        string t = s;
        for(; k >= 0; --k)
            t.push_back(s[k]);
        st.insert(stoll(t)); // we could check if > INF and not insert

        if( i == 10 )
            return;

        if( i != -1 ) {
            // we will be adding to the existing length
            // i will be either 2, 4, 6, or 8
            if( l + (i/2) > 8 )
                return;
        }

        if( i == -1 ) {
            // we are just starting out

            // we need to continue
            //    if lead_digit is odd continue at 2, 4 ,6, 8
            //    if lead_digit is even, continue at next greater even, ... 8
            int j = lead_digit % 2 ? 2 : lead_digit+2;
            for(; j <= 8; j += 2)
                rec(j, s);

        } else {
            // i is the digit we are adding
            // i will be either 2, 4, 6, or 8
            if( i == 2 ) {
                // lead digit will always be odd
                for(auto it = s.begin(); it != s.end(); ++it) {
                    s.insert(it, '2');
                    for(int j = 4; j <= 8; j += 2)
                        rec(j, s);
                    s.erase(it);
                }

            } else if( i == 4 ) {

                for(auto it0 = s.begin();; ++it0) {
                    s.insert(it0, '4');
                    for(auto it1 = it0+1;; ++it1){
                        s.insert(it1, '4');

                        for(int j = 6; j <= 8; j += 2)
                            rec(j, s);

                        s.erase(it1);
                        if( (lead_digit % 2 == 0 && it1 == s.end()) ||
                            (lead_digit % 2 == 1 && it1 + 1 == s.end()) )
                            break;
                    }
                    s.erase(it0);
                    if( (lead_digit % 2 == 0 && it0 == s.end()) ||
                        (lead_digit % 2 == 1 && it0 + 1 == s.end()) )
                        break;
                }

            } else if( i == 6 ) {

                for(auto it0 = s.begin();; ++it0) {
                    s.insert(it0, '6');
                    for(auto it1 = it0+1;; ++it1){
                        s.insert(it1, '6');

                        for(auto it2 = it1+1;; ++it2){
                            s.insert(it2, '6');

                            rec(8, s); // continue at 8

                            s.erase(it2);
                            if( (lead_digit % 2 == 0 && it2 == s.end()) ||
                                (lead_digit % 2 == 1 && it2 + 1 == s.end()) )
                                break;
                        }
                        s.erase(it1);
                        if( (lead_digit % 2 == 0 && it1 == s.end()) ||
                            (lead_digit % 2 == 1 && it1 + 1 == s.end()) )
                            break;
                    }
                    s.erase(it0);
                    if( (lead_digit % 2 == 0 && it0 == s.end()) ||
                        (lead_digit % 2 == 1 && it0 + 1 == s.end()) )
                        break;
                }

            } else { // i == 8

                for(auto it0 = s.begin();; ++it0) {
                    s.insert(it0, '8');
                    for(auto it1 = it0+1;; ++it1){
                        s.insert(it1, '8');

                        for(auto it2 = it1+1;; ++it2){
                            s.insert(it2, '8');

                                for(auto it3 = it2+1;; ++it3){
                                    s.insert(it3, '8');

                                rec(10, s); // continue at 10, not really, but it will record our number
                                s.erase(it3);
                                if( (lead_digit % 2 == 0 && it3 == s.end()) ||
                                    (lead_digit % 2 == 1 && it3 + 1 == s.end()) )
                                    break;
                            }
                            s.erase(it2);
                            if( (lead_digit % 2 == 0 && it2 == s.end()) ||
                                (lead_digit % 2 == 1 && it2 + 1 == s.end()) )
                                break;
                        }
                        s.erase(it1);
                        if( (lead_digit % 2 == 0 && it1 == s.end()) ||
                            (lead_digit % 2 == 1 && it1 + 1 == s.end()) )
                            break;
                    }
                    s.erase(it0);
                    if( (lead_digit % 2 == 0 && it0 == s.end()) ||
                        (lead_digit % 2 == 1 && it0 + 1 == s.end()) )
                        break;
                }

            }
        }

        return;
    }



public:
    long long specialPalindrome(long long n) {
        // 0 <= n <= 1e15
        // could we pregenerate the Special Palindrome Numbers?
        // largest possible answer
        // 0123456789012345 (16 digits)
        // 1000000000000000 1e15 = max n
        // 2666888888886662

        if( !init ) {

            for(int i = 1; i < 10; ++i) {
                int cnt = i % 2 ? (int)(i/2)+1 : (int)(i/2);
                string s(cnt, '0'+i);
                rec(-1, s);
            }
            st.insert(2666888888886662LL);

            // cout << "special palindrome count " << st.size() << endl;
            // for(long long sp: st)
            //     cout << sp << endl;

            init = true;
        }

        return *(st.upper_bound(n));
    }
};
