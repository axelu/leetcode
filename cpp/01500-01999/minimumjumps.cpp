
// 1654. Minimum Jumps to Reach Home
// https://leetcode.com/problems/minimum-jumps-to-reach-home/



#include <iostream>
#include <cassert>
#include <chrono>

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
#include <cstring>
#include <climits>


using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
private:
    int r; // minimum number of jumps needed for the bug to reach its home
    int * pForbidden, * pSeen;
    int A,B,X;

    void dfs(int pos, int n, int backward) {
        // cout << pos << " " << n << " " << backward << endl;
        if( pos == X ) {
            r = min(r,n);
            return;
        } else if( pos < 0 ||
                 ( pos <= 2000 && pForbidden[pos] ) ||
                 ( pos > X && A >= B && pos-X > B ) ||
                 pos > 10000 || pSeen[pos] )  {
            return;
        }

        if( !backward ) pSeen[pos] = 1;

        // choice: forward or backward?
        // go forward
        dfs(pos+A,n+1,0);
        // go backward
        if( !backward ) dfs(pos-B,n+1,1);
    }
public:
    int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
        if( x == 0 ) return 0;

        int seen[10001]; memset(seen,0,sizeof seen);
        pSeen = seen;
        int fb[2001]; memset(fb,0,sizeof fb);
        fb[0] = 1;
        for(auto it = begin(forbidden); it != end(forbidden); ++it)
            fb[*it] = 1;
        pForbidden = fb;

        A = a;
        B = b;
        X = x;

        r = INT_MAX;
        dfs(a,1,0);

        return r == INT_MAX ? -1 : r;
    }
};

int main() {

    Solution s;
    vector<int> forbidden;
    int a,b,x,r;



    // case 60/94
    forbidden = {162,118,178,152,167,100,40,74,199,186,26,73,200,127,30,124,193,84,184,36,103,149,153,9,54,154,133,95,45,198,79,157,64,122,59,71,48,177,82,35,14,176,16,108,111,6,168,31,134,164,136,72,98};
    a = 29;
    b = 98;
    x = 80;
    r = s.minimumJumps(forbidden,a,b,x);
    cout << r << endl; // 121
    assert(r == 121);

    // case 92/94
    forbidden = {1998};
    a = 1999;
    b = 2000;
    x = 2000;
    r = s.minimumJumps(forbidden,a,b,x);
    cout << r << endl; // 3998
    assert(r == 3998);

    // case 94/94
    forbidden = {621,1511,1328,1602,414,1084,685,408,1547,1454,1138,1091,1624,871,1625,985,428,1116,475,1875,583,1762,1448,151,1869,1651,1590,1193,221,797,691,17,1027,1101,347,1085,1475,1021,1194,1787,1830,652,1177,2000,279,1782,886,1489,176,514,766,1758,696,651,31,1828,1606,784,914,1213,1848,1490,978,1992,1617,276,1311,1288,882,469,1457,803,795,222,851,528,662,179,1449,1414,1960,809,1781,722,1613,1738,378,1199,848,575,24,1644,1706,1521,744,1353,1403,1835,965,745,446,336,1324,191,1172,65,1063,569,1542,1844,831,844,355,748,920,562,1204,353,632,1953,1999,1381,573,512,421,1323,321,1966,1890,788,1540,864,1609,177,131,337,1819,1169,1641,1279,612,76,1263,885,1341,1982,1307,1837,1838,1483,1836,791,1637,303,1484,1577,1544,717,681,1571,1595,1650,189,1912,698,726,1740,1653,174,794,1067,594,518,686,1938,590,1665,833,1568,1543,556,665,906,487,1906,1620,210,646,1569,1296,1130,626,452,1206,1163,120,740,269,129,1859,166,1701,989,1382,56,1303,933,1549,550,258,589,300,1271,1536,489,60,1097,1494,367,1840,1212,1899,1477,1392,1286,661,1429,322,140,596,1945,1038,713,233,1006,813,968,1240};
    a = 7;
    b = 14;
    x = 0;
    r = s.minimumJumps(forbidden,a,b,x);
    cout << r << endl; // 0
    assert(r == 0);


    return 0;
}
