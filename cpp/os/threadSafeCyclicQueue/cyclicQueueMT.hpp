#ifndef __THREAD_SAFE_CYCLIC_QUEUE_H__
#define __THREAD_SAFE_CYCLIC_QUEUE_H__

#include <iosfwd>
#include "semaphore.hpp"

namespace experis {

template<size_t N, class T>
class CyclicQueueMT {
public:
    CyclicQueueMT();
    //CyclicQueueMT(const CyclicQueueMT& a_cyclicQueueMT) = default;
    //~CyclicQueueMT() = default;
    //CyclicQueueMT& operator=(const CyclicQueueMT& a_cyclicQueueMT) = default;

    void AddNewElement(T& a_newElement);
    T RemoveElement();
private:
    T m_array[N];
    size_t m_head;
    size_t m_tail;
    Semaphore m_lockIfFull;
    Semaphore m_lockIfEmpty;
    Semaphore m_threadSafeLock;
};

} // experis

namespace experis {

template<size_t N, class T>
CyclicQueueMT<N, T>::CyclicQueueMT()
: m_array()
, m_head(0)
, m_tail(0)
, m_lockIfFull(N)
, m_lockIfEmpty(0)
, m_threadSafeLock() {
}

template<size_t N, class T>
void CyclicQueueMT<N, T>::AddNewElement(T& a_newElement) {
    m_lockIfFull.Wait();
    
    m_threadSafeLock.Wait();
    m_array[m_tail] = a_newElement;
    (++m_tail) %= N;
    m_threadSafeLock.Post();

    m_lockIfEmpty.Post();
}

template<size_t N, class T>
T CyclicQueueMT<N, T>::RemoveElement() {
    m_lockIfEmpty.Wait();
    
    m_threadSafeLock.Wait();
    T removedElement = m_array[m_head];
    (++m_head) %= N;
    m_threadSafeLock.Post();

    m_lockIfFull.Post();

    return removedElement;
}

} // experis

#endif