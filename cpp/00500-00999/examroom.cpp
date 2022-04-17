
// 855. Exam Room
// https://leetcode.com/problems/exam-room/



class ExamRoom {
private:
    int N;
    unordered_map<int,int> byend;   // end,   start
    unordered_map<int,int> bystart; // start, end
    map<int,set<int>> m;            // length,start

    void remove(int s, int l) {
        int e = s + l - 1;

        bystart.erase(s);
        byend.erase(e);

        auto f = m.find(l);
        f->second.erase(s);
        if( f->second.empty() )
            m.erase(f);
    }

    void add(int s, int l) {
        int e = s + l - 1;

        bystart.insert({s,e});
        byend.insert({e,s});
        auto f = m.find(l);
        if( f == m.end() )
            m.insert({l,{s}});
        else
            f->second.insert(s);
    }

public:
    ExamRoom(int n) {
        m.insert({n,{0}});
        bystart.insert({0,n-1});
        byend.insert({n-1,0});
        N = n;
    }

    int seat() {
        if( N == 1 )
            return 0;

        // we sit the person in the middle of the longest gap
        // if there are multiple, we get the left most one
        // edge case if longest gap starts at 0 or ends at N-1;
        int l = prev(m.end())->first;
        int s = *(prev(m.end())->second.begin());
        int e = s + l - 1;
        // cout << "l " << l << " s " << s << " e " << e << endl;
        if( l == 1 ) {
            remove(s,l);
            return s;
        } else if( s == 0 ) {
            remove(0,l);
            add(1,l-1);
            return 0;
        } else if( e == N-1 ) {
            remove(s,l);
            add(s,l-1);
            return N-1;
        } else if ( l == 2 ) {
            // is there a space of l == 1 that is lower
            auto f = m.find(1);
            if( f != m.end() ) {
                int s_1 = *(f->second.begin());
                if( s_1 < s ) {
                    remove(s_1,1);
                    return s_1;
                }
            }
            remove(s,l);
            add(s+1,1);
            return s;
        } else {
            // there is someone to the right and someone to the left
            // placing our new studend in the middle will remove the current range
            // and create to new ranges, one to the left and one to the right
            // BUT...
            // if there is a range starting at 0, we need to measure against that AND
            // if the largest range we found is of even length, we
            // need to see if there is a range l-1 that starts further to the left
            // as that would give us the same spacing, but seating the student
            // in the left most space

            int mid = s + ((e-s)/2);

            int spacing = mid - s; // spacing we can achieve putting student in that range

            // spacing we can achieve by placing student in seat 0
            int spacing_start = 0;
            auto f_start = bystart.find(0);
            if( f_start != bystart.end() )
                spacing_start = f_start->second;
            if( spacing_start >= spacing ) {
                remove(0,spacing_start+1);
                add(1,spacing_start);
                return 0;
            }

            // spacing we can achieve by placing student in seat N-1
            int spacing_end = 0;
            auto f_end = byend.find(N-1);
            if( f_end != byend.end() )
                spacing_end = N-1 - f_end->second;
            if( spacing_end > spacing ) {
                remove(N-1-spacing_end,spacing_end+1);
                add(N-1-spacing_end,spacing_end);
                return N-1;
            }

            if( l % 2 == 0 ) {
                auto f_2 = m.find(l-1);
                if( f_2 != m.end() ) {
                    int s_2 = *(f_2->second.begin());
                    if( s_2 < s ) {
                        l = f_2->first;
                        s = s_2;
                        e = s + l - 1;
                        mid = s + ((e-s)/2);
                    }
                }
            }
            remove(s,l);
            add(s,mid-1 - s + 1);
            add(mid+1,e - (mid+1) + 1);
            return mid;
        }
    }

    void leave(int p) {
        if( N == 1 )
            return;

        if( p == 0 ) {
            int s = 1;
            auto f = bystart.find(s);
            if( f != bystart.end() ) {
                // extend the range to the right by one to the left
                int e = f->second;
                int l = e - s + 1;
                remove(s,l);
                add(0,l+1);
            } else {
                add(0,1);
            }
        } else if( p == N-1 ) {
            int e = N-2;
            auto f = byend.find(e);
            if( f != byend.end() ) {
                // extend the range to the left by one to the right
                int s = f->second;
                int l = e - s + 1;
                remove(s,l);
                add(s,l+1);
            } else {
                add(N-1,1);
            }
        } else {
            auto fl = byend.find(p-1);
            auto fr = bystart.find(p+1);
            if( fl == byend.end() && fr == bystart.end() ) {
                add(p,1);

            } else if( fl != byend.end() && fr == bystart.end() ) {
                // extend the range to the left by one to the right
                int s = fl->second;
                int l = (p-1) - s + 1;
                remove(s,l);
                add(s,l+1);

            } else if( fl == byend.end() && fr != bystart.end() ) {
                // extend the range to the right by one to the left
                int e = fr->second;
                int l = e - (p+1) + 1;
                remove(p+1,l);
                add(p,l+1);

            } else { // fl != byend.end() && fr =! bystart.end()
                int s  = fl->second;
                int ll = (p-1) - s + 1;
                remove(s,ll);
                int e  = fr->second;
                int rl = e - (p+1) + 1;
                remove(p+1,rl);
                int l  = e - s + 1;
                add(s,l);
            }
        }
    }
};

/**
 * Your ExamRoom object will be instantiated and called as such:
 * ExamRoom* obj = new ExamRoom(n);
 * int param_1 = obj->seat();
 * obj->leave(p);
 */
