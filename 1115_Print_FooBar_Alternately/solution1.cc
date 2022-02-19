class FooBar {
private:
    int n;

public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
					std::unique_lock<std::mutex> lock(mutex_);
          while(!turn) {
						cv_.wait(lock);
					}  
					
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
					turn = false;
					cv_.notify_one();
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
					std::unique_lock<std::mutex> lock(mutex_);
          while(turn) {
						cv_.wait(lock);
					}  
            
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
					turn = true;
					cv_.notify_one();
        }
    }

private:
	std::mutex mutex_;
	std::condition_variable cv_;
	bool turn = true;
};

void printFoo() {
	std::cout << "foo";
}

void printBar() {
	std::cout << "bar";
}
