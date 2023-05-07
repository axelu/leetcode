
// 2590. Design a Todo List
// https://leetcode.com/problems/design-a-todo-list/




/* as per the constraints we have at most 100 tasks we are dealing with
 * times pontentially up to 20 tags
 *
 */

class TodoList {
private:
    int g_id;

    struct T{
        int id;
        int userId;
        string description;
        int dueDate;
        bool isComplete;
        unordered_set<string> tags;

        T(int id, int userId, string description, int dueDate, unordered_set<string> tags) :
            id(id), userId(userId), description(description), dueDate(dueDate), isComplete(false), tags(tags) {}
    };

    vector<T*> tasks;

    void printTasks() {

        for(auto t: tasks) {
            cout << "id:" << t->id << " ";
            cout << "userId: " << t->userId << " ";
            cout << "description: " << t->description << " ";
            cout << "dueDate: " << t->dueDate << " ";
            cout << "isComplete " << t->isComplete << " ";
            cout << "tags: ";
            for(auto s: t->tags)
                cout << s << " ";
            cout << endl;
        }
    }

public:
    TodoList() {
        g_id = 1;
    }

    int addTask(int userId, string taskDescription, int dueDate, vector<string> tags) {

        int id = g_id++;

        // transfor tags to unordered_set<string>
        unordered_set<string> ttags(tags.begin(),tags.end());

        T* t = new T(id,userId,taskDescription,dueDate,ttags);
        tasks.push_back(t);

        return id;
    }

    vector<string> getAllTasks(int userId) {

        vector<T*> t; // task description, task dueDate
        for(auto task: tasks) {
            if( task->userId == userId && task->isComplete == false)
                t.push_back(task);
        }

        sort(t.begin(),t.end(),[](const T* a, const T* b){
            return a->dueDate < b->dueDate;
        });

        vector<string> ans;
        for(auto task: t)
            ans.push_back(task->description);

        return ans;
    }

    vector<string> getTasksForTag(int userId, string tag) {

        vector<T*> t; // task description, task dueDate
        for(auto task: tasks) {
            if( task->userId == userId && task->isComplete == false && task->tags.find(tag) != task->tags.end() )
                t.push_back(task);
        }

        sort(t.begin(),t.end(),[](const T* a, const T* b){
            return a->dueDate < b->dueDate;
        });

        vector<string> ans;
        for(auto task: t)
            ans.push_back(task->description);

        return ans;
    }

    void completeTask(int userId, int taskId) {

        vector<T*> t; // task description, task dueDate
        for(auto task: tasks) {
            if( task->userId == userId && task->id == taskId )
                t.push_back(task);
        }

        if( !t.empty() )
            t.front()->isComplete = true;

        return;
    }
};

/**
 * Your TodoList object will be instantiated and called as such:
 * TodoList* obj = new TodoList();
 * int param_1 = obj->addTask(userId,taskDescription,dueDate,tags);
 * vector<string> param_2 = obj->getAllTasks(userId);
 * vector<string> param_3 = obj->getTasksForTag(userId,tag);
 * obj->completeTask(userId,taskId);
 */
