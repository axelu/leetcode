
// 3369. Design an Array Statistics Tracker 
// https://leetcode.com/problems/design-an-array-statistics-tracker/




class StatisticsTracker {
private:
    queue<int> q;
    long sum;

    map<int,int> cnt; // key: value, value: count
    map<int,set<int>> cnt_values; // key: count, value: sorted values with given count

    // stores the smaller half elements, left side
    multiset<int> l;
    // stores the greater half elements, right side
    multiset<int> r;

    void balance() {
        int n = q.size();
        if( n > 0 ) {
            if( n % 2 ) {
                while( l.size() >= r.size() ) {
                    int i = *l.rbegin();
                    r.insert(i);
                    l.erase(prev(l.end()));
                }
                while( l.size() < r.size()-1 ) {
                    int i = *r.begin();
                    l.insert(i);
                    r.erase(r.begin());
                }
            } else {
                while( l.size() > r.size() ) {
                    int i = *l.rbegin();
                    r.insert(i);
                    l.erase(prev(l.end()));
                }
                while( l.size() < r.size() ) {
                    int i = *r.begin();
                    l.insert(i);
                    r.erase(r.begin());
                }
            }
        }

        return;
    }

public:
    StatisticsTracker() {
        sum = 0L;
    }

    void addNumber(int number) {
        q.push(number);
        sum = sum + (long)number;

        int new_count = ++cnt[number];
        if( new_count > 1 ) {
            cnt_values[new_count-1].erase(number);
            if( cnt_values[new_count-1].empty() )
                cnt_values.erase(new_count-1);
        }
        cnt_values[new_count].insert(number);

        int n = q.size();
        // l and r combined contain current n-1 elements
        if( n == 1 ) {
            // neither l nor r contain an element
            r.insert(number);
        } else if( n == 2 ) {
            // r contains one element
            if( number > *r.begin() )
                r.insert(number);
            else
                l.insert(number);
        } else {
            // l and r contain at least one element each
            if( number >= *r.begin() )
                r.insert(number);
            else
                l.insert(number);
        }
        // balance l and r
        balance();

        /*
        // debug
        cout << "addNumber " << number << endl;
        cout << "l ";
        for(int i: l)
            cout << i << " ";
        cout << "r ";
        for(int i: r)
            cout << i << " ";
        cout << endl;
        */

        return;
    }

    void removeFirstAddedNumber() {
        int number = q.front();
        q.pop();

        sum = sum - (long)number;

        int new_count = --cnt[number];
        cnt_values[new_count+1].erase(number);
        if( cnt_values[new_count+1].empty() )
            cnt_values.erase(new_count+1);
        if( new_count > 0 )
            cnt_values[new_count].insert(number);


        int n = q.size();
        // l and r combined contain current n+1 elements
        if( n == 0 ) {
            r.clear();
        } else {
            // l and r contain at least one element each
            if( number < *r.begin() )
                l.erase(l.find(number));
            else
                r.erase(r.find(number));
        }
        // balance l and r
        balance();

        /*
        // debug
        cout << "removeNumber " << number << endl;
        cout << "l ";
        for(int i: l)
            cout << i << " ";
        cout << "r ";
        for(int i: r)
            cout << i << " ";
        cout << endl;
        */

        return;
    }

    int getMean() {
        // it is guaranteed that there is at least one element
        long n = q.size();
        long mean = sum / n;
        return (int)mean;
    }

    int getMedian() {
        // it is guaranteed that there is at least one element
        return *r.begin();
    }

    int getMode() {
        // it is guaranteed that there is at least one element
        return *(cnt_values.rbegin()->second.begin());
    }
};

/**
 * Your StatisticsTracker object will be instantiated and called as such:
 * StatisticsTracker* obj = new StatisticsTracker();
 * obj->addNumber(number);
 * obj->removeFirstAddedNumber();
 * int param_3 = obj->getMean();
 * int param_4 = obj->getMedian();
 * int param_5 = obj->getMode();
 */
