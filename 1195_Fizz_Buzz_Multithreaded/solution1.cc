class FizzBuzz {
private:
    int n;

public:
    FizzBuzz(int n) {
        this->n = n;
				value = 1;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
			while(true) {
				std::unique_lock<std::mutex> lock(mutex_);
				while((value <= n) && (!((value % 3 == 0) && (value % 5) !=0))) {
					cv_.wait(lock);
				}
				if(value > n) {
					return;
				}
				value++;

				printFizz();
				cv_.notify_all();
			}
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
			while(true) {
				std::unique_lock<std::mutex> lock(mutex_);
				while((value <= n) && (!((value % 3 != 0) && (value % 5) ==0))) {
					cv_.wait(lock);
				}
				if(value > n) {
					return;
				}
				value++;

				printBuzz();
				cv_.notify_all();
			}
    }

    // printFizzBuzz() outputs "fizzbuzz".
		void fizzbuzz(function<void()> printFizzBuzz) {
			while(true) {
				std::unique_lock<std::mutex> lock(mutex_);
				while((value <= n) && (!((value % 3 == 0) && (value % 5) ==0))) {
					cv_.wait(lock);
				}
				if(value > n) {
					return;
				}
				value++;
				printFizzBuzz();
				cv_.notify_all();
			}
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
			while(true) {
				std::unique_lock<std::mutex> lock(mutex_);
				while((value <= n) && (!((value % 3 != 0) && (value % 5) !=0))) {
					cv_.wait(lock);
				}
				if(value > n) {
					return;
				}
				printNumber(value);

				value++;
				cv_.notify_all();
			}
    }

private:
	std::mutex mutex_;
	std::condition_variable cv_;
	int value;
};
