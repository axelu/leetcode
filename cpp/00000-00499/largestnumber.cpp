
// 179. Largest Number
// day 25 September 2020 challenge
// https://leetcode.com/explore/challenge/card/september-leetcoding-challenge/557/week-4-september-22nd-september-28th/3472/
// https://leetcode.com/problems/largest-number/


#include <iostream>
#include <cassert>
#include <chrono>
#include <bitset>

#include <vector>
#include <algorithm>
#include <stack>

using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        if( nums.empty() ) return "";
        // if( nums.size() == 1 ) return to_string(nums[0]);
        if( find_if(nums.begin(), nums.end(), [](int a){return a > 0;}) == nums.end() ) return "0";

        auto comp = [](int a, int b) {
            if( a == b || b == 0 ) {
                return true;
            } else if( a == 0 ) {
                return false;
            }

            // a
            vector<int> sa;
            while(a > 0) {
                int rem = a % 10;
                sa.insert(sa.begin(), rem);
                a /= 10;
            }

            // b
            vector<int> sb;
            while(b > 0) {
                int rem = b % 10;
                sb.insert(sb.begin(), rem);
                b /= 10;
            }

            bool r = true;
            auto sasz = sa.size();
            auto sbsz = sb.size();
            int i = 0;
            int k = 0;
            while( i < sasz || k < sbsz ) {
                if( i == sasz ) i = 0;
                if( k == sbsz ) k = 0;
                a = sa[i];
                b = sb[k];
                if( a > b ) {
                    break;
                } else if ( a < b ) {
                    r = false;
                    break;
                }
                ++i;
                ++k;
            }

            return r;
        };

        sort(nums.begin(), nums.end(), comp);
        for(int i : nums) cout << i << " ";
        cout << endl;

        // if( nums[0] == 0 ) return "0";
        string r = "";
        for(int i : nums) r += to_string(i);

        return r;
    }
};

int main() {

    chrono::time_point<chrono::system_clock> start;
    chrono::time_point<chrono::system_clock> end;
    chrono::duration<double> elapsed_seconds;

    // start = chrono::system_clock::now();
    // do something
    // end = chrono::system_clock::now();
    // elapsed_seconds = end - start;
    // cout << "elapsed_seconds " << elapsed_seconds.count() << endl;

    Solution s;
    vector<int> nums;
    string r;

    nums = {0,0,0};
    r = "0";
    assert(s.largestNumber(nums) == r);

    nums = {0};
    r = "0";
    assert(s.largestNumber(nums) == r);

    nums = {10};
    r = "10";
    assert(s.largestNumber(nums) == r);

    nums = {9999};
    r = "9999";
    assert(s.largestNumber(nums) == r);


    nums = {3,30,34,5,9};
    r = "9534330";
    assert(s.largestNumber(nums) == r);

    nums = {3,0};
    r = "30";
    assert(s.largestNumber(nums) == r);

    nums = {3,0,0,4};
    r = "4300";
    assert(s.largestNumber(nums) == r);

    nums = {2147483647,2147483647,0,0,0};
    r = "21474836472147483647000";
    assert(s.largestNumber(nums) == r);

    // case 52/222 initially runtime error
    nums = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    r = "0";
    assert(s.largestNumber(nums) == r);

    // case 137/222 initially wrong answer
    nums = {824,938,1399,5607,6973,5703,9609,4398,8247};
    r = "9609938824824769735703560743981399";
    assert(s.largestNumber(nums) == r);

    nums = {82478247,938,1399,5607,6973,5703,9609,4398,8247};
    r = "960993882478247824769735703560743981399";
    assert(s.largestNumber(nums) == r);

    nums = {824782478,938,1399,5607,6973,5703,9609,4398,8247};
    r = "9609938824782478824769735703560743981399";
    assert(s.largestNumber(nums) == r);


    return 0;
}

