
// 1114. Print in Order
// https://leetcode.com/problems/print-in-order/



class Foo {
private:
    mutex mtx;
    condition_variable cv1,cv2;
    bool executedFirst, executedSecond;
public:
    Foo() {
        // init instance variables
        executedFirst = false;
        executedSecond = false;
    }

    void first(function<void()> printFirst) {
        unique_lock lck(mtx);

        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();

        executedFirst = true;
        lck.unlock();
        cv1.notify_one();
    }

    void second(function<void()> printSecond) {
        unique_lock lck(mtx);
        while(!executedFirst){
            cv1.wait(lck);
        }

        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();

        executedSecond = true;
        lck.unlock();
        cv2.notify_one();
    }

    void third(function<void()> printThird) {
        unique_lock lck(mtx);
        while(!executedSecond){
            cv2.wait(lck);
        }

        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};
