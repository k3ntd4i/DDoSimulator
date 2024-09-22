#pragma once

#include <iostream>
#include <algorithm>

template <typename T>
class ArbolBinario
{
    T elemento{};
    ArbolBinario<T> *hijo_izquierdo{ nullptr };
    ArbolBinario<T> *hijo_derecho{ nullptr };

    int cantidad_nodos{ 1 };
    int altura{ 1 };

    ArbolBinario<T> *raiz{ nullptr };

    int frecuencia{ 1 };

public:
    ArbolBinario() = default;

    ArbolBinario(const T &elemento_inicial)
        : ArbolBinario{ elemento_inicial, nullptr, nullptr }
    {
    }

    ArbolBinario
    (
        const T &elemento_inicial,
        ArbolBinario<T> *sub_arbol_izquierdo,
        ArbolBinario<T> *sub_arbol_derecho
    )
        : elemento{ elemento_inicial }
        , hijo_izquierdo{ sub_arbol_izquierdo }
        , hijo_derecho{ sub_arbol_derecho }
        , cantidad_nodos{ 1 }
        , altura{ 1 }
        , raiz{ nullptr }
        , frecuencia{ 1 }
    {
        actualizar_datos(sub_arbol_izquierdo, sub_arbol_derecho);
    }

    ~ArbolBinario()
    {
        if (this->raiz != nullptr)
        {
            if (this->raiz->get_left_child() == this)
            {
                this->raiz->remove_subtree(true);
            }
            else // this->raiz->get_right_child() == this
            {
                this->raiz->remove_subtree(false);
            }
        }

        make_tree(T{}, nullptr, nullptr);
    }

    bool is_leaf()
    {
        return (this->cantidad_nodos == 1);
    }

    int size()
    {
        return this->cantidad_nodos;
    }

    // Profundidad maxima: cantidad total de niveles (contando desde 1)
    int height()
    {
        return this->altura;
    }

    // El nivel del nodo respecto a la raiz del arbol al que pertenece (contando desde 1)
    int depth()
    {
        int profundidad{ 1 };
        ArbolBinario<T> *nodo_padre{ this->raiz };

        while (nodo_padre != nullptr)
        {
            profundidad++;
            nodo_padre = nodo_padre->raiz;
        }

        return profundidad;
    }

    ArbolBinario<T> *get_parent()
    {
        return this->raiz;
    }

    ArbolBinario<T> *get_left_child()
    {
        return this->hijo_izquierdo;
    }

    ArbolBinario<T> *get_right_child()
    {
        return this->hijo_derecho;
    }

    T get_element()
    {
        return this->elemento;
    }

    int get_frequency()
    {
        return this->frecuencia;
    }

    void set_left_child(ArbolBinario<T> *sub_arbol_izquierdo)
    {
        if (sub_arbol_izquierdo == nullptr)
        {
            remove_subtree(true);
            return;
        }

        set_child(sub_arbol_izquierdo, true);
        this->hijo_izquierdo = sub_arbol_izquierdo;
    }

    void set_right_child(ArbolBinario<T> *sub_arbol_derecho)
    {
        if (sub_arbol_derecho == nullptr)
        {
            remove_subtree(false);
            return;
        }

        set_child(sub_arbol_derecho, false);
        this->hijo_derecho = sub_arbol_derecho;
    }

    void set_element(const T &nuevo_elemento)
    {
        this->elemento = nuevo_elemento;
    }

    void decrease_frequency()
    {
        this->frecuencia --;
    }

    void reset_frequency()
    {
        this->frecuencia = 1;
    }

    void increase_frequency()
    {
        this->frecuencia ++;
    }

    void increase_frequency(int incremento)
    {
        this->frecuencia = std::max(this->frecuencia += incremento, 1);
    }

    // Reemplazar el arbol existente en la instancia por uno nuevo
    void make_tree
    (
        const T &elemento_inicial,
        ArbolBinario<T> *sub_arbol_izquierdo,
        ArbolBinario<T> *sub_arbol_derecho
    )
    {
        this->elemento = elemento_inicial;

        if (this->hijo_izquierdo != nullptr)
        {
            this->hijo_izquierdo->raiz = nullptr;
        }

        if (this->hijo_derecho != nullptr)
        {
            this->hijo_derecho->raiz = nullptr;
        }

        this->hijo_izquierdo = sub_arbol_izquierdo;
        this->hijo_derecho = sub_arbol_derecho;

        int cantidad_nodos_anterior{ this->cantidad_nodos };
        int altura_anterior{ this->altura };

        this->cantidad_nodos = 1;
        this->altura = 1;

        actualizar_datos(sub_arbol_izquierdo, sub_arbol_derecho);

        if (this->raiz != nullptr)
        {
            actualizar_datos_padre(cantidad_nodos_anterior, altura_anterior);
        }
    }

