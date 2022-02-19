class Foo {
    std::condition_variable cv;
    bool first_done, second_done;
public:
    Foo() {
        first_done = false;
        second_done = false;
    }

    void first(function<void()> printFirst) {
        
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        first_done = true;
        cv.notify_all();
    }

    void second(function<void()> printSecond) {
        std::mutex m;
        std::unique_lock<mutex> ul(m);
        cv.wait(ul, [&](){
                return first_done;
            });
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        second_done = true;
        cv.notify_all();
    }

    void third(function<void()> printThird) {
        std::mutex m;
        std::unique_lock<mutex> ul(m);
        cv.wait(ul, [&](){
                return second_done;
            });
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};

void printfFirst() {
	std::cout << "first";
}

void printSecond() {
	std::cout << "second";
}

void printThird() {
	std::cout << "third";
}
