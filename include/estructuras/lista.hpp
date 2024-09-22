#pragma once

#include <iostream>
#include <stdexcept>

template <typename T>
class Lista
{
    struct Nodo
    {
        T elemento{};
        Nodo *nodo_siguiente{};

        Nodo(const T &nuevo_elemento)
            : elemento{ nuevo_elemento }
            , nodo_siguiente{ nullptr }
        {
        }
    };

    Nodo *raiz{ nullptr };
    int longitud{ 0 };

public:
    Lista() = default;

    ~Lista()
    {
        Nodo *nodo_actual{ this->raiz };
        Nodo *nodo_eliminar{};

        while (nodo_actual != nullptr)
        {
            nodo_eliminar = nodo_actual;
            nodo_actual = nodo_actual->nodo_siguiente;

            delete nodo_eliminar;
        }
    }

    bool is_empty()
    {
        return (this->longitud == 0);
    }

    // Numero de elementos total
    int size()
    {
        return this->longitud;
    }

    // Indice maximo
    int length()
    {
        return (this->longitud - 1);
    }

    T get(int posicion)
    {
        verificar_indice(posicion);
        return obtener_nodo(posicion)->elemento;
    }

    int index_of(T x)
    {
        Nodo *nodo_actual{ this->raiz };

        for (int i{0}; i < this->longitud; ++i)
        {
            if (nodo_actual->elemento == x)
            {
                return i;
            }

            nodo_actual = nodo_actual->nodo_siguiente;
        }

        return -1;
    }

    T remove(int posicion)
    {
        verificar_indice(posicion);

        Nodo *nodo_eliminar{ this->raiz };
        Nodo *nodo_anterior{ nullptr };

        for (int i{0}; i < posicion; ++i)
        {
            nodo_anterior = nodo_eliminar;
            nodo_eliminar = nodo_eliminar->nodo_siguiente;
        }

        if (nodo_anterior == nullptr)
        {
            this->raiz = nodo_eliminar->nodo_siguiente;
        }
        else
        {
            nodo_anterior->nodo_siguiente = nodo_eliminar->nodo_siguiente;
        }

        T elemento_removido{ nodo_eliminar->elemento };

        delete nodo_eliminar;
        nodo_eliminar = nullptr;

        --this->longitud;
        return elemento_removido;
    }

    void insert(int posicion, const T &nuevo_elemento)
    {
        if (posicion < 0 || posicion > this->longitud)
        {
            throw std::out_of_range{ "Indice fuera de rango." };
        }

        Nodo *nuevo_nodo{ new Nodo{nuevo_elemento} };

        if (posicion == 0)
        {
            nuevo_nodo->nodo_siguiente = this->raiz;
            this->raiz = nuevo_nodo;
        }
        else
        {
            Nodo *nodo_anterior{ obtener_nodo(--posicion) };

            nuevo_nodo->nodo_siguiente = nodo_anterior->nodo_siguiente;
            nodo_anterior->nodo_siguiente = nuevo_nodo;
        }

        ++this->longitud;
    }

    void output()
    {
        std::cout << '[';

        if (this->longitud > 0)
        {
            Nodo *nodo_actual{ this->raiz };

            std::cout << nodo_actual->elemento;
            for (int i{1}; i < this->longitud; ++i)
            {
                nodo_actual = nodo_actual->nodo_siguiente;
                std::cout << ", " << nodo_actual->elemento;
            }
        }

        std::cout << ']';
    }

private:
    void verificar_indice(int posicion)
    {
        if (posicion < 0 || posicion >= this->longitud)
        {
            throw std::out_of_range{ "Indice fuera de rango." };
        }
    }

    Nodo *obtener_nodo(int posicion)
    {
        Nodo *nodo_actual{ this->raiz };

        for (int i{0}; i < posicion; ++i)
        {
            nodo_actual = nodo_actual->nodo_siguiente;
        }

        return nodo_actual;
    }
};