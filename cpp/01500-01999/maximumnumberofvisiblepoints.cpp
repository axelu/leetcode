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
#include <cmath>

// 1610. Maximum Number of Visible Points
// https://leetcode.com/problems/maximum-number-of-visible-points

using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
private:
    double offset(int& px, int& py, int& lx, int& ly) {
        // calc angle counterclockwise from east to point pivoting on location
        // NOTE: will not be called for points at location!

        int a = py - ly;
        int b = px - lx;

        double pi = 3.14159265;
        double deg = atan2(a, b) * 180 / pi;
        return deg < 0 ? deg + 360 : deg;
    }
public:
    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        auto n = points.size();
        if( n == 1 ) return 1;
        auto norg = n;

        int r = 0;

        int lx = location[0];
        int ly = location[1];

        double offsets[100000];
        for(int i = 0; i < 100000; ++i) offsets[i] = 360.0;
        for(int i = 0; i < n; ++i) {
            int px = points[i][0];
            int py = points[i][1];
            if( px == lx && py == ly) {
                --n;
                ++r;
                continue;
            }
            offsets[i] = offset(px, py, lx, ly);
        }

        if( n <= 1 ) return norg;   // all or all but one point are at location
        double w = (double) angle;  // field of view

        sort(offsets, offsets + n);

        int c = 0;
        int i = 0;
        double o1 = offsets[i];
        int j = 1;
        while(true) {
            double o2 = j < n ? offsets[j] : 360.0 + offsets[j-n];
            double od = o2 - o1;
            if( od <= w + 1e-9 ) { // floating point compare
                c = max(c, j - i);
            } else {
                while( od > w && i < n - 1 ) {
                    ++i;
                    o1 = offsets[i];
                    od = o2 - o1;
                }
            }
            if( i == n - 1 && od > w ) break;
            ++j;
        }
        
        return r + c + 1;
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

    // smallest angle in degrees (besides 0)
