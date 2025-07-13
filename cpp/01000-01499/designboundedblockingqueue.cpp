
// 1188. Design Bounded Blocking Queue
// https://leetcode.com/problems/design-bounded-blocking-queue/






class BoundedBlockingQueue {
private:
    int capacity;

    mutex mtx;
    condition_variable cv_enqueue, cv_dequeue;

    bool working;
    queue<int> q;

public:
    BoundedBlockingQueue(int capacity) {
        this->capacity = capacity;
        working = false;
    }

    void enqueue(int element) {
        unique_lock lck(mtx);
        while( working || q.size() == capacity ) {
            cv_enqueue.wait(lck);
        }

        working = true;
        q.push(element);
        working = false;
        lck.unlock();
        cv_dequeue.notify_one();

        return;
    }

    int dequeue() {
        unique_lock lck(mtx);
        while( working || q.size() == 0 ) {
            cv_dequeue.wait(lck);
        }

        working = true;
        int element = q.front();
        q.pop();
        working = false;
        lck.unlock();
        cv_enqueue.notify_one();

        return element;
    }

    int size() {
        return q.size();
    }
};
