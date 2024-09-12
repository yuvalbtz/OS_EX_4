#include <iostream>
#include <pthread.h>
#include <unistd.h> // for sleep()

// Singleton and DerivedSingleton classes (as defined previously)
class Singleton
{
protected:
    static Singleton *instance;
    static pthread_mutex_t mutex;

    Singleton() {} // Protected constructor

public:
    virtual ~Singleton() {}

    static Singleton *getInstance();

    // Pure virtual function to be implemented by derived classes
    virtual void performAction() = 0;
};

// Initialize static members
Singleton *Singleton::instance = nullptr;
pthread_mutex_t Singleton::mutex = PTHREAD_MUTEX_INITIALIZER;

// DerivedSingleton class
class DerivedSingleton : public Singleton
{
private:
    DerivedSingleton() {} // Private constructor for derived singleton

public:
    void performAction() override
    {
        std::cout << "Performing action in DerivedSingleton" << std::endl;
    }

    static DerivedSingleton *getInstance()
    {
        if (instance == nullptr)
        {
            pthread_mutex_lock(&mutex);
            if (instance == nullptr)
            {
                std::cout << "Creating Singleton instance..." << std::endl;
                instance = new DerivedSingleton();
            }
            pthread_mutex_unlock(&mutex);
        }
        return static_cast<DerivedSingleton *>(instance);
    }
};

// Test function for threads
void *testSingleton(void *threadid)
{
    long tid = (long)threadid;
    DerivedSingleton *singleton = DerivedSingleton::getInstance();
    std::cout << "Thread ID: " << tid << " got instance at address: " << singleton << std::endl;
    pthread_exit(NULL);
}

int main()
{
    const int NUM_THREADS = 10;
    pthread_t threads[NUM_THREADS];

    // Create multiple threads to test Singleton's thread safety
    for (long t = 0; t < NUM_THREADS; t++)
    {
        std::cout << "Creating thread " << t << std::endl;
        int rc = pthread_create(&threads[t], NULL, testSingleton, (void *)t);
        if (rc)
        {
            std::cout << "Error: unable to create thread," << rc << std::endl;
            exit(-1);
        }
    }

    // Join threads
    for (long t = 0; t < NUM_THREADS; t++)
    {
        pthread_join(threads[t], NULL);
    }

    std::cout << "All threads finished. Singleton instance should have been created only once." << std::endl;

    pthread_exit(NULL);
}


// how to run 
// g++ singleton_test.cpp -o singleton_test -pthread
//./singleton_test