    ArbolBinario<T> *remove_left_subtree()
    {
        ArbolBinario<T> *arbol_retorno{ this->hijo_izquierdo };
        remove_subtree(true);

        return arbol_retorno;
    }

    ArbolBinario<T> *remove_right_subtree()
    {
        ArbolBinario<T> *arbol_retorno{ this->hijo_derecho };
        remove_subtree(false);

        return arbol_retorno;
    }

private:
    int n_nodos{};
    int iterador{};

public:
    void pre_order()
    {
        std::cout << "[";

        this->n_nodos = this->cantidad_nodos;
        this->iterador = 0;
        pre_order_recursivo(this);

        std::cout << "]";
    }
    
    void in_order()
    {
        std::cout << "[";

        this->n_nodos = this->cantidad_nodos;
        this->iterador = 0;
        in_order_recursivo(this);

        std::cout << "]";
    }

    void post_order()
    {
        std::cout << "[";

        this->n_nodos = this->cantidad_nodos;
        this->iterador = 0;
        post_order_recursivo(this);

        std::cout << "]";
    }

    void level_order()
    {
        std::cout << "[";

        ArbolBinario<T> *array_nodos[this->cantidad_nodos] {};
        array_nodos[0] = this;

        this->iterador = 0;
        int indice_insercion{ 1 };
        for (int i{0}; i < this->cantidad_nodos; i++)
        {
            if (array_nodos[i]->hijo_izquierdo != nullptr)
            {
                array_nodos[indice_insercion] = array_nodos[i]->hijo_izquierdo;
                indice_insercion++;
            }

            if (array_nodos[i]->hijo_derecho != nullptr)
            {
                array_nodos[indice_insercion] = array_nodos[i]->hijo_derecho;
                indice_insercion++;
            }

            std::cout << array_nodos[i]->elemento;

            if (array_nodos[i]->get_frequency() > 1)
            {
                std::cout << '{' << array_nodos[i]->get_frequency() << '}';
            }

            this->iterador ++;

            if (this->iterador < this->cantidad_nodos)
            {
                std::cout << ", ";
            }
        }

        std::cout << "]";
    }

private:
    void actualizar_datos
    (
        ArbolBinario<T> *sub_arbol_izquierdo,
        ArbolBinario<T> *sub_arbol_derecho
    )
    {
        int altura_maxima{ 0 };

        if (sub_arbol_izquierdo != nullptr)
        {
            altura_maxima = sub_arbol_izquierdo->altura;
            this->cantidad_nodos += sub_arbol_izquierdo->cantidad_nodos;
        }

        if (sub_arbol_derecho != nullptr)
        {
            altura_maxima = std::max(altura_maxima, sub_arbol_derecho->altura);
            this->cantidad_nodos += sub_arbol_derecho->cantidad_nodos;
        }

        this->altura += altura_maxima;
    }

    void actualizar_datos_padre(int cantidad_nodos_anterior, int altura_anterior)
    {
        int altura_derecha{ 0 };
        int altura_izquierda{ 0 };
        int diferencia_altura{ 0 };
        int altura_maxima{ 0 };

        ArbolBinario<T> *nodo_padre{ this->raiz };

        int diferencia_nodos{ this->cantidad_nodos - cantidad_nodos_anterior };
        bool calculado{ false };

        do
        {
            nodo_padre->cantidad_nodos += diferencia_nodos;

            if (nodo_padre->hijo_izquierdo != nullptr)
            {
                altura_izquierda = nodo_padre->hijo_izquierdo->altura;
            }

            if (nodo_padre->hijo_derecho != nullptr)
            {
                altura_derecha = nodo_padre->hijo_derecho->altura;
            }

            altura_maxima = std::max(altura_izquierda, altura_derecha);

            if ((altura_maxima + 1) != nodo_padre->altura)
            {
                if (!calculado)
                {
                    diferencia_altura = altura_maxima - altura_anterior;
                    calculado = true;
                }

                nodo_padre->altura += diferencia_altura;
            }

            nodo_padre = nodo_padre->raiz;
        } while (nodo_padre != nullptr);
    }

