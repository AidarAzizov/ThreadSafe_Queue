#pragma once

#include <atomic>




template <typename T>
class SafeQueue
{
	struct Node
	{
		T					payload;
		std::shared_ptr<Node>	next;

		Node() {}
		Node(const T &item) { payload = item; }
	};

	std::shared_ptr<Node> m_head;
	std::shared_ptr<Node> m_tail;
public:

	SafeQueue()
	{
		m_head = std::make_shared<Node>();
		m_tail = m_head;
	}

	bool	PopFront(T &item)
	{
		while (true)
		{
			std::shared_ptr<Node>	curr_head = m_head;
			std::shared_ptr<Node>	curr_tail = m_tail;

			if (curr_head == curr_tail)
			{
				if (curr_tail->next)
					std::atomic_compare_exchange_strong(&m_tail, &curr_tail, curr_tail->next);
				else
					return false;
			}
			else
			{
				if (std::atomic_compare_exchange_strong(&m_head, &curr_head, curr_head->next))
				{
					item = curr_head->next->payload;
					return true;
				}
			}
		}
	}

	void	PushBack(const T &item)
	{
		std::shared_ptr<Node>	new_tail = std::make_shared<Node>(item);
		std::shared_ptr<Node>	curr_tail, expected_null;
		while (true)
		{
			curr_tail = std::shared_ptr<Node>(m_tail);

			if (!curr_tail->next)
			{
				expected_null = nullptr;
				if (std::atomic_compare_exchange_strong(&m_tail->next, &expected_null, new_tail))
					break;
			}
			else
				std::atomic_compare_exchange_strong(&m_tail, &curr_tail, curr_tail->next);
		}
		std::atomic_compare_exchange_strong(&m_tail, &curr_tail, new_tail);
	}

	~SafeQueue()
	{

	}
};






class PriorityMutex
{

	std::atomic_bool high_flag;

public:
	PriorityMutex() : high_flag(false)
	{

	}

	void LowLock()
	{



	}
	void LowUnlock()
	{

	}


};


