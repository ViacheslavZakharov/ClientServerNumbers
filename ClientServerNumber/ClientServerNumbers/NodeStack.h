#pragma once
#include "pch.h"
#include "framework.h"

// Структура, описывающая узел стека, основанного на двусвязном списке.
template <typename T>
class NodeStack
{
public:
    // Данные.
    T item;
    // Указатель на следующий элемент.
    NodeStack<T>* next;
    // Указатель на предыдущий элемент.
    NodeStack<T>* prev;
};
