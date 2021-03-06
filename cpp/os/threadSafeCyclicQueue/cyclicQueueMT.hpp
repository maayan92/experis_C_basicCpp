#ifndef __CYCLIC_QUEUE_MT_H__
#define __CYCLIC_QUEUE_MT_H__

#include <iosfwd>
#include "semaphore.hpp"
#include "mutex.hpp"

namespace experis {

template<size_t N, class T>
class CyclicQueueMT {
public:
    CyclicQueueMT();
    //CyclicQueueMT(const CyclicQueueMT& a_cyclicQueueMT) = default;
    //~CyclicQueueMT() = default;
    //CyclicQueueMT& operator=(const CyclicQueueMT& a_cyclicQueueMT) = default;

    void AddNewElement(const T& a_newElement);
    T RemoveElement();

private:
    T m_elements[N];
    size_t m_head;
    size_t m_tail;
    Semaphore m_semEmptyPlaces;
    Semaphore m_semElements;
    Mutex m_threadSafeLock;
};

} // experis

namespace experis {

template<size_t N, class T>
CyclicQueueMT<N, T>::CyclicQueueMT()
: m_elements()
, m_head(0)
, m_tail(0)
, m_semEmptyPlaces(N)
, m_semElements(0)
, m_threadSafeLock() {
}

template<size_t N, class T>
void CyclicQueueMT<N, T>::AddNewElement(const T& a_newElement) {
    m_semEmptyPlaces.Wait();
    
    try {
        m_threadSafeLock.Lock();
        m_elements[m_tail] = a_newElement;
        (++m_tail) %= N;
        m_threadSafeLock.Unlock();

        m_semElements.Post();
    }catch(const std::exception& exc) {
        m_semEmptyPlaces.Post();
        throw exc;
    }
}

template<size_t N, class T>
T CyclicQueueMT<N, T>::RemoveElement() {
    m_semElements.Wait();
    
    try {
        m_threadSafeLock.Lock();
        T removedElement = m_elements[m_head];
        (++m_head) %= N;
        m_threadSafeLock.Unlock();

        m_semEmptyPlaces.Post();
        return removedElement;
    }catch(const std::exception& exc) {
        m_semElements.Post();
        throw exc;
    }
}

} // experis

#endif