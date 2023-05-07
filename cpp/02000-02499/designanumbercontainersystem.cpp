
// 2349. Design a Number Container System
// https://leetcode.com/problems/design-a-number-container-system/




class NumberContainers {
private:
    unordered_map<int,int> byindex;         // index, number
    unordered_map<int,set<int>> bynumber;   // number, list of indicies
public:
    NumberContainers() {

    }

    void change(int index, int number) {
        auto f = byindex.find(index);

        if( f == byindex.end() ) {
            byindex.insert({index,number});
            bynumber[number].insert(index);

        } else {
            int curr_number = f->second;
            f->second = number;

            bynumber[curr_number].erase(index);
            if( bynumber[curr_number].empty() )
                bynumber.erase(curr_number);

            bynumber[number].insert(index);
        }
    }

    int find(int number) {
        auto f = bynumber.find(number);
        if( f != bynumber.end() )
            return *f->second.begin();

        return -1;
    }
};

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */
