#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <queue>
#include <ctime>
#include <future>

#include "../includes/operand.hpp"

template <typename T>
struct t_node
{
    t_node<T>* next;
    T data;
};

/*
template <class Type>
class SafeQueue
{

    t_node<Type> *m_head;

public:
    SafeQueue()
    {
        m_head = new t_node<Type>; //first element will be always
        m_head->next = nullptr;
    }

    void Push(Type data)
    {
        t_node<Type> *new_node = new t_node<Type>;
        new_node->data = data;

        while (true)
        {
            new_node->next = m_head;
            if (std::atomic_compare_exchange_weak(m_head, new_node->next, new_node)) break;
        }
    }

    bool Pop(Type &data)
    {
        t_node<Type> *ptr;

        while (true)
        {
            ptr = m_head;
            if (std::atomic_compare_exchange_strong(ptr->next, nullptr, nullptr)) return false;
            if (std::atomic_compare_exchange_strong(m_head, ptr, m_head->next)) break;
        }
        data = ptr->data; delete[] ptr;
        return true;
    }




    SafeQueue(const SafeQueue &cp) = delete;
    SafeQueue(const SafeQueue &&mv) = delete;
    SafeQueue operator=(const SafeQueue &cp) = delete;
    SafeQueue operator=(const SafeQueue &&mv) = delete;

    ~SafeQueue()
    {
        t_node<Type> *ptr = m_head;
        while (true)
        {
            if (std::atomic_compare_exchange_weak(m_head, ptr, m_head->next)) delete[] ptr;
            if (!m_head) break;
            ptr = m_head;
        }
    }
};
*/




void test_push(SafeQueue<int> &qu)
{

	for (int i = 0; i < 1000; ++i) {

		qu.PushBack(i);

	}


}



void test_pop(SafeQueue<int> &qu)
{
	for (int i = 0; i < 1000; ++i) {

		qu.PopFront(i);

	}
}


int main()
{
	SafeQueue<int> qu;

	test_push(qu);
	test_pop(qu);



    return 0;
}


