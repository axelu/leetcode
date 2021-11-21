
// 381. Insert Delete GetRandom O(1) - Duplicates allowed
// https://leetcode.com/problems/insert-delete-getrandom-o1-duplicates-allowed/





class RandomizedCollection {
private:
    int arr[200000];
    int n;
    unordered_map<int,unordered_set<int>> um; // {value,{idx1,idx2,...}}

    void printArr() {
        cout << "arr: ";
        for(int i = 0; i < n; ++i)
            cout << arr[i] << " ";
        cout << endl;
    }

public:
    RandomizedCollection() {
        srand(time(nullptr)); // use current time as seed for random generator
        n = 0;
    }

    bool insert(int val) {
        bool ret = false;
        if( um.find(val) == um.end() )
            ret = true;

        arr[n] = val;
        um[val].insert(n);
        ++n;

        return ret;
    }

    bool remove(int val) {
        auto f = um.find(val);
        if( f == um.end() )
            return false;


        if( arr[n-1] == val ) {
            f->second.erase(n-1);

        } else {
            auto f2 = um.find(arr[n-1]);
            f2->second.erase(n-1);
            f2->second.insert(*f->second.begin());
            arr[*f->second.begin()] = arr[n-1];
            f->second.erase(f->second.begin());
        }

        --n;
        if( f->second.empty() )
            um.erase(f);

        return true;
    }

    int getRandom() {
        int rdm = rand() % n;
        return arr[rdm];
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
