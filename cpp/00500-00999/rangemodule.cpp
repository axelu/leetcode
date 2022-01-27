
// 715. Range Module
// https://leetcode.com/problems/range-module/



class RangeModule {
private:
    map<int,int> endpoints; // right,left of non-tracking range with [left,right)
    // int qc;

    void split(int left, int right, map<int,int>::iterator it) {
        int t = it->second;

        // shrinkLeft
        shrinkLeft(right,it);

        // insert left part
        endpoints.insert({left,t});
    }

    void shrinkLeft(int right, map<int,int>::iterator it) {
        it->second = right;
    }

    void shrinkRight(int left, map<int,int>::iterator it) {
        int t = it->second;
        endpoints.erase(it);
        endpoints.insert({left,t});
    }

    void cleanup(int left, map<int,int>::iterator it) {
        // search endpoints by left
        map<int,int>::iterator it2 = endpoints.upper_bound(left);
        if( it2 != it ) {
            // found a range we 'hook' into
            // - delete anything after till it2 (if there is anything)
            // - if the found range is exclipsed - delete it
            // - if the found range is not eclipsed - shrink it
            if( next(it2) != it )
                endpoints.erase(next(it2),it);
            if( it2->second >= left ) {
                endpoints.erase(it2);
            } else {
                shrinkRight(left,it2);
            }
        }
    }

    void expandLeftRight(int left, int right, map<int,int>::iterator it) {
        endpoints.erase(it);
        endpoints.insert({right,left});
    }

    void expandLeft(int left, map<int,int>::iterator it) {
        it->second = left;
    }

    void expandRight(int right, map<int,int>::iterator it) {
        int t = it->second;
        endpoints.erase(it);
        endpoints.insert({right,t});
    }

public:
    RangeModule() {
        // init our entire plane to non-tracking
        endpoints.insert({999999999,1});
        // qc = 0;
    }

    void addRange(int left, int right) {
        // base case
        if( left == 1 && right == 999999999 ) {
            if( !endpoints.empty() ) endpoints.clear();
            return;
        }

        // search endpoints by right
        map<int,int>::iterator it = endpoints.lower_bound(right);
        if( it == endpoints.end() ) {
            cleanup(left,it);
        } else if( it->first == right ) {
            // it1 is pointing to something == right
            if( it->second == left ) {
                endpoints.erase(it);
            } else if( it->second < left ) {
                shrinkRight(left,it);
            } else {
                cleanup(left,it);
                endpoints.erase(it);
            }
        } else {
            // it1 is pointing to something > right
            if( it->second >= right ) {
               cleanup(left,it);
            } else if( it->second > left ) {
                cleanup(left,it);
                shrinkLeft(right,it);
            } else if( it->second == left ) {
                shrinkLeft(right,it);
            } else {
                split(left,right,it);
            }
        }

        // cout << "after add" << endl;
        // for(pair<int,int> p : endpoints) cout << p.second << " " << p.first << endl;
    }

    bool queryRange(int left, int right) {
        // if query range is overlapping with anything in endpoints: false
        // ++qc;
        // cout << "query " << qc << " " << left << " " << right << endl;
        // for(pair<int,int> p : endpoints) cout << p.second << " " << p.first << endl;

        bool r = true;

        // base case
        if( endpoints.empty() ) {
            r = true;
        } else {

        map<int,int>::iterator it1,it2;

        // search endpoints by right
        it1 = endpoints.lower_bound(right);
        if( it1 == endpoints.end() ) {
            // search endpoints by left
            it2 = endpoints.upper_bound(left);
            if( it2 != it1 ) r = false;
        } else if( it1->first == right ) {
            r = false;
        } else {
            // it1 is pointing to something > right
            if( it1->second < right ) r = false;

            // search endpoints by left
            it2 = endpoints.upper_bound(left);
            if( it2 != it1 ) r = false;
        }
        }

        // cout << "ans " << r << endl;
        return r;
    }

    void removeRange(int left, int right) {
        // base cases
        if( left == 1 && right == 999999999 ) {
            if( !endpoints.empty() ) endpoints.clear();
            endpoints.insert({999999999,1});
            return;
        }
        if( endpoints.empty() ) {
            endpoints.insert({right,left});
            return;
        }

        map<int,int>::iterator it1,it2;

        // search endpoints by right
        it1 = endpoints.lower_bound(right);
        if( it1 == endpoints.end() ) {
            it2 = endpoints.upper_bound(left);
            if( it1 == it2 ) {
                endpoints.insert({right,left});
            } else {
                if( next(it2) != it1 )
                    endpoints.erase(next(it2),it1);
                if( it2->second > left ) {
                    expandLeftRight(left,right,it2);
                } else {
                    expandRight(right,it2);
                }
            }
        } else if( it1->first == right ) {
             // it1 is pointing to something == right
            if( it1->second <= left ) {
                // nothing to do
            } else {
                it2 = endpoints.upper_bound(left);
                if( it2 == it1 ) {
                    expandLeft(left,it1);
                } else {
                    if( next(it2) != it1 )
                        endpoints.erase(next(it2),it1);
                    if( it2->second > left ) {
                        endpoints.erase(it1);
                        expandLeftRight(left,right,it2);
                    } else {
                        endpoints.erase(it1);
                        expandRight(right,it2);
                    }
                }
            }
        } else {
            // it1 is pointing to something > right
            if( it1->second <= left ) {
                // nothing to do
            } else if( it1->second >= right ) {
                it2 = endpoints.upper_bound(left);
                if( it2 == it1 ) {
                    endpoints.insert({right,left});
                } else {
                    if( next(it2) != it1 )
                        endpoints.erase(next(it2),it1);
                    if( it2->second > left ) {
                        expandLeftRight(left,right,it2);
                    } else {
                        expandRight(right,it2);
                    }
                }
            } else {
                it2 = endpoints.upper_bound(left);
                if( it2 == it1 ) {
                    expandLeft(left,it1);
                } else {
                    if( next(it2) != it1 )
                        endpoints.erase(next(it2),it1);
                    if( it2->second >= left ) {
                        endpoints.erase(it2);
                        expandLeft(left,it1);
                    } else {
                        int t = it2->second;
                        endpoints.erase(it2);
                        expandLeft(t,it1);
                    }
                }

            }
        }

        // cout << "after remove" << endl;
        // for(pair<int,int> p : endpoints) cout << p.second << " " << p.first << endl;

    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */
