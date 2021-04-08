#include <iostream>
#include <cassert>
#include <chrono>
#include <string>
// #include <map>
// #include <vector>

// https://leetcode.com/problems/multiply-strings/

using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
        if ( num1 == "0" || num2 == "0" ) return "0";
        if ( num1.empty() || num2.empty() ) return "";
        if ( num1 == "1" ) return num2;
        if ( num2 == "1" ) return num1;

        string r;
        int e1 = 0;
        auto it1 = num1.rbegin();

        while( it1 != num1.rend() ) {

            int e2 = 0;
            auto it2 = num2.rbegin();
            while ( it2 != num2.rend() ) {

                int p = (*it1 - '0') * (*it2 - '0');
                int idx = e1 + e2;

                if ( (r.size() - 1) < idx || r.size() == 0 ) {

                    r.insert(r.begin(), (p % 10) + '0');
                    if ( p > 9 ) r.insert(r.begin(), (p/10) + '0');

                } else if ( (r.size() - 1) == idx ) {

                    p += r[0] - '0';
                    r[0] = (p % 10) + '0';
                    if ( p > 9 ) r.insert(r.begin(), (p/10) + '0');

                } else {

                    while ( (r.size() - 1) > idx || p > 0 ) {

                        int base = (r.size() - 1) - idx;
                        p += r[base] - '0';
                        r[base] = (p % 10) + '0';
                        p /= 10;

                        idx++;

                        if ( (r.size() - 1) == idx && p > 0 ) {

                            p += r[0] - '0';
                            r[0] = (p % 10) + '0';
                            if ( p > 9 ) r.insert(r.begin(), (p/10) + '0');
                            break;
                        }
                    }
                }

                e2++;
                ++it2;
            }

            e1++;
            ++it1;
        }

        return r;
    }
};

int main() {

    Solution s;

    assert(s.multiply("56", "23") == "1288");


    string s1 = "9202953157832105909627474081198239446064767189691555493013224067111";
    string s2 = "39426334295360801314639055998391233088629155358611196023732663716316308315071834";

    chrono::time_point<std::chrono::system_clock> start, end; 
  
    start = chrono::system_clock::now(); 

    string r = s.multiply(s1, s2);

    end = std::chrono::system_clock::now(); 
    std::chrono::duration<double> elapsed_seconds = end - start; 
  
    cout << "elapsed time: " << elapsed_seconds.count() << endl; 

    cout << r << endl;

    assert(r == "362838707705234942674725327663776668211969177660797521970833279727507495362433786003107626316387484748633290231302646855731489019146439265601851574");


    s1 = "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999";
    s2 = "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999";


    start = chrono::system_clock::now(); 

    r = s.multiply(s1, s2);

    end = std::chrono::system_clock::now(); 
    elapsed_seconds = end - start; 
  
    cout << "elapsed time: " << elapsed_seconds.count() << endl; 

    cout << r << endl;

    // result has 218 digits
    assert(r == "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999980000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");



    return 0;
}
