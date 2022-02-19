class Foo {
public:
    Foo() {
    }

    void first(function<void()> printFirst) {
        
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
				p1.set_value();
    }

    void second(function<void()> printSecond) {
        p1.get_future().wait();
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
				p2.set_value();
    }

    void third(function<void()> printThird) {
				p2.get_future().wait();
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }

private:
	std::promise<void> p1;
	std::promise<void> p2;
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


