#include <iostream>
#include <cassert>

#include <vector>
#include <algorithm>
#include <string>
#include <stack>

using namespace std;

// day 15 August 2020 challenge
// Non-overlapping Intervals
// https://leetcode.com/explore/challenge/card/august-leetcoding-challenge/551/week-3-august-15th-august-21st/3425/

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {

        if ( intervals.empty() ) return 0;
        if ( intervals.size() == 1 ) return 0;

        auto comp = [] (vector<int> v1, vector<int> v2) {

            //if ( v1.front() < v2.front() ) {
            //    return true;
            //} else if ( v1.front() == v2.front() ) {
            //    if ( v1.back() <= v2.back() ) {
            //        return true;
            //    } else {
            //        return false;
            //    }
            //} else {
            //    return false;
            //}

            return v1.front() <= v2.front();
        };

        cout << "before sort ";
        for(auto v : intervals) cout << v.front() << " " << v.back() << ", ";
        cout << endl;
        sort(intervals.begin(), intervals.end(), comp);
        cout << "after sort  ";
        for(auto v : intervals) cout << v.front() << " " << v.back() << ", ";
        cout << endl;

        int r = 0;
        
        stack<vector<int>> stck;
        stck.push(intervals[0]);
        cout << stck.top().back() << endl;
        for(auto it = intervals.begin() + 1; it != intervals.end(); ++it) {
            
            cout << "interval: " << it->front() << " " << it->back() << endl;
            cout << "stck top: " << stck.top().front() << " " << stck.top().back() << endl;

            if ( it->front() < stck.top().back() ) {
                cout << "updating" << endl;
                if ( it->back() < stck.top().back() ) stck.top().back() = it->back();
            } else {
                cout << "pushing" << endl;
                stck.push(*it);
            }
        }
        cout << stck.size() << endl;







/*
        for(auto it = intervals.begin(); it != intervals.end() - 1; ++it) {

            cout << it->front() << " " << it->back() << endl;


            // equal
            if ( *it == *(it+1) ) {
                cout << "equal" << endl;
                r++;
                continue;
            }

            if ( it->back() > (it+1)->front() ) {
                r++;
                if ( it->back() <= (it+1)->back() ) {
                    it++;
                }
            }
*/
            /*

           // skip touch
            if ( it <= intervals.end() - 3 ) {
                bool skipped = false;
                for (auto iti = it + 2; iti != intervals.end(); ++iti ) {
                    if ( it->back() == iti->front() ) {
                        cout << "skip touch +" << iti - it - 1 << endl;
                        r += iti - it - 1;
                        it = ( iti == intervals.end() - 1 ) ? iti - 1 : iti;
                        skipped = true;
                        break;
                    }
                }
                if ( skipped ) continue;
            }

            if ( it->back() > (it+1)->front() ) {
                cout << "interleave with " << (it+1)->front() << " " << (it+1)->back() << endl;
                r++;
            }
            // interleave
            for (auto iti = it + 1; iti != intervals.end(); ++iti ) {
                if ( it->back() > iti->front() && it->back() < iti->back() ) {
                    cout << "interleave with " << iti->front() << " " << iti->back() << endl;
                    r++;
                    break;
                }
            }*/

//        }
        
        cout << r << endl;
        return intervals.size() - stck.size();
    }
};

int main() {

    Solution s;

    vector<int> v30 = {1,2};
    vector<int> v31 = {2,3};
    vector<int> v32 = {3,4};
    vector<int> v33 = {1,3};
    vector<vector<int>> v3 = {v30, v31, v32, v33};
    assert(s.eraseOverlapIntervals(v3) == 1);

    vector<int> v40 = {1,2};
    vector<int> v41 = {1,2};
    vector<int> v42 = {1,2};
    vector<vector<int>> v4 = {v40, v41, v42};
    assert(s.eraseOverlapIntervals(v4) == 2);

    vector<int> v50 = {1,2};
    vector<int> v51 = {2,3};
    vector<vector<int>> v5 = {v50, v51};
    assert(s.eraseOverlapIntervals(v5) == 0);

    vector<int> v60 = {1,100};
    vector<int> v61 = {11,22};
    vector<int> v62 = {1,11};
    vector<int> v63 = {2,12};
    vector<vector<int>> v6 = {v60, v61, v62, v63};
    assert(s.eraseOverlapIntervals(v6) == 2);

    vector<int> v70 = {1,2};
    vector<int> v71 = {1,3};
    vector<int> v72 = {1,4};
    vector<vector<int>> v7 = {v70, v71, v72};
    assert(s.eraseOverlapIntervals(v7) == 2);

    vector<int> v80 = {0,2};
    vector<int> v81 = {1,3};
    vector<int> v82 = {2,4};
    vector<int> v83 = {3,5};
    vector<int> v84 = {4,6};
    vector<vector<int>> v8 = {v80, v81, v82, v83, v84};
    assert(s.eraseOverlapIntervals(v8) == 2);

    string str = "[[-100,-87],[-99,-44],[-98,-19],[-97,-33],[-96,-60],[-95,-17],[-94,-44],[-93,-9],[-92,-63],[-91,-76],[-90,-44],[-89,-18],[-88,10],[-87,-39],[-86,7],[-85,-76],[-84,-51],[-83,-48],[-82,-36],[-81,-63],[-80,-71],[-79,-4],[-78,-63],[-77,-14],[-76,-10],[-75,-36],[-74,31],[-73,11],[-72,-50],[-71,-30],[-70,33],[-69,-37],[-68,-50],[-67,6],[-66,-50],[-65,-26],[-64,21],[-63,-8],[-62,23],[-61,-34],[-60,13],[-59,19],[-58,41],[-57,-15],[-56,35],[-55,-4],[-54,-20],[-53,44],[-52,48],[-51,12],[-50,-43],[-49,10],[-48,-34],[-47,3],[-46,28],[-45,51],[-44,-14],[-43,59],[-42,-6],[-41,-32],[-40,-12],[-39,33],[-38,17],[-37,-7],[-36,-29],[-35,24],[-34,49],[-33,-19],[-32,2],[-31,8],[-30,74],[-29,58],[-28,13],[-27,-8],[-26,45],[-25,-5],[-24,45],[-23,19],[-22,9],[-21,54],[-20,1],[-19,81],[-18,17],[-17,-10],[-16,7],[-15,86],[-14,-3],[-13,-3],[-12,45],[-11,93],[-10,84],[-9,20],[-8,3],[-7,81],[-6,52],[-5,67],[-4,18],[-3,40],[-2,42],[-1,49],[0,7],[1,104],[2,79],[3,37],[4,47],[5,69],[6,89],[7,110],[8,108],[9,19],[10,25],[11,48],[12,63],[13,94],[14,55],[15,119],[16,64],[17,122],[18,92],[19,37],[20,86],[21,84],[22,122],[23,37],[24,125],[25,99],[26,45],[27,63],[28,40],[29,97],[30,78],[31,102],[32,120],[33,91],[34,107],[35,62],[36,137],[37,55],[38,115],[39,46],[40,136],[41,78],[42,86],[43,106],[44,66],[45,141],[46,92],[47,132],[48,89],[49,61],[50,128],[51,155],[52,153],[53,78],[54,114],[55,84],[56,151],[57,123],[58,69],[59,91],[60,89],[61,73],[62,81],[63,139],[64,108],[65,165],[66,92],[67,117],[68,140],[69,109],[70,102],[71,171],[72,141],[73,117],[74,124],[75,171],[76,132],[77,142],[78,107],[79,132],[80,171],[81,104],[82,160],[83,128],[84,137],[85,176],[86,188],[87,178],[88,117],[89,115],[90,140],[91,165],[92,133],[93,114],[94,125],[95,135],[96,144],[97,114],[98,183],[99,157]]";
    str.erase(str.begin());str.erase(str.end()-1);
    cout << str << endl;
    vector<vector<int>> v9;
    int mode;
    string nbr1;
    int inbr1;
    string nbr2;
    int inbr2; 
    for(auto c : str) {
        if ( c == '[' ) {
            mode = 1;
            continue;
        }
        if ( mode == 1 && c == ',' ) {
            inbr1 = stoi(nbr1);
            nbr1.clear();
            mode = 2;
            continue;
        }
        if ( mode == 2 && c == ']' ) {
            inbr2 = stoi(nbr2);
            nbr2.clear();
            vector<int> iv = {inbr1,inbr2};
            v9.push_back(iv);
            mode = 3;
        }

        if ( mode == 1 ) {
            nbr1.push_back(c);
        }
        if ( mode == 2 ) {
            nbr2.push_back(c);
        }
    }
    cout << "v9 length " << v9.size() << endl;
    assert(s.eraseOverlapIntervals(v9) == 187);



    return 0;
}
