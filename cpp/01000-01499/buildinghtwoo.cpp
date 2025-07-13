
// 1117. Building H2O
// https://leetcode.com/problems/building-h2o/





class H2O {
private:
    mutex mtx;
    condition_variable cv_o,cv_h;

    int o_released, o_waiting;
    int h_released, h_waiting;

public:
    H2O() {
        o_released = 0;
        o_waiting = 0;
        h_released = 0;
        h_waiting = 0;
    }

    void hydrogen(function<void()> releaseHydrogen) {
        unique_lock lck(mtx);
        h_waiting += 1;
        while( h_released == 2 ) {
            cv_h.wait(lck);
        }

        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
        h_released += 1;
        h_waiting  -= 1;
        if( h_released == 2 && o_released == 1 ) {
            h_released = 0;
            o_released = 0;
        }

        if( h_released == 0 ) {
            // wake another o if any waiting or another h if any waiting
            if( o_waiting  ) {
                lck.unlock();
                cv_o.notify_one();
            } else if( h_waiting ) {
                lck.unlock();
                cv_h.notify_one();
            }

        } else {
            // h 1 o 0 OR h 2 o 0 OR h 1 o 1
            // wake another h if any waiting
            if( h_released == 1 && h_waiting ) {
                lck.unlock();
                cv_h.notify_one();
            }
        }

        return;
    }

    void oxygen(function<void()> releaseOxygen) {
        unique_lock lck(mtx);
        o_waiting += 1;
        while( o_released == 1 ) {
            cv_o.wait(lck);
        }

        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
        o_waiting -= 1;
        if( h_released != 2 ) {
            o_released = 1;
        } else {
            h_released = 0;
        }

        if( o_released == 0 ) {
            // wake another o if any waiting or another h if any waiting
            if( o_waiting  ) {
                lck.unlock();
                cv_o.notify_one();
            } else if( h_waiting ) {
                lck.unlock();
                cv_h.notify_one();
            }

        } else {
            // wake another h if any waiting
            if( h_waiting ) {
                lck.unlock();
                cv_h.notify_one();
            }
        }

        return;
    }
};
