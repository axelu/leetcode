
// 1172. Dinner Plate Stacks
// https://leetcode.com/problems/dinner-plate-stacks/





class DinnerPlates {
private:
    vector<vector<int>> stacks;
    int capacity;
    set<int> below_capacity_stacks;
    set<int> non_empty_stacks;

    int _popAtStack(int index) {

        int ret = stacks[index].back();

        stacks[index].pop_back();
        if( stacks[index].size() == capacity - 1 )
            below_capacity_stacks.insert(index);
        if( stacks[index].empty() )
            non_empty_stacks.erase(index);

        return ret;
    }

public:
    DinnerPlates(int capacity) {
        this->capacity = capacity;
        stacks.push_back({});
        below_capacity_stacks.insert(0);
    }

    void push(int val) {
        int index = *below_capacity_stacks.begin();
        stacks[index].push_back(val);

        if( stacks[index].size() == capacity ) {
            below_capacity_stacks.erase(index);
            if( below_capacity_stacks.empty() ) {
                stacks.push_back({});
                below_capacity_stacks.insert(stacks.size()-1);
            }
        }
        if( stacks[index].size() == 1 ) {
            non_empty_stacks.insert(index);
        }
        return;
    }

    int pop() {
        if( non_empty_stacks.empty() )
            return -1;

        int index = *non_empty_stacks.rbegin();
        return _popAtStack(index);
    }

    int popAtStack(int index) {
        if( index >= stacks.size() || stacks[index].empty() )
            return -1;

        return _popAtStack(index);    }
};

/**
 * Your DinnerPlates object will be instantiated and called as such:
 * DinnerPlates* obj = new DinnerPlates(capacity);
 * obj->push(val);
 * int param_2 = obj->pop();
 * int param_3 = obj->popAtStack(index);
 */
