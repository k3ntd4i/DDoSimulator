#pragma once

#include "lista.hpp"

template <typename T>
class ColaDoble
{
    Lista<T> lista{};

public:
    ColaDoble() = default;

    int size()
    {
        return lista.size();
    }

    bool is_empty()
    {
        return lista.is_empty();
    } 

    T front()
    {
        return lista.get(0);
    }

    T back()
    {
        return lista.get(lista.length());
    }

    void push_front(const T &elemento)
    {
        lista.insert(0, elemento);
    }

    void push_back(const T &elemento)
    {
        lista.insert(lista.size(), elemento);
    }

    T pop_front()
    {
        return lista.remove(0);
    }

    T pop_back()
    {
        return lista.remove(lista.length());
    }

    void output()
    {
        lista.output();
    }
};
