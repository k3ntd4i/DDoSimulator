#pragma once

#include <stdexcept>
#include <utility>

template <typename T>
class MaximoHeap
{
    T *heap{};
    int capacidad{};
    int cantidad_nodos{};

public:
    MaximoHeap() : heap{ new T[1]{} }, capacidad{ 1 }, cantidad_nodos{ 0 } {}

    MaximoHeap(int capacidad_inicial)
        : capacidad{ capacidad_inicial }
        , cantidad_nodos{ 0 }
    {
        if (capacidad_inicial < 1)
        {
            throw std::out_of_range{ "La capacidad inicial debe ser mayor o igual a 1" };
        }

        this->heap = new T[capacidad_inicial]{};
    }

    ~MaximoHeap() { delete[] this->heap; }

    bool is_empty()
    {
        return (this->cantidad_nodos == 0);
    }

    int size()
    {
        return this->cantidad_nodos;
    }

    T get_max()
    {
        verificar_longitud();
        return this->heap[0];
    }

    void put(const T &valor)
    {
        if (this->cantidad_nodos == this->capacidad)
        {
            this->capacidad *= 2;
            T *nuevo_arreglo{ new T[this->capacidad]{} };

            for (int i{0}; i < this->cantidad_nodos; ++i)
            {
                nuevo_arreglo[i] = this->heap[i];
            }

            delete[] this->heap;
            this->heap = nuevo_arreglo;
        }

        this->heap[this->cantidad_nodos] = valor;

        heapify_up(this->cantidad_nodos);
        ++this->cantidad_nodos;
    }

    T extract_max()
    {
        verificar_longitud();

        T valor_maximo{ this->heap[0] };
        this->heap[0] = this->heap[--this->cantidad_nodos];

        heapify_down(0);
        return valor_maximo;
    }

private:
    void verificar_longitud()
    {
        if (this->cantidad_nodos <= 0)
        {
            throw std::underflow_error{ "El heap esta vacio.\n" };
        }
    }

    void heapify_up(int indice)
    {
        int indice_padre{};
        while (indice > 0)
        {
            indice_padre = static_cast<int>((indice - 1) / 2);
            if (this->heap[indice_padre] < this->heap[indice])
            {
                std::swap(this->heap[indice_padre], this->heap[indice]);
                indice = indice_padre;
            }
            else
            {
                break;
            }
        }
    }

    void heapify_down(int indice)
    {
        int indice_mayor{};
        int indice_hijo_izquierdo{};
        int indice_hijo_derecho{};
        while (indice < this->cantidad_nodos)
        {
            indice_mayor = indice;
            indice_hijo_izquierdo = (2 * indice) + 1;
            indice_hijo_derecho = (2 * indice) + 2;

            if (indice_hijo_izquierdo < this->cantidad_nodos
                && this->heap[indice_hijo_izquierdo] > this->heap[indice_mayor])
            {
                indice_mayor = indice_hijo_izquierdo;
            }

            if (indice_hijo_derecho < this->cantidad_nodos
                && this->heap[indice_hijo_derecho] > this->heap[indice_mayor])
            {
                indice_mayor = indice_hijo_derecho;
            }

            if (indice_mayor != indice)
            {
                std::swap(this->heap[indice_mayor], this->heap[indice]);
                indice = indice_mayor;
            }
            else
            {
                break;
            }
        }
    }
};