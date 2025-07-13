#include <iostream>
#include <queue>

using namespace std;

    bool isPalindrome(string& s) {
        if( s.size() == 1 ) 
            return true;

        bool p = true;

        auto fi = s.begin();
        auto ri = s.rbegin();
        while( fi <= ri.base() ) {
            if( *fi == *ri ) {
                ++fi;
                ++ri;
            } else {
                p = false;
                break;
            }
        }

        return p;
    }

    // base k encoding
    string basekencode(long long num, int k) {
        if( num == 0 ) 
            return "0";
        string ret = "";
        long rem;
        while( num > 0 ) {
            rem = num % k;
            ret = to_string(rem) + ret;
            num /= k;
        }
        return ret;
    }
    
    // inspired by https://www.geeksforgeeks.org/generate-palindromic-numbers-less-n/
    pair<long long,long long> createPalindrome(long long input) {
        // let d be the number of digits in input
        // generates 2d-1 and 2d 'palindrome' from input
        // examples
        //    input 1 -> 1,11
        //    input 10 -> 101,1001
        
        long long n = input / 10;
        long long palinodd = input;

        while( n > 0 ) {
            palinodd = palinodd * 10 + (n % 10);
            n /= 10;
        }
        
        n = input;
        long long palineven = input;

        while( n > 0 ) {
            palineven = palineven * 10 + (n % 10);
            n /= 10;
        }
        
        return {palinodd,palineven};
    }



int main() {


	long long res[8][30];        

        for(int k = 2; k <= 9; ++k) {
            for(int n = 1; n <= 30; ++n) {
        
                int cnt = 0;
                long long ans = 0LL;
                long long i = 1LL;
                queue<long long> q;
                while( cnt < n ) {
                    auto p = createPalindrome(i);
                    if( !q.empty() && p.first > q.front() ) {
                        // process queue
                        while( !q.empty() ) {
                            long long palin = q.front();
                            q.pop();
                            string s = basekencode(palin,k);
                            if( isPalindrome(s) ) {
                                ans += palin;
                                res[k-2][cnt] = ans;
                                ++cnt;
                                if( cnt == n )
                                    break;
                            }
                        }
                    }
                    if( cnt == n )
                        break;
                    string s = basekencode(p.first,k);
                    if( isPalindrome(s) ) {
                        ans += p.first;
                        res[k-2][cnt] = ans;
                        ++cnt;
                        if( cnt == n )
                            break;
                    }
                    q.push(p.second);
                    ++i;
                }
        
            }
        }


    cout << "{";
    for(int k = 2; k <= 9; ++k) {
        if( k > 2 ) cout << ",";
        cout << "{";
        for(int n = 1; n <= 30; ++n) {
            if( n > 1 ) cout << ",";
            cout << res[k-2][n-1];
        }
        cout << "}";
    }
    cout << "}" << endl;

	return 0;

}


// clang++ --std=c++17 sumofkmirrornumbers_helper.cpp -o sumofkmirrornumbers_helper
