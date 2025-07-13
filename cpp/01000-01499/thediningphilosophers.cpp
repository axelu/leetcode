
// 1226. The Dining Philosophers
// https://leetcode.com/problems/the-dining-philosophers/

// both pass, but I have not seen it going to 2 eating in this

/* it appears as if we could have 2 philosophers eating at the same time
   0 2 *
   0 3
   1 3
   1 4
   2 0 * same
   2 4
 */
class DiningPhilosophers {
private:
    mutex mtx;
    condition_variable cv;

    int eating;
    int waiting;
    int peating[5];
    int pwaiting[5];

public:
    DiningPhilosophers() {
        eating = 0;
        waiting = 0;
        memset(peating,0,sizeof peating);
        memset(pwaiting,0,sizeof pwaiting);
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {

        unique_lock lck(mtx);
        waiting += 1;
        pwaiting[philosopher] += 1;

        while( eating == 2 || (
                   eating == 1 && (
                       (philosopher == 0 && (peating[1] != 0 || peating[4] != 0 )) ||
                       (philosopher == 1 && (peating[0] != 0 || peating[4] != 2 )) ||
                       (philosopher == 2 && (peating[1] != 0 || peating[3] != 0 )) ||
                       (philosopher == 3 && (peating[2] != 0 || peating[4] != 0 )) ||
                       (philosopher == 4 && (peating[0] != 0 || peating[3] != 0 ))
                   )
               )
            ) {
            cv.wait(lck);
        }

        eating += 1;
        peating[philosopher] += 1;
        waiting -= 1;
        pwaiting[philosopher] -= 1;

        pickLeftFork();
        pickRightFork();
        eat();
        putRightFork();
        putLeftFork();

        eating -= 1;
        peating[philosopher] -= 1;

        if( waiting && eating == 0 ) {
            lck.unlock();
            cv.notify_one();
            return;
        }

		lck.unlock();
        return;
    }
};




/* it appears as if we could have 2 philosophers eating at the same time
   0 2 *
   0 3
   1 3
   1 4
   2 0 * same
   2 4

    we will just have one eat at a time
 */
class DiningPhilosophers {
private:
    mutex mtx;
    condition_variable cv;

    int eating;
    int waiting;

public:
    DiningPhilosophers() {
        eating = 0;
        waiting = 0;
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {

        unique_lock lck(mtx);
        waiting += 1;

        while( eating )
            cv.wait(lck);

        eating = 1;
        waiting -= 1;

        pickLeftFork();
        pickRightFork();
        eat();
        putRightFork();
        putLeftFork();

        eating = 0;

        if( waiting ) {
            lck.unlock();
            cv.notify_one();
            return;
        }

		lck.unlock();
        return;
    }
};
