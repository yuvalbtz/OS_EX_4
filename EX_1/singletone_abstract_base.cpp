#include <pthread.h>
#include <iostream>

// Abstract Singleton class
class Singleton
{
protected:
    static Singleton *instance;
    static pthread_mutex_t mutex;

    Singleton() {} // Protected constructor to prevent direct instantiation

public:
    virtual ~Singleton() {}

    // Static method to provide access to the instance
    static Singleton *getInstance();

    // Pure virtual function to be implemented by derived classes
    virtual void performAction() = 0;
};

// Initialize static members
Singleton *Singleton::instance = nullptr;
pthread_mutex_t Singleton::mutex = PTHREAD_MUTEX_INITIALIZER;

// Derived class implementing the Singleton pattern
class DerivedSingleton : public Singleton
{
private:
    DerivedSingleton() {} // Private constructor for derived singleton

public:
    // Implement the pure virtual function
    void performAction() override
    {
        std::cout << "Performing action in DerivedSingleton" << std::endl;
    }

    // Provide access to the DerivedSingleton instance
    static DerivedSingleton *getInstance()
    {
        if (instance == nullptr)
        {
            pthread_mutex_lock(&mutex);
            if (instance == nullptr)
            {
                instance = new DerivedSingleton();
            }
            pthread_mutex_unlock(&mutex);
        }
        return static_cast<DerivedSingleton *>(instance);
    }
};

// Main function to test
int main()
{
    DerivedSingleton *singleton = DerivedSingleton::getInstance();
    singleton->performAction();

    return 0;
}
