#include <pthread.h>

class Singleton
{
protected:
    static Singleton *instance;
    static pthread_mutex_t mutex;

    Singleton() {} // Protected constructor

public:
    virtual ~Singleton() {}

    static Singleton *getInstance()
    {
        if (instance == nullptr)
        {
            pthread_mutex_lock(&mutex);
            if (instance == nullptr)
            {
                instance = new Singleton();
            }
            pthread_mutex_unlock(&mutex);
        }
        return instance;
    }

    // Pure virtual function to be implemented by derived classes
    virtual void performAction() = 0;
};

// Initialize static members
Singleton *Singleton::instance = nullptr;
pthread_mutex_t Singleton::mutex = PTHREAD_MUTEX_INITIALIZER;
