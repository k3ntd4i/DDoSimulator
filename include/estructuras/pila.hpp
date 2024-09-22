#pragma once

#include "lista.hpp"

template<typename T>
class Pila
{
    Lista<T> lista{};

public:
    Pila() = default;

    int size()
    {
        return lista.size();
    }

    bool is_empty()
    {
        return lista.is_empty();
    }

    T top()
    {
        return lista.get(0);
    }

    void push(const T &elemento)
    {
        lista.insert(0, elemento);
    }

    T pop()
    {
        return lista.remove(0);
    }

    void output()
    {
        lista.output();
    }
};