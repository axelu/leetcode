
// 380. Insert Delete GetRandom O(1)
// https://leetcode.com/problems/insert-delete-getrandom-o1/
// day 21 October 2021 challenge



class RandomizedSet {
private:
    vector<int> v;
    unordered_map<int,int> um; // value, idx in v
public:
    RandomizedSet() {
        srand(time(nullptr)); // use current time as seed for random generator
    }

    bool insert(int val) {
        if( um.find(val) != um.end() )
            return false;

        v.push_back(val);
        um[val] = v.size()-1;

        return true;
    }

    bool remove(int val) {
        auto f = um.find(val);
        if( f == um.end() )
            return false;

        if( f->second != v.size()-1 ) {
            v[f->second] = v.back();
            um[v.back()] = f->second;
        }

        v.pop_back();
        um.erase(f);
        return true;
    }

    int getRandom() {
        int rdm = rand() % v.size();
        return v[rdm];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
