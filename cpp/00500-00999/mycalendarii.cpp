
// 731. My Calendar II
// https://leetcode.com/problems/my-calendar-ii/



class MyCalendarTwo {
private:
    // in neither calendar itself will be overlaps!
    vector<vector<int>> calSingle;
    vector<vector<int>> calDouble;

    // debug
    void printCalendar(vector<vector<int>>& calendar) {
        for(int i = 0; i < calendar.size(); ++i)
            cout << "[" << calendar[i][0] << "," << calendar[i][1] << "] ";
        cout << endl;
    }

    void printCalendar(bool res) {
        cout << "booked " << res << endl;
        cout << "single ";
        printCalendar(calSingle);
        cout << "double ";
        printCalendar(calDouble);
    }

    bool hasConflict(int s1, int e1, int s2, int e2) {
        // assumption: s1 <= e1, s2 <= e2
        if( e2 <= s1 || e1 <= s2 )
            return false;
        return true;
    }

    // binary search
    pair<int,bool> search(vector<vector<int>>& calendar, int s, int e, int start, int end) {
        // return idx,true:
        //    conflict with element at idx
        // return idx,false:
        //    no conflict and idx is the element before which the new one should be inserted
        // return -1,false
        //    no conflict and the element is after
        //    if this is the overall return, then it goes at the end

        if( s > e ) {
            if( e == -1 ) return make_pair(0,false);
            return make_pair(-1,false);
        }
        if( s == e ) {
            if( hasConflict(calendar[s][0],calendar[s][1],start,end) )
                return make_pair(s,true);
            if( end <= calendar[s][0] )
                return make_pair(s,false);
            else
                return make_pair(-1,false);
        }

        int mid = s + ((e - s)/2);

        if( hasConflict(calendar[mid][0],calendar[mid][1],start,end) )
            return make_pair(mid,true);

        if( end <= calendar[mid][0] ) {
            // the current event is a candidate before which
            // the new event could be inserted
            // can we do better?
            pair<int,bool> p = search(calendar,s,mid-1,start,end);
            if( p.second ) return p;
            if( p.first == -1 ) return make_pair(mid,false);
            return p;
        } else {
            return search(calendar,mid+1,e,start,end);
        }
    }

    pair<int,bool> insert(vector<vector<int>>& calendar, int start, int end) {
        // returns idx,false when insertion did NOT succeed where idx is a conflicting element
        // returns idx,true when the insertion took place where idx is the idx of the inserted element
        int n = calendar.size();
        if( n == 0 ) {
            calendar.push_back({start,end});
            return make_pair(0,true);
        }
        auto p = search(calendar,0,n-1,start,end);
        if( !p.second ) {
            if( p.first == -1 ) {
                // insert at the end
                calendar.push_back({start,end});
                return make_pair(n,true);
            } else {
                calendar.insert(calendar.begin() + p.first, {start,end});
                return make_pair(p.first,true);
            }
        }
        return make_pair(p.first,false);
    }


public:
    MyCalendarTwo() {

    }

    bool book(int start, int end) {
        // cout << "book " << start << " " << end << endl;
        if( calSingle.empty() ) {
            calSingle.push_back({start,end});
            // printCalendar(true);
            return true;
        }

        int nD = calDouble.size();
        auto pD = search(calDouble,0,nD-1,start,end);
        if( pD.second ) {
            // there is already at least one double booked time
            // that conflicts with start,end
            // printCalendar(false);
            return false;
        }

        auto pS = insert(calSingle,start,end);
        if( pS.second ) {
            // printCalendar(true);
            return true;
        }

        // we need to get all singly booked times that start,end 'touches'
        // then we need to split start,end into the entries that go into
        // the single booked calendar and the double booked calendar

        vector<vector<int>> single;
        // go left
        for(int i = pS.first-1; i >= 0; --i)
            if( hasConflict(calSingle[i][0],calSingle[i][1],start,end) )
                single.insert(single.begin(),{calSingle[i][0],calSingle[i][1]});
            else
                break;
        single.push_back({calSingle[pS.first][0],calSingle[pS.first][1]});
        // go right
        for(int i = pS.first+1; i < calSingle.size(); ++i)
            if( hasConflict(calSingle[i][0],calSingle[i][1],start,end) )
                single.push_back({calSingle[i][0],calSingle[i][1]});
            else
                break;


        // debug
        // cout << "single conflicts" << endl;
        // printCalendar(single);


        // single now contains all the existing singly booked events that start,end 'touches'
        // in chronoligcal order

        for(int i = single.size()-1; i >= 0; --i) {
            if( single[i][0] <= start && end <= single[i][1] ) {
                // only insert in double is needed
                insert(calDouble,start,end);
            } else if( start <= single[i][0] ) {
                if( end <= single[i][1] ) {
                    // only insert into double
                    insert(calDouble,single[i][0],end);
                } else {
                    // split
                    // insert overlap into double
                    insert(calDouble,single[i][0],single[i][1]);
                    // insert non overlap into single
                    insert(calSingle,single[i][1],end);
                }
                end = single[i][0];
            } else {
                // start > single[i][0]
                if( end <= single[i][1] ) {
                    // only insert into double
                    insert(calDouble,start,end);
                } else {
                    // split
                    // insert overlap into double
                    insert(calDouble,start,single[i][1]);
                    // insert non overlap into single
                    insert(calSingle,single[i][1],end);
                }
                end = single[i][0];
            }
        }
        if( start < end ) insert(calSingle,start,end);

        // printCalendar(true);
        return true;
    }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(start,end);
 */
