class DiningPhilosophers {
public:
    DiningPhilosophers() {
        
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
				int left = philosopher % 5;
				int right = (philosopher + 1) % 5;

				if(right == 0) {
					mutex_[right].lock();
					mutex_[left].lock();
					pickRightFork();
					pickLeftFork();
					eat();
					putLeftFork();
					putRightFork();
				}else {
					mutex_[left].lock();
					mutex_[right].lock();
					pickLeftFork();
					pickRightFork();
					eat();
					putLeftFork();
					putRightFork();
				}
				
				mutex_[left].unlock();
				mutex_[right].unlock();
    }

private:
	std::mutex mutex_[5];
};


