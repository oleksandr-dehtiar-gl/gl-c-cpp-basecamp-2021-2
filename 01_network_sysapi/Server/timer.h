#include <functional>
namespace std{class thread;};

class Timer
{
    public:
    void start(int ms, const std::function<void()> &processing);
    void stop();
    std::function <void()> handl;

    private:
    std::thread *th;
    bool active;
    void handle(int ms);
};