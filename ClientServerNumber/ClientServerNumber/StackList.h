#pragma once

#include <iostream>
#include "NodeStack.h"

using namespace std;

// Шаблонный класс Стек на базе односвязного списка.
template <typename T>
class StackList
{
public:
    // Конструктор по умолчанию.
    StackList(){ pTop = nullptr; _count = 0; }

    // Конструктор копированния
    StackList(const StackList& SL) {
        NodeStack<T>* p; // дополнительные указатели
        NodeStack<T>* p2;
        NodeStack<T>* p3;
        _count = SL._count;

        // Инициализировать pTop
        pTop = nullptr;
        p3 = nullptr;

        p = SL.pTop; // указатель p движется по списку SL.pTop->...
        while (p != nullptr)
        {
            // 1. Сформировать узел p2
            try {
                // попытка выделения памяти
                p2 = new NodeStack<T>;
            }
            catch (bad_alloc e)
            {
                // если память не выделена, то выход
                cout << e.what() << endl;
                return;
            }
            p2->item = p->item;
            p2->next = nullptr;

            // 2. pTop = pTop + p2
            if (pTop == nullptr) // создать очередь
            {
                pTop = p2;
                p3 = p2;
            }
            else
            {
                p3->next = p2;
                p3 = p3->next;
            }

            // 3. Перейти на следующий элемент
            p = p->next;
        }
    }

    // поместить элемент в стек
    // элемент помещается на начало списка
    void Push(T item) {
        NodeStack<T>* p;

        // 1. Сформировать элемент
        try {
            p = new NodeStack<T>; // попытка выделить память
        }
        catch (bad_alloc e)
        {
            // если память не выделилась, то выход
            cout << e.what() << endl;
            return;
        }
        p->item = item;
        p->next = pTop; // p указывает на 1-й элемент

        // 2. Перенаправить pTop на p
        pTop = p;
        _count++;
    }

    // Количество элементов в стеке
    int Count() {
        return _count;
    }

    // очищает стек - удаляет все элементы из стека
    void Empty() {
        NodeStack<T>* p; // дополнительный указатель
        NodeStack<T>* p2;

        p = pTop;

        while (p != nullptr)
        {
            p2 = p; // сделать копию из p
            p = p->next; // перейти на следующий элемент стека
            delete p2; // удалить память, выделенную для предыдущего элемента
        }
        pTop = nullptr; // поправить вершину стека
        _count = 0;
    }

    // оператор копирования
    StackList<T>& operator=(const StackList<T>& LS){
        // есть ли элементы в стеке?
        if (pTop != nullptr) Empty();
        _count = LS._count;

        NodeStack<T>* p; // дополнительный указатель
        NodeStack<T>* p2;
        NodeStack<T>* p3;

        // Инициализировать pTop
        pTop = nullptr;
        p3 = nullptr;

        p = LS.pTop; // указатель p двигается по списку SL.pTop->...
        while (p != nullptr)
        {
            // 1. Сформировать узел p2
            try {
                // попытка выделить память
                p2 = new NodeStack<T>;
            }
            catch (bad_alloc e)
            {
                // если память не выделена, то выход
                cout << e.what() << endl;
                return *this;
            }
            p2->item = p->item;
            p2->next = nullptr;

            // 2. pTop = pTop + p2
            if (pTop == nullptr) // создать стек
            {
                pTop = p2;
                p3 = p2;
            }
            else
            {
                p3->next = p2;
                p3 = p3->next;
            }

            // 3. Перейти на следующий элемент
            p = p->next;
        }
        return *this;
    }

    // вывод стека
    void Print() {
        if (pTop == nullptr)
            cout << "stack is empty." << endl;
        else
        {
            NodeStack<T>* p; // дополнительный указатель
            p = pTop;
            while (p != nullptr)
            {
                cout << p->item << "\t";
                p = p->next;
            }
            cout << endl;
        }
    }

    // деструктор
    ~StackList() {
        Empty();
    }

    // метод, вытягивающий элемент со стека
    T Pop() {
        // проверка, пуст ли стек?
        if (pTop == nullptr) {
            throw "Pop operation is imposible, stack is empty.";
        }

        NodeStack<T>* p2; // дополнительный указатель
        T item;
        item = pTop->item;

        // перенаправить указатели pTop, p2
        p2 = pTop;
        pTop = pTop->next;

        // Освободить память, выделенную под 1-й элемент
        delete p2;

        _count--;

        // вернуть item
        return item;
    }

    T Top(){
        return pTop->item;
    }

private:
    // Указатель на вершину стека
    NodeStack<T>* pTop;
    int _count;
};