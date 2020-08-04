#include "thread.hpp"
#include <errno.h>
#include <assert.h>

namespace experis {

static void* RunnableDo(void* a_threadAction) {
    ((Runnable*)a_threadAction)->Do();
}

Thread::Thread(Runnable &a_threadAction)
: m_thread()
, m_hasJoined(false) {
    int status = pthread_create(&m_thread, NULL, RunnableDo, (void*)&a_threadAction);
    if(0 != status) {
        assert(EINVAL != status);
        assert(EPERM != status);

        if(EAGAIN == status) {
            throw ExcNoResourcesToCreateThread();
        }
        if(EAGAIN == status) {
            throw ExcReachedToMaximum();
        }
        assert(!"undocumented error for pthread_create");
    }
}

Thread::~Thread() {
    Join();
}

void Thread::Join() {
    if(!m_hasJoined) {
        int status = pthread_join(m_thread, NULL);
        if(0 != status) {
            switch(status) {
                case EINVAL:
                    throw ExcThreadNotJoinable();
                case EDEADLK:
                    throw ExcDeadlockDetected();
                case ESRCH:
                    throw ExcThreadNotExist();
                default:
                    assert(!"undocumented error for pthread_join");
            }
        }
        m_hasJoined = true;
    }
}

} // experis