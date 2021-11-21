
// 327. Count of Range Sum
// https://leetcode.com/problems/count-of-range-sum/


#include <iostream>
#include <cassert>
#include <chrono>

#include <stack>
#include <vector>
#include <string>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <set>
#include <iterator>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <map>
#include <cmath>
#include <bitset>
#include <cstring>
#include <climits>


using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789



int gen_random_int() {
    const int BITS_PER_RAND = (int)(log2(RAND_MAX/2 + 1) + 1.0);
    long ret = 0;
    for (int i = 0; i < sizeof(int) * CHAR_BIT; i += BITS_PER_RAND) {
        ret <<= BITS_PER_RAND;
        ret |= rand();
    }
    return ret;
}

class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        auto n = nums.size();
        if( n == 0 ) return 0;

        // max running sum 10e4 * 2147483647
        // min running sum 10e4 * -2147483648
        long sum = 0L; // running sum for index 0

        vector<vector<long>> rsum(n, vector<long>(2,{}));
        int r = 0;
        for(int i = 0; i < n; ++i) {
            sum += (long)nums[i];
            if( sum >= lower && sum <= upper ) {
                ++r; // counting for 0,0 to 0,n-1
                // cout << sum << endl;
            }
            rsum[i] = {sum,i};
        }
        // cout << "r intermediate " << r << endl;
        sort(begin(rsum),end(rsum));

        long offset = 0;
        for(int i = 1; i < n; ++i) {
            offset += (long)nums[i-1];
            vector<long> l = {(long)lower+offset,0};
            auto it = lower_bound(begin(rsum),end(rsum),l);
            while( it != end(rsum) ) {
                // cout << "here" << endl;
                if( (*it)[0] > (long)upper+offset ) break;
                if( (*it)[1] >= i ) {
                    ++r;
                    /*
                    cout << "offset " << offset << endl;
                    cout << "lower + offset " << (long)lower+offset << endl;
                    cout << "upper + offset " << (long)upper+offset << endl;

                    cout << "i " << i << endl;
                    cout << "j " << (*it)[1] << endl;
                    // doublecheck
                    long t = 0;
                    for(int k = i; k <= (*it)[1]; ++k)
                        t += (long)nums[k];
                    cout << t << endl;
                    */
                }
                ++it;
             }
        }

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
    int r,lower,upper;

    // expect 3
    nums = {0,0};
    lower = 0;
    upper = 0;
    r = s.countRangeSum(nums,lower,upper);
    cout << "r " << r << endl;

    // return 0;

    nums = {-1899399272,623370525,-1872362387,-1742292031,-590467191,-125328405,-1558503963,-1123814020,2123036273,189526096,651437128,1739681859,-414045109,-1190343471,-1593361456,804687614,-1865103878,1721718770,-192610317,103231960,1918119627,131172829,2055413729,896203312,1146474496,-1276134575,-1824267547,329225348,34535973,-1295231725,1087513173,-756618913,-1209969619,-220089673,944526597,-38173795,-138954157,1074778241,-899642156,1799942279,-1238256333,2044743966,987354989,1141614408,1512851191,-536934520,-644161428,-324709988,1819030073,-1109227334,1485826275,-816248049,1093081554,-1031635605,82028099,-1707211909,1292114379,-2071268466,564017723,1153876683,-1083271375,-1765217664,-676611269,713403447,1660239984,1758491826,-1543225015,197971081,-946709677,-256704062,2082125800,-2020909812,-1626383913,1358742252,1420618608,-1132980923,-1165406198,-1390085570,-693158942,1447884985,1074977640,1965663653,-146346706,1229092813,-817513437,-1957737961,-991527220,-1803598401,-1628375107,-1532793674,-79720862,-2017892914,878477761,1207822770,-1937176958,-995083787,1567117271,817036956,-1160752696,-1819769466};
    lower = 871034872;
    upper = 1556563816;

    // expect 290
    cout << lower << " " << upper << endl;
    r = s.countRangeSum(nums,lower,upper);
    cout << "r " << r << endl;

    return 0;



    srand(time(nullptr)); // use current time as seed for random generator
    int rdm;
    int n = 100;
    for(int i = 0; i < n; ++i) {
        rdm = gen_random_int(); // random in the range INT_MIN and INT_MAX
                                // -2147483648 to 2147483647
        nums.push_back(rdm);
    }
    lower = gen_random_int();
    upper = gen_random_int();
    while( upper < lower ) upper = gen_random_int();

    start = chrono::system_clock::now();
    r = s.countRangeSum(nums,lower,upper);
    end = chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "elapsed_seconds " << elapsed_seconds.count() << endl;
    cout << "r " << r << endl;


    for(int i : nums)
        cout << "," << i;
    cout << endl;
    cout << "lower " << lower << endl;
    cout << "upper " << upper << endl;


    return 0;
}
