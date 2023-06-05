#include <iostream>
#include <coroutine>
#include <chrono>
#include <thread>

class CoroutineObject {
public:
    struct promise_type {
        auto get_return_object() { return CoroutineObject{ handle_type::from_promise(*this) }; }
        
        std::chrono::system_clock::time_point current_time;    
        
        auto initial_suspend() { return std::suspend_always{}; }
        auto final_suspend() noexcept { return std::suspend_always{}; }
        void unhandled_exception() { std::terminate(); }

        auto yield_value(std::chrono::system_clock::time_point time) {
            current_time = time;
            return std::suspend_always{};
        }
    };
    
    using handle_type = std::coroutine_handle<promise_type>;
    CoroutineObject(handle_type handle) : handle_(handle) {}
    ~CoroutineObject() { handle_.destroy(); }

    std::chrono::system_clock::time_point current_time() {
        handle_.resume();
        return handle_.promise().current_time;
    }
    
private:
    handle_type handle_;
};

int main() {
    CoroutineObject coroutine = []() -> CoroutineObject {
        while (true) {
            co_yield std::chrono::system_clock::now();
        }
    }();
    
    for (int i = 0; i < 10; i++) {
        std::cout << "Current time: " << std::chrono::system_clock::to_time_t(coroutine.current_time()) << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}