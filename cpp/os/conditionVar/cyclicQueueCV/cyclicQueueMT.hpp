#ifndef __CYCLIC_QUEUE_MT_H__
#define __CYCLIC_QUEUE_MT_H__

#include <iosfwd>
#include "conditionVariable.hpp"

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
    size_t m_countElements;
    Mutex m_threadSafeLock;
    ConditionVariable m_conditionVar;
};

} // experis

namespace experis {

template<size_t N, class T>
CyclicQueueMT<N, T>::CyclicQueueMT()
: m_elements()
, m_head(0)
, m_tail(0)
, m_countElements(0)
, m_threadSafeLock()
, m_conditionVar() {
}

template<size_t N, class T>
void CyclicQueueMT<N, T>::AddNewElement(const T& a_newElement) {
    MutexLocker lockIfFull(m_threadSafeLock);
    while(N == m_countElements) {
        m_conditionVar.Wait(lockIfFull);
    }
    
    m_elements[m_tail] = a_newElement;
    (++m_tail) %= N;
    ++m_countElements;
    m_conditionVar.NotifyOne();
}

template<size_t N, class T>
T CyclicQueueMT<N, T>::RemoveElement() {
    MutexLocker lockIfFull(m_threadSafeLock);
    while(0 == m_countElements) {
        m_conditionVar.Wait(lockIfFull);
    }

    T removedElement = m_elements[m_head];
    (++m_head) %= N;
    --m_countElements;
    m_conditionVar.NotifyOne();
    
    return removedElement;
}

} // experis

#endif