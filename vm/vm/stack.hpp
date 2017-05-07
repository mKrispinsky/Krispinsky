#ifndef STACK_HPP
#define STACK_HPP
#include <iostream>

template <typename T>
class stack
{
public:
	stack();
	stack(T data);
	stack(stack<T>& myStack);
	~stack();
	int push_back();
	int push_back(T data);
	T pop_back();
	T top();
	int size();
	bool empty();

	void swap(stack<T>& RHS);

	stack<T>& operator=(stack<T>& myStack);

	struct node
	{
	public:
		node* next;
		T data;
	};

private:
	node* head;
	int sizevar;
};

template <typename T>
stack<T>::stack()
{
	head = nullptr;
	//head->next = nullptr; A troubled man wrote this line right after that previous one.
	sizevar = 0;
}

template <typename T>
stack<T>::stack(T data)
{
	head = new node;
	head->next = nullptr;
	head->data = data;
	sizevar = 1;
}

template <typename T>
stack<T>::stack(stack<T>& myStack)
{
	head = nullptr;
	sizevar = 0;

	T things[myStack.sizevar];
	node* temp = myStack.head;

	for (int i = 0; i < myStack.sizevar; i++)
	{
		things[i] = temp->data;
		temp = temp->next;
	}


	for (int i = 1; i <= myStack.sizevar; i++)
	{
		std::cerr << things[myStack.sizevar - i] << std::endl;
		this->push_back(things[myStack.sizevar - i]);
	}
}

template <typename T>
stack<T>::~stack()
{
	if (head == nullptr)
		return;

	node* current = head;
	node* previous;

	while (current->next != nullptr)
	{
		previous = current;
		current = current->next;
		delete previous;
	}

	delete current;
}

template <typename T>
int stack<T>::push_back()
{
	node* add = new node;
	add->next = head;
	head = add;

	sizevar++;

	return sizevar;
}

template <typename T>
int stack<T>::push_back(T data)
{
	node* add = new node;
	add->next = head;
	add->data = data;
	head = add;

	sizevar++;

	return sizevar;
}

template <typename T>
T stack<T>::pop_back()
{
	T thinger;

	if (head != nullptr)
	{
		node* temp = head;
		thinger = head->data;
		head = head->next;
		delete temp;
		sizevar--;
	}

	return thinger;
}

template <typename T>
T stack<T>::top()
{
	return head->data;
}

template <typename T>
int stack<T>::size()
{
	return sizevar;
}

template <typename T>
stack<T>& stack<T>::operator=(stack<T>& myStack)
{

	if (this == &myStack)
		return *this;

	while (sizevar > 0)
		this->pop_back();

	T things[myStack.sizevar];
	node* temp = myStack.head;

	for (int i = 0; i < myStack.sizevar; i++)
	{
		things[i] = temp->data;
		temp = temp->next;
	}


	for (int i = 1; i <= myStack.sizevar; i++)
	{
		this->push_back(things[myStack.sizevar - i]);
	}

	return *this;
}

template <typename T>
void stack<T>::swap(stack<T>& RHS)
{
	node* temp = this->head;
	this->head = RHS.head;
	RHS.head = temp;
}

template <typename T>
bool stack<T>::empty()
{
	return (sizevar == 0);
}

#endif
