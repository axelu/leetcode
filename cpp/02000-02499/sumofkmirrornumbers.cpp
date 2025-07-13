
// 2081. Sum of k-Mirror Numbers
// https://leetcode.com/problems/sum-of-k-mirror-numbers/

// ran this helper locally to pre-calculate
// helper is based on my original solution
/*

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

*/

long long res[8][30] = {{1,4,9,16,25,58,157,470,1055,1772,9219,18228,33579,65802,105795,159030,212865,286602,872187,2630758,4565149,6544940,9674153,14745858,20005383,25846868,39347399,759196316,1669569335,2609044274},{1,3,7,15,136,287,499,741,1225,1881,2638,31730,80614,155261,230718,306985,399914,493653,1342501,2863752,5849644,9871848,14090972,18342496,22630320,28367695,36243482,44192979,71904751,155059889},{1,3,6,11,66,439,832,1498,2285,3224,11221,64456,119711,175366,233041,739646,2540727,4755849,8582132,12448815,17500320,22726545,27986070,33283995,38898160,44577925,98400760,721411086,1676067545,53393239260},{1,3,6,10,16,104,356,638,1264,1940,3161,18912,37793,10125794,20526195,48237967,78560270,126193944,192171900,1000828708,1832161846,2664029984,3500161622,4336343260,6849225412,9446112364,12339666346,19101218022,31215959143,43401017264},{1,3,6,10,15,22,77,188,329,520,863,1297,2074,2942,4383,12050,19827,41849,81742,156389,325250,1134058,2043967,3911648,7009551,11241875,15507499,19806423,24322577,28888231},{1,3,6,10,15,21,29,150,321,563,855,17416,83072,2220384,6822448,13420404,20379000,29849749,91104965,321578997,788407661,1273902245,1912731081,2570225837,3428700695,29128200347,69258903451,115121130305,176576075721,241030621167},{1,3,6,10,15,21,28,37,158,450,783,1156,1570,2155,5818,14596,27727,41058,67520,94182,124285,154588,362290,991116,1651182,3148123,5083514,7054305,11253219,66619574},{1,3,6,10,15,21,28,36,227,509,882,1346,1901,2547,3203,10089,35841,63313,105637,156242,782868,2323319,4036490,5757761,7586042,9463823,11349704,13750746,16185088,18627530}};

class Solution {
public:
    long long kMirror(int k, int n) {
        return res[k-2][n-1];
    }
};

// below solution passed 97/97 test cases 9/27/2023 and was accepted, 
// but does not pass 6/23/2025
// case 97 fails with TLE, but runs in 0ms, so unclear why TLE on that test case
// case 97 k = 9, n = 17

class Solution {
private:
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

public:
    long long kMirror(int k, int n) {

        int cnt = 0;
        long long ans = 0LL;
        long long i = 1LL;
        queue<long long> q;
        while( cnt < n ) {
            auto p = createPalindrome(i);
            if( p.first > q.front() ) {
                // process queue
                while( !q.empty() ) {
                    long long palin = q.front();
                    q.pop();
                    string s = basekencode(palin,k);
                    if( isPalindrome(s) ) {
                        ans += palin;
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
                ++cnt;
                if( cnt == n )
                    break;
            }
            q.push(p.second);
            ++i;
        }

        return ans;
    }
};
