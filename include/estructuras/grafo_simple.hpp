#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include "lista.hpp"
#include "cola.hpp"

template <typename T>
class GrafoSimple
{
    struct Node
    {
        T elemento{};
        int grado{};

        Node() = default;
        Node(const T &nuevo_elemento) : elemento{ nuevo_elemento }, grado{ 0 } {}
    };

    Node **lista_nodos{};
    bool *matriz_adyacencia{};
    int cantidad_nodos{};
    int capacidad{};

public:
    GrafoSimple(int numero_nodos)
        : lista_nodos{ new Node*[numero_nodos]{} }
        , matriz_adyacencia{ new bool[numero_nodos * numero_nodos]{} }
        , cantidad_nodos{ 0 }
        , capacidad{ numero_nodos }
    {
    }

    ~GrafoSimple()
    {
        for (int i{0}; i < this->capacidad; ++i)
        {
            delete this->lista_nodos[i];
        }

        delete[] this->lista_nodos;
        delete[] this->matriz_adyacencia;
    }

    bool is_empty()
    {
        return (this->cantidad_nodos == 0);
    }

    int size()
    {
        return this->cantidad_nodos;
    }

    T remove_node(int indice_nodo)
    {
        verificar_indice(indice_nodo);
        verificar_existencia(indice_nodo);

        T nodo_removido{ this->lista_nodos[indice_nodo]->elemento };

        delete this->lista_nodos[indice_nodo];
        this->lista_nodos[indice_nodo] = nullptr;

        for (int i{0}; i < this->capacidad; ++i)
        {
            if (this->matriz_adyacencia[(this->capacidad * indice_nodo) + i])
            {
                this->matriz_adyacencia[(this->capacidad * indice_nodo) + i] = false;
                this->matriz_adyacencia[(this->capacidad * i) + indice_nodo] = false;

                --this->lista_nodos[i]->grado;
            }
        }

        --this->cantidad_nodos;
        return nodo_removido;
    }

    void set_node(int indice_nodo, const T &elemento)
    {
        verificar_indice(indice_nodo);
        Node *nuevo_nodo{ new Node{elemento} };

        if (this->lista_nodos[indice_nodo] != nullptr)
        {
            delete this->lista_nodos[indice_nodo];

            this->lista_nodos[indice_nodo] = nuevo_nodo;
            return;
        }

        this->lista_nodos[indice_nodo] = nuevo_nodo;
        ++this->cantidad_nodos;
    }

    void update_edge(int indice_nodo_1, int indice_nodo_2, bool enlazar)
    {
        verificar_indice(indice_nodo_1, indice_nodo_2);
        verificar_existencia(indice_nodo_1);
        verificar_existencia(indice_nodo_2);

        if (indice_nodo_1 == indice_nodo_2)
        {
            throw std::logic_error{ "No se permiten ciclos en un grafo simple." };
        }

        this->matriz_adyacencia[(this->capacidad * indice_nodo_1) + indice_nodo_2] = enlazar;
        this->matriz_adyacencia[(this->capacidad * indice_nodo_2) + indice_nodo_1] = enlazar;

        if (enlazar)
        {
            ++this->lista_nodos[indice_nodo_1]->grado;
            ++this->lista_nodos[indice_nodo_2]->grado;
        }
        else
        {
            --this->lista_nodos[indice_nodo_1]->grado;
            --this->lista_nodos[indice_nodo_2]->grado;
        }
    }

    bool contains_node(int indice_nodo)
    {
        verificar_indice(indice_nodo);
        return (this->lista_nodos[indice_nodo] == nullptr) ? false : true;
    }

    bool contains_edge(int indice_nodo_1, int indice_nodo_2)
    {
        verificar_indice(indice_nodo_1, indice_nodo_2);
        verificar_existencia(indice_nodo_1);
        verificar_existencia(indice_nodo_2);

        return (this->matriz_adyacencia[(this->capacidad * indice_nodo_1) + indice_nodo_2]);
    }

    T get_element(int indice_nodo)
    {
        verificar_indice(indice_nodo);
        verificar_existencia(indice_nodo);

        return this->lista_nodos[indice_nodo]->elemento;
    }

