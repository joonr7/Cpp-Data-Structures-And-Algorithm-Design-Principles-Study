#include <iostream>
#include <algorithm>

struct singly_ll_node
{
	std::string title;
	singly_ll_node* next;
	singly_ll_node* prev;
};

class singly_ll
{
public:
	// typedef 대신 using 쓰기.
	// tip: using 은 새로운 이름이 왼쪽
	using node = singly_ll_node;
	using node_ptr = node*;

private:
	node_ptr head;
	node_ptr tail;
	node_ptr dummy;
public:
	void push_front(std::string val)
	{
		auto new_node = new node {val, NULL, NULL};
		if (head == NULL)
		{
			// this가 비어있을 때
			new_node->next = new_node;
			new_node->prev = new_node;
			tail = new_node;
		}
		else if (tail == head)
		{
			// this가 한개만 있을 때
			new_node->next = head;
			new_node->prev = tail;
			tail->next = new_node;
			tail->prev = new_node;
		}
		else
		{
			new_node->next = head;
			new_node->prev = tail;
			tail->next = new_node;
		}
		head = new_node;
	}

	void push_back(std::string val)
	{
		auto new_node = new node {val, NULL, NULL};
		// this가 비어있을 때
		if (tail == NULL)
		{
			new_node->next = new_node;
			new_node->prev = new_node;
			head = new_node;
		}
		else
		{
			new_node->next = head;
			new_node->prev = tail;
			head->prev = new_node;
		}
		tail = new_node;
	}

	void pop_front()
	{
		auto first = head;
		if (head)
		{
			head = head->next;
			tail->next = head;
			delete first;
		}
	}

	void pop_back()
	{
		auto last = tail;
		if (tail)
		{
			tail = tail->prev;
			head->prev = tail;
			delete last;
		}
	}

	struct singly_ll_iterator
	{
	private:
		node_ptr ptr;

	public:
		singly_ll_iterator(node_ptr p) : ptr(p) {}

		std::string& operator*() { return ptr->title; }

		node_ptr get() { return ptr; }

		singly_ll_iterator& operator++()		// 선행증가
		{
			ptr = ptr-> next;
			return *this;
		}
		singly_ll_iterator operator++(int)		// 후행증가
		{
			singly_ll_iterator result = *this;
			++(*this);
			return result;
		}

		friend bool operator == (const singly_ll_iterator& left,
														const singly_ll_iterator& right)
		{
			return left.ptr == right.ptr;
		}

		friend bool operator!=(const singly_ll_iterator& left,
													const singly_ll_iterator& right)
		{
			return left.ptr != right.ptr;
		}
	};

	// singly_ll_iterator에 더하여, const버전 추가
	singly_ll_iterator begin() { return singly_ll_iterator(head);}
	singly_ll_iterator end() { return singly_ll_iterator(tail); }
	singly_ll_iterator begin() const { return singly_ll_iterator(head);}
	singly_ll_iterator end() const { return singly_ll_iterator(tail); }

	singly_ll() = default;

	singly_ll(const singly_ll& other) : head(NULL), tail(NULL)
	{
		if (other.head)
		{
			head = new node{"", NULL, NULL};
			tail = new node{"", NULL, NULL};
			auto cur = head;
			auto it = other.begin();
			while (true)
			{
				cur->title = *it;

				auto tmp = it;
				++tmp;
				if (tmp == other.end())
					break;

				cur->next = new node{0,NULL,NULL};
				cur = cur->next;
				it = tmp;

			}
		}
	}

	singly_ll(const std::initializer_list<std::string>& ilist) : head(NULL)
	{
		// 오른쪽부터 하나씩 push_front 해서 생성.
		for (auto it = std::rbegin(ilist); it != std::rend(ilist); it++)
		{
			push_front(*it);
		}
	}
};

int main()
{
	singly_ll sll = {"Yanghwa bridge","Peaches","Next level"};
	sll.push_front("Dynamite");
	std::cout << "첫번째 리스트: ";
	// TODO: for문에서 end가 tail인데, end바로 앞까지만 출력함..
	for (auto i : sll)
		std::cout << i << ", ";
	std::cout << std::endl;


	// auto sll2 = sll;
	// 이하 에러문 발생으로 선언 후 딥카피함.
	/*
	terminate called after throwing an instance of 'std::logic_error'
  	what():  basic_string::_M_construct null not valid
	Aborted (core dumped)
	*/
	
	singly_ll sll2;
	sll2 = sll;
	
	sll2.push_front("Solo");
	std::cout << "첫번째 리스트를 복사한 후, 맨 앞에 y를 추가: ";
	for (auto i : sll2)
		std::cout << i << ", ";
	std::cout << std::endl;

	std::cout << "딥카피 후 첫 리스트: ";
	for (auto i : sll)
		std::cout << i << ", ";
	std::cout << std::endl;

	// auto sll3 = sll; // 딥카피
	singly_ll sll3;
	sll3 = sll;
	sll3.pop_front();
	std::cout << "첫번째 리스트 복사한 뒤, 맨 앞 pop :";
	for (auto i : sll3)
		std::cout << i << ", ";
	std::cout << std::endl;


}
