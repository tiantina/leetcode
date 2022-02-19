class ZeroEvenOdd {
private:
    int n;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
			for(int i = 0; i < n; i++) {
				std::unique_lock<std::mutex> lock(mutex_);
				while(!zero_) {
					cv_.wait(lock);
				}

				printNumber(0);
				
				if(i % 2 == 0) {
					odd_ = true;
				}else {
					even_ = true;
				}

				zero_ = false;
				cv_.notify_all();
			}
    }

    void odd(function<void(int)> printNumber) {
			for(int i = 1; i <= n; i = i + 2) {
				std::unique_lock<std::mutex> lock(mutex_);
				while(!odd_) {
					cv_.wait(lock);
				}

				printNumber(i);
				
				zero_ = true;
				odd_ = false;
				cv_.notify_all();
			}
    }

    void even(function<void(int)> printNumber) {
			for(int i = 2; i <= n; i = i + 2) {
				std::unique_lock<std::mutex> lock(mutex_);
				while(!even_) {
					cv_.wait(lock);
				}

				printNumber(i);
				
				zero_ = true;
				even_ = false;
				cv_.notify_all();
			}
    }


private:
	std::mutex mutex_;
	std::condition_variable cv_;
	bool zero_ = true;
	bool odd_ = false;
	bool even_ = false;
};

void printNumber(int x) {
	std::cout << x;
}
