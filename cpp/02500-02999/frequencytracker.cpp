
// 2671. Frequency Tracker
// https://leetcode.com/problems/frequency-tracker/




class FrequencyTracker {
private:
    unordered_map<int,int> cnt;
    unordered_map<int,int> frq;

    void printMap(unordered_map<int,int> um) {
        for(auto& p: um)
            cout << p.first << ":" << p.second << " ";
        cout << endl;
    }

public:
    FrequencyTracker() {

    }

    void add(int number) {
        // cout << "add " << number << endl;
        auto p = cnt.insert({number,1});
        if( !p.second )
            ++p.first->second;

        int org_frq = p.first->second - 1;
        if( org_frq != 0 ) {
            --frq[org_frq];
            if( frq[org_frq] == 0 )
                frq.erase(org_frq);
        }

        int new_frq = p.first->second;
        p = frq.insert({new_frq,1});
        if( !p.second )
            ++p.first->second;

        // cout << "cnt ";printMap(cnt);
        // cout << "frq ";printMap(frq);
    }

    void deleteOne(int number) {
        // cout << "delete " << number << endl;
        auto f = cnt.find(number);
        if( f == cnt.end() )
            return;

        int org_frq = f->second;
        if( org_frq == 1 )
            cnt.erase(f);
        else
            --f->second;

        f = frq.find(org_frq);
        if( f->second == 1 )
            frq.erase(f);
        else
            --f->second;

        int new_frq = org_frq - 1;
        if( new_frq > 0 ) {
            auto p = frq.insert({new_frq,1});
            if( !p.second )
                ++p.first->second;
        }

        // cout << "cnt ";printMap(cnt);
        // cout << "frq ";printMap(frq);
    }

    bool hasFrequency(int frequency) {
        return frq.find(frequency) != frq.end();
    }
};

/**
 * Your FrequencyTracker object will be instantiated and called as such:
 * FrequencyTracker* obj = new FrequencyTracker();
 * obj->add(number);
 * obj->deleteOne(number);
 * bool param_3 = obj->hasFrequency(frequency);
 */
