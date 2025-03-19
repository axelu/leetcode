
// 3408. Design Task Manager
// https://leetcode.com/problems/design-task-manager/




class TaskManager {
private:
    map<int,set<int>> by_priority; // key: priority, value: ordered set of taskId's
    unordered_map<int,pair<int,int>> by_taskid; // key taskId, value: {userId, priority}

public:
    TaskManager(vector<vector<int>>& tasks) {
        // tasks = {{userId, taskId, priority}, {userId, taskId, priority}, ...}
        // taskId is unique accross all tasks
        
        for(auto& task: tasks) {
            int userId = task[0];
            int taskId = task[1];
            int priority = task[2];
            add(userId, taskId, priority);
        }
    }
    
    void add(int userId, int taskId, int priority) {
        by_priority[priority].insert(taskId);
        by_taskid[taskId] = {userId, priority};

        return;
    }
    
    void edit(int taskId, int newPriority) {
        // it is guaranteed that taskId exists
        auto t = by_taskid.find(taskId);
        int userId = t->second.first;
        int priority = t->second.second;

        auto priority_it = by_priority.find(priority);
        priority_it->second.erase(taskId);
        if( priority_it->second.empty() )
            by_priority.erase(priority_it);

        by_priority[newPriority].insert(taskId);
        t->second.second = newPriority;        
        
        return;
    }
    
    void rmv(int taskId) {
        // it is guaranteed that taskId exists
        auto t = by_taskid.find(taskId);
        int userId = t->second.first;
        int priority = t->second.second;

        auto priority_it = by_priority.find(priority);
        priority_it->second.erase(taskId);
        if( priority_it->second.empty() )
            by_priority.erase(priority_it);

        by_taskid.erase(t);

        return;
    }
    
    int execTop() {
        if( by_priority.empty() )
            return -1;

        int taskId = *(by_priority.rbegin()->second.rbegin());
        int userId = by_taskid[taskId].first;
        rmv(taskId);

        return userId;
    }
};

/**
 * Your TaskManager object will be instantiated and called as such:
 * TaskManager* obj = new TaskManager(tasks);
 * obj->add(userId,taskId,priority);
 * obj->edit(taskId,newPriority);
 * obj->rmv(taskId);
 * int param_4 = obj->execTop();
 */
