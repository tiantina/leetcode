class H2O {
public:
    H2O() {
			num_h_ = 0;
      num_o_ = 0;
    }

    void hydrogen(function<void()> releaseHydrogen) {
        std::unique_lock<std::mutex> lock(mutex_);
				
				while(((num_o_ == 0) && (num_h_ >= 2)) || (num_h_ >= 2 * num_o_)) {
					cv_.wait(lock);
				}
				num_h_++;

        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
				cv_.notify_all();
    }

    void oxygen(function<void()> releaseOxygen) {
				std::unique_lock<std::mutex> lock(mutex_);

				
				while(((num_h_ % 2 == 0) && num_o_ >= num_h_ / 2 + 1) || ((num_h_ % 2 == 1) && 2 * num_o_ >= num_h_)) {
					cv_.wait(lock);
				}
				num_o_++;
        
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
				cv_.notify_all();
    }

private:
	std::mutex mutex_;
	std::condition_variable cv_;
	int num_h_;
	int num_o_;
};

void releaseHydrogen() {
	std::cout << "H";
}

void releaseOxygen() {
	std::cout << "O";
}