/*
    int a = 0;          // 1
    int b = 1000000000; // 1000000000

    long long int a2 = (long long int)a*a;
    long long int b2 = (long long int)b*b;
    // c = sqrt((a*a)+(b*b));
    double c = sqrt(a2+b2);
    double rad = asin(a/c);
    double pi = 3.14159;
    double deg = rad * (180/pi);
    cout << deg << endl;
*/


    Solution s;
    vector<vector<int>> points;
    int angle;
    vector<int> location;
    int r;
    
    cout << "Example 1" << endl;
    points = {{2,1},{2,2},{3,3}};
    angle = 90;
    location = {1,1};
    r = s.visiblePoints(points, angle, location);
    cout << "result " << r << endl;
    assert(r == 3);

    cout << "Example 2" << endl;
    points = {{2,1},{2,2},{3,4},{1,1}};
    angle = 90;
    location = {1,1};
    r = s.visiblePoints(points, angle, location);
    cout << "result " << r << endl;
    assert(r == 4);

    cout << "Example 3" << endl;
    points = {{1,0},{2,1}};
    angle = 13;
    location = {1,1};
    r = s.visiblePoints(points, angle, location);
    cout << "result " << r << endl;
    assert(r == 1);

    // case 39 / 109 initially wrong answer 12 expected 11
    cout << "case 39" << endl;
    points = {{673648153,788793266},{812553910,829107321},{562844327,521976767},{695280855,29162561},{553807953,876072613},{243000458,647162898},{772234285,290257609},{103667421,244622378},{978409303,40172399},{291256097,732953826},{396058829,803288361},{509929097,947931206},{630228714,178451455},{511534046,361537974},{403211023,621721535},{347953873,660963267},{429833379,411318713},{394331091,999309563},{373115960,658138440},{494978699,566605693},{951582130,869030454},{836619118,57683411},{195853444,993138748},{133699350,235334518},{109421553,529705542},{837642897,229897873},{384114697,552096579},{24497401,903872844},{692676763,501763030},{340977815,208394801},{94905515,13970927},{845032273,339031792},{409895856,880313851},{725779700,880650516},{621492830,222798085}};
    angle = 15;
    location = {561408099,110226317};
    r = s.visiblePoints(points, angle, location);
    cout << "result " << r << endl;
    assert(r == 11);

    // case 97/109 initially wrong answer 3 expected 4
    cout << "case 97" << endl;
    points = {{1,1},{2,2},{3,3},{4,4},{1,2},{2,1}};
    angle = 0;
    location = {1,1};
    r = s.visiblePoints(points, angle, location);
    cout << "result " << r << endl;
    assert(r == 4);

    // case 98/109 initially wrong answer 1 expected 2
    cout << "case 98" << endl;
    points = {{0,0},{0,2}};
    angle = 90;
    location = {1,1};
    r = s.visiblePoints(points, angle, location);
    cout << "result " << r << endl;
    assert(r == 2);

    // case 98/109 (again???) initially wrong answer 33 expected 45
    cout << "case 98 again" << endl;
    points = {{198768142,325231488},{730653894,526879029},{482566443,124650516},{301750308,786306795},{428637509,388444545},{824139468,560868920},{46101719,541790947},{33117389,306138652},{379129552,739264502},{632078701,382510936},{648669937,641406148},{402494603,290848535},{681757446,651339050},{755146968,328108553},{856055968,54585842},{642810790,781285498},{624780623,839525682},{225552068,597591380},{941428680,575243295},{904246597,409781914},{133988308,424694994},{263860625,642729245},{725256971,428462957},{951188673,24284291},{65878467,597579989},{423910337,760218568},{375233659,465709839},{39079416,44449206},{76488044,376497238},{768046853,401132958},{862857872,713625310},{834212457,613684155},{145940546,414657761},{438671565,895069996},{486059332,78047139},{539611528,236860222},{328891159,833572609},{561041358,896191043},{469734995,511499580},{868786087,593647615},{502014973,630219398},{834825976,939531210},{232809706,831430339},{446916520,518080962},{516594877,208057152},{851130172,768268153},{665228968,134767900},{347594646,46036486},{675842115,24895986},{877430373,353382710},{167579980,47992154},{125351210,769215749},{438404131,569154245},{604952972,128325995},{304627075,646626043},{651998767,527382342},{121415369,22955171},{46278664,726969424},{650197837,730272955},{326340006,424213045},{242071539,679004233},{208227275,449583956},{688763276,330569373},{657221239,659946024},{760680906,398786962},{695186876,163719246},{416909447,908414565},{59247263,674732497},{396812330,607544608},{752069054,728117920}};
    angle = 86;
    location = {136181398,475556834};
    r = s.visiblePoints(points, angle, location);
    cout << "result " << r << endl;
    assert(r == 45);

    // case 109 / 109 initially wrong answer 4 expected 1
    cout << "case 109" << endl;
    angle = 0;
    location = {181392827,952114560};
    r = s.visiblePoints(points, angle, location);
    cout << "result " << r << endl;
    assert(r == 1);

return 0;
    // generate 10e5 random points with x and y between 0 and 10e9
    cout << "random" << endl;
    srand(time(nullptr)); // use current time as seed for random generator
    int rdm1, rdm2;
    points = {};
    for(int i = 0; i < 100000; ++i) {
        int rdm1 = rand() % 1000000001; // random in the range 0 and 10e9
        int rdm2 = rand() % 1000000001;
        points.push_back({rdm1,rdm2});
    }
    angle = rand() % 360; // random in the range 0 and 359
    rdm1 = rand() % 1000000001; // random in the range 0 and 10e9
    rdm2 = rand() % 1000000001;
    location = {rdm1,rdm2};
    /*
    string str;
    int i = 1;
    for(auto point : points) {
        if( i == 1 ) {
            str = "[[" + to_string(point[0]) + "," + to_string(point[1]) + "]";
        } else if ( i == 100000 ) {
            str += ",[" + to_string(point[0]) + "," + to_string(point[1]) + "]]";
        } else {
            str += ",[" + to_string(point[0]) + "," + to_string(point[1]) + "]";
        }
        ++i;
    }
    cout << str << endl;
    */
    cout << "angle " << angle << endl;
    cout << "location " << location[0] << " " << location[1] << endl;
    start = chrono::system_clock::now();
    r = s.visiblePoints(points, angle, location);
    end = chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "elapsed_seconds " << elapsed_seconds.count() << endl;
    cout << "result " << r << endl;

    return 0;
}