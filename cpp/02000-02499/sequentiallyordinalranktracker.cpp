
// 2102. Sequentially Ordinal Rank Tracker
// https://leetcode.com/problems/sequentially-ordinal-rank-tracker/





class SORTracker {
private:
    struct cmp1 {
        public:
        bool operator()(const pair<string,int>& a, const pair<string,int>& b){
            if( a.second > b.second ) {
                return true;
            } else if( a.second == b.second ) {
                if( a.first < b.first ) {
                    return true;
                }
            }
            return false;
        }
    };
    priority_queue<pair<string,int>,vector<pair<string,int>>,cmp1> min_heap; // left

    struct cmp2 {
        public:
        bool operator()(const pair<string,int>& a, const pair<string,int>& b){
            if( a.second < b.second ) {
                return true;
            } else if( a.second == b.second ) {
                if( a.first > b.first ) {
                    return true;
                }
            }
            return false;
        }
    };
    priority_queue<pair<string,int>,vector<pair<string,int>>,cmp2> max_heap; // right

    int q;

public:
    SORTracker() {
        int q = 0;
    }

    void add(string name, int score) {
        if( q == 0 ) {
            max_heap.push({name,score});
            return;
        }
        if( max_heap.empty() ) {
            min_heap.push({name,score});
            auto p = min_heap.top();
            min_heap.pop();
            max_heap.push(p);
            return;
        }

        auto p = max_heap.top();
        bool is_smaller = false;
        if( score < p.second ) {
            is_smaller = true;
        } else if( score == p.second ) {
            if( name > p.first ) {
                is_smaller = true;
            }
        }
        if( is_smaller ) {
            max_heap.push({name,score});
        } else {
            min_heap.push({name,score});
            p = min_heap.top();
            min_heap.pop();
            max_heap.push(p);
        }
        return;
    }

    string get() {
        auto p = max_heap.top();
        max_heap.pop();
        min_heap.push(p);
        ++q;
        return p.first;
    }
};

/**
 * Your SORTracker object will be instantiated and called as such:
 * SORTracker* obj = new SORTracker();
 * obj->add(name,score);
 * string param_2 = obj->get();
 */
