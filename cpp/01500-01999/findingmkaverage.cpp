
// 1825. Finding MK Average
// https://leetcode.com/problems/finding-mk-average/





class MKAverage {
private:
    int m,k;
    long d;

    queue<int> q;

    map<int,int> left;
    int left_cnt;

    map<int,int> middle;
    int middle_cnt;
    long sum;

    map<int,int> right;
    int right_cnt;

    // debug
    void printState() {
        cout << "q size " << q.size() << endl;
        cout << "left size " << left.size() << " left_cnt " << left_cnt << endl;
        cout << "left smallest element " << left.begin()->first << " left largest element " << left.rbegin()->first << endl;
        cout << "middle size " << middle.size() << " middle_cnt " << middle_cnt << endl;
        cout << "middle smallest element " << middle.begin()->first << " middle largest element " << middle.rbegin()->first << endl;
        cout << "middle sum " << sum << endl;
        cout << "right size " << right.size() << " right_cnt " << right_cnt << endl;
        cout << "right smallest element " << right.begin()->first << " right largest element " << right.rbegin()->first << endl;
        return;
    }

    void remove(int x) {
        // we prefer to remove from the left
        // meaning if max left and min middle = x, remove from left
        //         if max middle and min right = x, remove from middle

        if( x <= left.rbegin()->first ) {
            --left[x];
            if( left[x] == 0 )
                left.erase(x);
            --left_cnt;
            return;
        }

        if( x <= middle.rbegin()->first ) {
            --middle[x];
            if( middle[x] == 0 )
                middle.erase(x);
            --middle_cnt;
            sum -= x;
            return;
        }

        // x must be in the right
        --right[x];
        if( right[x] == 0 )
            right.erase(x);
        --right_cnt;
        return;
    }

    void add(int x) {
        // we prefer to add to the left

        if( left.empty() || x <= left.rbegin()->first ) {
            ++left[x];
            ++left_cnt;
            return;
        }

        if( middle.empty() || x <= middle.rbegin()->first ) {
            ++middle[x];
            ++middle_cnt;
            sum += x;
            return;
        }

        // add to right
        ++right[x];
        ++right_cnt;
        return;
    }

    void balance() {

        while( left_cnt < k && !middle.empty() ) {
            // we need to move elements from middle to left
            ++left[middle.begin()->first];
            --middle.begin()->second;
            sum -= middle.begin()->first;
            if(middle.begin()->second == 0 )
                middle.erase(middle.begin());

            ++left_cnt;
            --middle_cnt;
        }

        while( left_cnt > k ) {
            // we need to move elements from left to middle
            --left.rbegin()->second;
            ++middle[left.rbegin()->first];
            sum += left.rbegin()->first;
            if( left.rbegin()->second == 0 )
                left.erase(prev(left.end()));

            --left_cnt;
            ++middle_cnt;
        }

        // repeat for middle
        while( middle_cnt < d && !right.empty() ) {
            // we need to move elements from right to middle
            ++middle[right.begin()->first];
            sum += right.begin()->first;
            --right.begin()->second;
            if(right.begin()->second == 0 )
                right.erase(right.begin());

            ++middle_cnt;
            --right_cnt;
        }

        while( middle_cnt > d) {
            // we need to move elements from middle to right
            --middle.rbegin()->second;
            sum -= middle.rbegin()->first;
            ++right[middle.rbegin()->first];
            if( middle.rbegin()->second == 0 )
                middle.erase(prev(middle.end()));

            --middle_cnt;
            ++right_cnt;
        }

        return;
    }

public:
    MKAverage(int m, int k) {
        this->m = m;
        this->k = k;
        d = m - 2 * k; // cout << d << endl;
        left_cnt = 0;
        middle_cnt = 0;
        sum = 0L;
        right_cnt = 0;
    }

    void addElement(int num) {
        // cout << "add " << num << endl;
        if( q.size() == m ) {
            // we must remove an element
            // cout << "addElement -> remove " << q.front() << endl;
            // cout << "before remove" << endl;
            // printState();
            remove(q.front());
            // cout << "after remove before balance" << endl;
            // printState();
            balance();
            // cout << "after remove and balance" << endl;
            // printState();
            q.pop();
        }

        add(num);
        balance();
        q.push(num);

        /*
        cout << "  left ";
        for(auto p: left)
            cout << p.first << ":" << p.second << " ";
        cout << endl;
        cout << "  middle ";
        for(auto p: middle)
            cout << p.first << ":" << p.second << " ";
        cout << endl;
        cout << "  right ";
        for(auto p: right)
            cout << p.first << ":" << p.second << " ";
        cout << endl;
        */

        return;
    }

    int calculateMKAverage() {
        // if( left.size() + middle.size() + right.size() < m )
        if( q.size() < m )
            return -1;

        // cout << "calculate average" << endl;
        // printState();

        /*
        cout << "  middle ";
        for(auto p: middle)
            cout << p.first << ":" << p.second << " ";
        cout << endl;
        */

        return sum / d;
    }
};

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */
