
// 621. Task Scheduler
// https://leetcode.com/problems/task-scheduler/



class Solution {
private:
    struct Task{
        char key;
        int cnt;
        Task(char k, int c) : key(k), cnt(c) {}
    };

public:
    int leastInterval(vector<char>& tasks, int n) {
        int l = tasks.size();

        // base cases
        if( n == 0 ) return l;
        if( l == 1 ) return 1;

        // count frequency per task
        int fq[26]; memset(fq,0,sizeof fq);
        for(int i = 0; i < l; ++i)
            ++fq[tasks[i]-'A'];
        sort(fq,fq+26,greater<int>());

        auto cmp = [](Task* left, Task* right) { return left->cnt < right->cnt; };
        priority_queue<Task*, vector<Task*>, decltype(cmp)> pq(cmp);
        Task* t;
        for(int i = 0; i < 26; ++i) {
            if( fq[i] == 0 ) break;
            // cout << (char)(i+'A') << " " << fq[i] << endl;
            t = new Task(i+'A',fq[i]);
            pq.push(t);
        }

        int step = 0;
        queue<Task*> q;
        while(true) {
            for(int i = 0; i < n+1; ++i) {
                if( pq.empty() ) {
                    if( !q.empty() ) {
                        // idle
                        // cout << "idle" << endl;
                        ++step;
                    }
                    continue;
                }
                t = pq.top();
                pq.pop();
                // cout << "processing " << t->key << endl;
                ++step;
                --t->cnt;
                if( t->cnt > 0 )
                    q.push(t);
            }
            if( pq.empty() && q.empty() ) break;
            while( !q.empty() ) {
                pq.push(q.front());
                q.pop();
            }
        }
        return step;
    }
};
