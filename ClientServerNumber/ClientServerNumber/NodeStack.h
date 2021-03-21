#pragma once

// Структура, описывающая узел
template <typename T>
class NodeStack
{
public:
    T item;
    NodeStack<T>* next;
};
