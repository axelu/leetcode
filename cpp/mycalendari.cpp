
// 729. My Calendar I
// https://leetcode.com/problems/my-calendar-i/




class MyCalendar {
private:
    vector<vector<int>> calendar;
    int n;

    // debug
    void printCalendar(bool res) {
        cout << "booked " << res << endl;
        for(int i = 0; i < n; ++i)
            cout << "[" << calendar[i][0] << "," << calendar[i][1] << "] ";
        cout << endl;
    }

    bool hasConflict(int s1, int e1, int s2, int e2) {
        // assumption: s1 <= e1, s2 <= e2
        if( e2 <= s1 || e1 <= s2 )
            return false;
        return true;
    }

    // binary search
    pair<int,bool> search(int s, int e, int start, int end) {
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
            pair<int,bool> p = search(s,mid-1,start,end);
            if( p.second ) return p;
            if( p.first == -1 ) return make_pair(mid,false);
            return p;
        } else {
            return search(mid+1,e,start,end);
        }
    }
public:
    MyCalendar() {
        n = 0;
    }

    bool book(int start, int end) {
        // cout << "book " << start << " " << end << endl;
        if( n == 0 ) {
            calendar.push_back({start,end});
            ++n;
            // printCalendar(true);
            return true;
        }

        auto p = search(0,n-1,start,end);
        if( p.second ) {
            // debug
            // printCalendar(false);
            return false;
        }
        if( p.first == -1 ) {
            // insert at the end
            calendar.push_back({start,end});
        } else {
            calendar.insert(calendar.begin() + p.first, {start,end});
        }
        ++n;

        // printCalendar(true);
        return true;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */
