
// 1116. Print Zero Even Odd
// https://leetcode.com/problems/print-zero-even-odd/






// 1234567890123456789...
// 0o0e0o0e0o0e0o0e0o0e ...
// 010203040506070809010...



class ZeroEvenOdd {
private:
    int n;
    int i;

    mutex cv_m;
    condition_variable cv_zero,cv_even,cv_odd;

public:
    ZeroEvenOdd(int n) {
        this->n = (2*n) + 1;
        i = 1;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        int x = 0; // we always print 0

        unique_lock lck(cv_m);
        while( i != n ) {
            // cout << "loop zero " << i << endl;
            if( (i % 2) == 0 && i != n ) {
                cv_zero.wait(lck);
            }
            bool printed = false;
            if( (i % 2) && i != n  ) {
                printNumber(x);
                ++i;
                printed = true;
            }

            if( printed && i == n ) {
                // we need to tell the others that we are done
                // cv_zero.notify_one();
                cv_even.notify_one();
                cv_odd.notify_one();
            }
            if( printed && i != n ) {
                // we need to tell the next one
                if( i % 4 == 0 )
                    cv_even.notify_one();
                else
                    cv_odd.notify_one();
            }
        }

        return;
    }

    void even(function<void(int)> printNumber) {
        int x = 2; // the first even number we print
        // Note: if there is a next, its always zero

        unique_lock lck(cv_m);
        while( i != n ) {
            // cout << "loop even " << i << endl;
            if( i % 4 && i != n ) {
                cv_even.wait(lck);
            }
            bool printed = false;
            if( i % 4 == 0 && i != n  ) {
                printNumber(x);
                x += 2;
                ++i;
                printed = true;
            }

            if( printed && i == n ) {
                // we need to tell the others that we are done
                cv_zero.notify_one();
                // cv_even.notify_one();
                cv_odd.notify_one();
            }
            if( printed && i != n ) {
                // we need to tell the next one
                cv_zero.notify_one();
            }
        }

        return;
    }

    void odd(function<void(int)> printNumber) {
        int x = 1; // the first odd number we print
        // Note: if there is a next, its always zero

        unique_lock lck(cv_m);
        while( i != n ) {
            // cout << "loop odd " << i << endl;
            if( (i+2) % 4 && i != n ) {
                cv_odd.wait(lck);
            }
            bool printed = false;
            if( (i+2) % 4 == 0 && i != n  ) {
                printNumber(x);
                x += 2;
                ++i;
                printed = true;
            }

            if( printed && i == n ) {
                // we need to tell the others that we are done
                cv_zero.notify_one();
                cv_even.notify_one();
                // cv_odd.notify_one();
            }
            if( printed && i != n ) {
                // we need to tell the next one
                cv_zero.notify_one();
            }
        }

        return;
    }
};