    void remove_subtree(bool izquierdo)
    {
        int cantidad_nodos_anterior{ this->cantidad_nodos };
        int altura_anterior{ this->altura };

        ArbolBinario<T> *this_hijo{};
        ArbolBinario<T> *hermano_this_hijo{};

        if (izquierdo)
        { 
            this_hijo = this->hijo_izquierdo;
            hermano_this_hijo = this->hijo_derecho;

            this->hijo_izquierdo = nullptr;
        }
        else
        {
            this_hijo = this->hijo_derecho;
            hermano_this_hijo = this->hijo_izquierdo;

            this->hijo_derecho = nullptr;
        }

        if (this_hijo != nullptr)
        {
            this->cantidad_nodos -= this_hijo->cantidad_nodos;
            this_hijo->raiz = nullptr;
        }

        if (hermano_this_hijo != nullptr)
        {
            this->altura = hermano_this_hijo->altura + 1;
        }
        else
        {
            this->altura = 1;
        }

        if (this->raiz != nullptr)
        {
            actualizar_datos_padre(cantidad_nodos_anterior, altura_anterior);
        }
    }

    void set_child(ArbolBinario<T> *sub_arbol, bool izquierdo)
    {
        if (sub_arbol->raiz != nullptr)
        {
            if (sub_arbol->raiz->hijo_izquierdo == sub_arbol)
            {
                sub_arbol->raiz->remove_subtree(true);
            }
            else // sub_arbol->raiz->hijo_derecho == sub_arbol
            {
                sub_arbol->raiz->remove_subtree(false);
            }
        }

        ArbolBinario<T> *this_hijo{};
        ArbolBinario<T> *hermano_this_hijo{};

        if (izquierdo)
        { 
            this_hijo = this->hijo_izquierdo;
            hermano_this_hijo = this->hijo_derecho;
        }
        else
        {
            this_hijo = this->hijo_derecho;
            hermano_this_hijo = this->hijo_izquierdo;
        }

        sub_arbol->raiz = this;
        int cantidad_nodos_anterior{ this->cantidad_nodos };

        if (this_hijo != nullptr)
        {
            this->cantidad_nodos -= this_hijo->cantidad_nodos;
            this_hijo->raiz = nullptr;
        }

        this->cantidad_nodos += sub_arbol->cantidad_nodos;

        int altura_anterior{ this->altura };

        if (hermano_this_hijo != nullptr)
        {
            this->altura = std::max(hermano_this_hijo->altura, sub_arbol->altura) + 1;
        }
        else
        {
            this->altura = sub_arbol->altura + 1;
        }

        if (this->raiz != nullptr)
        {
            actualizar_datos_padre(cantidad_nodos_anterior, altura_anterior);
        }
    }

    void pre_order_recursivo(ArbolBinario<T> *arbol)
    {
        if (arbol == nullptr)
        {
            return;
        }

        std::cout << arbol->elemento;

        if (arbol->get_frequency() > 1)
        {
            std::cout << '{' << arbol->get_frequency() << '}';
        }

        this->iterador ++;

        if (this->iterador < this->n_nodos)
        {
            std::cout << ", ";
        }

        pre_order_recursivo(arbol->hijo_izquierdo);
        pre_order_recursivo(arbol->hijo_derecho);
    }
    
    void in_order_recursivo(ArbolBinario<T> *arbol)
    {
        if (arbol == nullptr)
        {
            return;
        }

        in_order_recursivo(arbol->hijo_izquierdo);

        std::cout << arbol->elemento;

        if (arbol->get_frequency() > 1)
        {
            std::cout << '{' << arbol->get_frequency() << '}';
        }

        this->iterador ++;

        if (this->iterador < this->n_nodos)
        {
            std::cout << ", ";
        }

        in_order_recursivo(arbol->hijo_derecho);
    }

    void post_order_recursivo(ArbolBinario<T> *arbol)
    {
        if (arbol == nullptr)
        {
            return;
        }

        post_order_recursivo(arbol->hijo_izquierdo);
        post_order_recursivo(arbol->hijo_derecho);

        std::cout << arbol->elemento;

        if (arbol->get_frequency() > 1)
        {
            std::cout << '{' << arbol->get_frequency() << '}';
        }

        this->iterador ++;

        if (this->iterador < this->n_nodos)
        {
            std::cout << ", ";
        }
    }
};
