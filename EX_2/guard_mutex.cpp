#include <pthread.h>

class Guard
{
private:
    pthread_mutex_t *mutex;

public:
    Guard(pthread_mutex_t *mtx) : mutex(mtx)
    {
        pthread_mutex_lock(mutex);
    }

    ~Guard()
    {
        pthread_mutex_unlock(mutex);
    }
};