    int get_degree(int indice_nodo)
    {
        verificar_indice(indice_nodo);
        verificar_existencia(indice_nodo);

        return this->lista_nodos[indice_nodo]->grado;
    }

    void clear()
    {
        for (int i{0}; i < this->capacidad; ++i)
        {
            delete this->lista_nodos[i];
        }

        delete[] this->lista_nodos;
        this->lista_nodos = new Node*[this->capacidad]{};

        delete[] this->matriz_adyacencia;
        this->matriz_adyacencia = new bool[this->capacidad * this->capacidad]{};
    }

    // El usuario es el responsable de liberar la memoria
    Lista<T> *get_adjacent_nodes(int indice_nodo)
    {
        verificar_indice(indice_nodo);
        verificar_existencia(indice_nodo);

        Lista<T> *nodos_adyacentes{ new Lista<T>{} };

        for (int i{0}; i < this->capacidad; ++i)
        {
            if (this->matriz_adyacencia[(this->capacidad * indice_nodo) + i])
            {
                nodos_adyacentes->insert(0, this->lista_nodos[i]->elemento);
            }
        }

        return nodos_adyacentes;
    }

    void print_matrix()
    {
        for (int i{0}; i < this->capacidad; ++i)
        {
            for (int j{0}; j < this->capacidad; ++j)
            {
                std::cout << this->matriz_adyacencia[(i * this->capacidad) + j] << ' ';
            }
            std::cout << '\n';
        }
    }

private:
    int iterador{};

public:
    void depth_first_search(int indice_nodo)
    {
        verificar_indice(indice_nodo);
        verificar_existencia(indice_nodo);

        bool visitado[this->capacidad] {};
        this->iterador = 0;

        std::cout << '[';
        depth_first_search_recursivo(indice_nodo, visitado);
        std::cout << ']';
    }

    void bradth_first_search(int indice_nodo)
    {
        verificar_indice(indice_nodo);
        verificar_existencia(indice_nodo);

        bool visitado[this->capacidad] {};
        Cola<int> cola{};
        cola.push(indice_nodo);

        this->iterador = 0;

        std::cout << '[';

        int v{};
        while (cola.size() > 0)
        {
            v = cola.pop();
            if (visitado[v])
            {
                continue;
            }

            std::cout << this->lista_nodos[v]->elemento;
            ++this->iterador;

            if (this->iterador < this->cantidad_nodos)
            {
                std::cout << ", ";
            }

            visitado[v] = true;

            for (int i{0}; i < this->capacidad; ++i)
            {
                if (this->matriz_adyacencia[(this->capacidad * v) + i] && !visitado[i])
                {
                    cola.push(i);
                }
            }
        }

        std::cout << ']';
    }

private:
    void verificar_indice(int posicion)
    {
        if (posicion < 0 || posicion >= this->capacidad)
        {
            throw std::out_of_range{ "Indice fuera de rango." };
        }
    }

    void verificar_indice(int posicion_1, int posicion_2)
    {
        if ((posicion_1 < 0 || posicion_1 >= this->capacidad)
            || (posicion_2 < 0 || posicion_2 >= this->capacidad))
        {
            throw std::out_of_range{ "Indice fuera de rango." };
        }
    }

    void verificar_existencia(int indice_nodo)
    {
        if (this->lista_nodos[indice_nodo] == nullptr)
        {
            throw std::invalid_argument
            {
                "El nodo con indice " + std::to_string(indice_nodo) + " no existe."
            };
        }
    }

    void depth_first_search_recursivo(int indice_nodo, bool *visitado)
    {
        std::cout << this->lista_nodos[indice_nodo]->elemento;
        ++this->iterador;

        if (this->iterador < this->cantidad_nodos)
        {
            std::cout << ", ";
        }

        visitado[indice_nodo] = true;

        for (int i{0}; i < this->capacidad; ++i)
        {
            if (this->matriz_adyacencia[(this->capacidad * indice_nodo) + i] && !visitado[i])
            {
                depth_first_search_recursivo(i, visitado);
            }
        }
    }
};