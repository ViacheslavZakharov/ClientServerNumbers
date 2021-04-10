#pragma once

#include <iostream>
#include "NodeStack.h"

using namespace std;

// Шаблонный класс Стек на основе двусвязного списка для возможности двунаправленного обхода.
template <typename T>
class StackList
{
public:
    // Конструктор по умолчанию.
    StackList()
    {
        _pTop = nullptr;
        _pTail = nullptr;
        _count = 0;
    }

    // Конструктор копирования.
    StackList(const StackList& SL) {
        Copy(SL);
    }

    // Помещает элемент в стек. Элемент помещается в начало списка.
    void Push(T item) {
        NodeStack<T>* p = new NodeStack<T>;

        // Если стек не пуст.
        if (_pTop != nullptr) {
            p->item = item;
            // Устанавливаем next на головной элемент.
            p->next = _pTop;
            p->prev = nullptr;
            // Устанавливаем у бывшего головного элемента prev на текущий элемент.
            _pTop->prev = p;
            // Передвигаем головной элемент на текущий.
            _pTop = p;
        }
        else { // Если стек пуст.
            p->prev = nullptr;
            p->item = item;
            p->next = nullptr;
            // Устанавливаем головной и хвостовой указатель на текущий элемент.
            _pTop = p;
            _pTail = p;
        }
        _count++;
    }

    // Возвращает количество элементов в стеке.
    int Count() {
        return _count;
    }

    // Очищает стек - удаляет все элементы из стека.
    void Empty() {
        NodeStack<T>* p; // дополнительный указатель
        NodeStack<T>* p2;

        p = _pTop;

        while (p != nullptr)
        {
            p2 = p; // сделать копию из p
            p = p->next; // перейти на следующий элемент стека
            delete p2; // удалить память, выделенную для предыдущего элемента
        }
        // Выставим вершину и хвост стека в null.
        _pTop = nullptr; 
        _pTail = nullptr;
        _count = 0;
    }

    // Оператор копирования.
    StackList<T>& operator=(const StackList<T>& SL) {
        // Если стек, в который копируем не пуст, предварительно очистим его.
        if (_pTop != nullptr)
        {
            Empty();
        }

        Copy(SL);
        return *this;
    }

    // Выводит стек в поток вывода.
    void Print() {
        if (_pTop == nullptr)
            cout << "stack is empty." << endl;
        else
        {
            NodeStack<T>* p;
            p = _pTop;
            while (p != nullptr)
            {
                cout << p->item << "\t";
                p = p->next;
            }
            cout << endl;
        }
    }

    // Деструктор.
    ~StackList() {
        Empty();
    }

    // Вытягивает элемент из стека.
    T Pop() {
        // Если стек пуст, то операция является невозможной.
        if (_pTop == nullptr) {
            throw "Pop operation is imposible, stack is empty.";
        }

        NodeStack<T>* p;
        T item;
        item = _pTop->item;

        // Перенаправляем указатели _pTop, p.
        p = _pTop;
        _pTop = _pTop->next;
        if (_pTop != nullptr) {
            _pTop->prev = nullptr;
        }

        // Освобождаем память, выделенную под дополнительный указатель.
        delete p;

        _count--;

        // Возвращаем значение головного элемента.
        return item;
    }

    T Top() {
        return _pTop->item;
    }

private:
    // Указатель на вершину стека.
    NodeStack<T>* _pTop;
    // Указатель на хвост стека.
    NodeStack<T>* _pTail;
    // Количество элементов в стеке.
    int _count;

    // Метод копирования стека в текущий.
    void Copy(const StackList& SL) {
        // Дополнительный указатель.
        NodeStack<T>* p;
        _count = SL._count;

        // Инициализируем _pTop и _pTail.
        _pTop = nullptr;
        _pTail = nullptr;

        // Указатель p движется по списку SL._pTail затем _pTail->prev...
        p = SL._pTail;
        while (p != nullptr)
        {
            Push(p->item);
            p = p->prev;
        }
    }
};