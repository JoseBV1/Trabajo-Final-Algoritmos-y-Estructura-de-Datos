#include "pch.h"
#include <iostream>
#include <functional>
#include <string>
#include <conio.h>
#include <fstream>

using namespace std; using namespace System;
#define max(a, b) (a > b? a : b)

void GuardarArchivo(string txt) {
    ofstream archivo;

    archivo.open("los datos.dot", ios::app);
    archivo << txt;

    archivo.close();
}


template<typename T, typename R = T>
class Indexador { //Arbol balanceado
    struct Nodo {
        T       Elemento;
        Nodo* I;
        Nodo* D;
        int     Altura;

        Nodo(T a) : Elemento(a), Altura(0), I(nullptr), D(nullptr) {}
    };
    Nodo* Raiz;
    function<R(T)>  K;
    int             Longitud;
public:
    Indexador(function<R(T)> key = [](T a) { return a; }) : K(key), Raiz(nullptr), Longitud(0) {}
    ~Indexador() {}

    void Ingresar(T a) {
        Ingresar(Raiz, a);
    }

    void inOrder(function<void(T)> proc) {
        inOrder(Raiz, proc);
    }

    void postOrder(function<void(T)> proc) {
        postOrder(Raiz, proc);
    }

    void Mayor(R val, function<void(T)> proc) {
        Mayor(Raiz, val, proc);
    }

    void Menor(R val, function<void(T)> proc) {
        Menor(Raiz, val, proc);
    }

    void ContenidoEn(R val, function<void(T)> proc) {
        ContenidoEn(Raiz, val, proc);
    }

    void NoContenidoEn(R val, function<void(T)> proc) {
        NoContenidoEn(Raiz, val, proc);
    }

    void IniciaCon(R val, function<void(T)> proc) {
        IniciaCon(Raiz, val, proc);
    }

    void FinalizaCon(R val, function<void(T)> proc) {
        FinalizaCon(Raiz, val, proc);
    }

    void Ingresar(Nodo*& a, T b) {
        if (a == nullptr) {
            a = new Nodo(b);
            ++Longitud;
        }
        else {
            if (K(b) < K(a->Elemento)) {
                Ingresar(a->I, b);
            }
            else {
                Ingresar(a->D, b);
            }
            balance(a);
        }
    }

    int Altura(Nodo* a) {
        return a == nullptr ? -1 : a->Altura;
    }

    void ActualizarAltura(Nodo* a) {
        if (a != nullptr) {
            int hl = Altura(a->I);
            int hr = Altura(a->D);

            a->Altura = max(hl, hr) + 1;
        }
    }

    void rI(Nodo*& a) {
        Nodo* aux = a->D;
        a->D = aux->I;
        ActualizarAltura(a);
        aux->I = a;
        ActualizarAltura(aux);
        a = aux;
    }

    void rD(Nodo*& a) {
        Nodo* aux = a->I;
        a->I = aux->D;
        ActualizarAltura(a);
        aux->D = a;
        ActualizarAltura(aux);
        a = aux;
    }

    void balance(Nodo*& a) {
        int hl = Altura(a->I);
        int hr = Altura(a->D);

        if (hr - hl < -1) {
            hl = Altura(a->I->I);
            hr = Altura(a->I->D);
            if (hr > hl) {
                rI(a->I);
            }
            rD(a);
        }
        else if (hr - hl > 1) {
            hl = Altura(a->D->I);
            hr = Altura(a->D->D);
            if (hl > hr) {
                rD(a->D);
            }
            rI(a);
        }
        else {
            ActualizarAltura(a);
        }
    }

    void inOrder(Nodo* a, function<void(T)> proc) {
        if (a != nullptr) {
            inOrder(a->I, proc);
            proc(a->Elemento);
            inOrder(a->D, proc);
        }
    }

    void postOrder(Nodo* a, function<void(T)> proc) {
        if (a != nullptr) {
            postOrder(a->I, proc);
            postOrder(a->D, proc);
            proc(a->Elemento);
        }
    }

    void Mayor(Nodo* a, R val, function<void(T)> proc) {
        if (a != nullptr) {
            if (val < K(a->Elemento)) proc(a->Elemento);
            Mayor(a->D, val, proc);
        }
    }

    void Menor(Nodo* a, R val, function<void(T)> proc) {
        if (a != nullptr) {
            if (val > K(a->Elemento)) proc(a->Elemento);
            Menor(a->I, val, proc);
        }
    }

    void ContenidoEn(Nodo* a, R val, function<void(T)> proc) {
        if (a != nullptr) {
            string elem = K(a->Elemento);
            auto it = elem.find(val);
            if (it != string::npos) proc(a->Elemento);
            ContenidoEn(a->D, val, proc);
            ContenidoEn(a->I, val, proc);
        }
    }

    void NoContenidoEn(Nodo* a, R val, function<void(T)> proc) {
        if (a != nullptr) {
            string elem = K(a->Elemento);
            auto it = elem.find(val);
            if (it == string::npos) proc(a->Elemento);
            NoContenidoEn(a->D, val, proc);
            NoContenidoEn(a->I, val, proc);
        }
    }

    void IniciaCon(Nodo* a, R val, function<void(T)> proc) {
        if (a != nullptr) {
            string elem = K(a->Elemento);
            if (elem.front() == val.front()) proc(a->Elemento);
            IniciaCon(a->D, val, proc);
            IniciaCon(a->I, val, proc);
        }
    }

    void FinalizaCon(Nodo* a, R val, function<void(T)> proc) {
        if (a != nullptr) {
            string elem = K(a->Elemento);
            if (elem.at(elem.length() - 1) == val.front()) proc(a->Elemento);
            FinalizaCon(a->D, val, proc);
            FinalizaCon(a->I, val, proc);
        }
    }
};

template <typename T>
class Fila { //Lista simplemente enlazada
    struct Nodo {
        T       Elemento;
        Nodo* Siguiente;

        Nodo(T a = "", Nodo* b = nullptr) : Elemento(a), Siguiente(b) {}
    };
    Nodo* Inicio;
    int Longitud;
public:
    Fila(int Columnas) : Inicio(nullptr), Longitud(Columnas) {}
    ~Fila() {
        Nodo* aux = Inicio;
        while (aux != nullptr) {
            aux = Inicio;
            Inicio = Inicio->Siguiente;
            delete aux;
        }
    }
    void agregaInicial(T a) {
        Nodo* nuevo = new Nodo(a, Inicio);
        if (nuevo != nullptr) {
            Inicio = nuevo;
        }
    }

    void agregaPos(T a, int b) {
        if (b > Longitud) return;
        if (b == 0) {
            agregaInicial(a);
        }
        else {
            Nodo* aux = Inicio;
            for (int i = 1; i < b; i++) {
                aux = aux->Siguiente;
            }
            Nodo* nuevo = new Nodo(a, aux->Siguiente);
            if (nuevo != nullptr) {
                aux->Siguiente = nuevo;
            }
        }
    }

    void agregaFinal(T a) {
        agregarPos(a, Longitud);
    }

    void modificarInicial(T a) {
        if (Longitud > 0) {
            Inicio->Elemento = a;
        }
    }

    void modificarPos(T a, int b) {
        if (b >= 0 && b < Longitud) {
            Nodo* aux = Inicio;
            for (int i = 0; i < b; i++) {
                aux = aux->Siguiente;
            }
            aux->Elemento = a;
        }
    }

    void modificarFinal(T a) {
        modificarPos(a, Longitud - 1);
    }

    T obtenerInicial() {
        return obtenerPos(0);
    }

    T obtenerPos(int a) {
        if (a >= 0 && a < Longitud) {
            Nodo* aux = Inicio;
            for (int i = 0; i < a; i++) {
                aux = aux->Siguiente;
            }
            return aux->Elemento;
        }
        else {
            return "";
        }
    }

    T obtenerFinal() {
        return obtenerPos(Longitud - 1);
    }
};

template <typename T>
class Tabla {
    Fila<T>** F;
    Fila<T>** FiltradoF;
    Fila<T>** OrdenadoF;
    Indexador<Fila<T>*, T>* Arbol;
    string* NombreDeColumnas;
    int NumeroDeColumnas;
    int NumeroDeFilas;
public:
    Tabla(int Columnas) {
        F = new Fila<T>*;
        NombreDeColumnas = new string[Columnas];
        NumeroDeColumnas = Columnas;
        NumeroDeFilas = 0;
    }
    ~Tabla() {}

    void NombrarCabeceras() {
        string Nombre;
        for (int i = 0; i < NumeroDeColumnas; ++i) {
            cout << "Ingrese el nombre de la columna " << i + 1 << ": ";
            cin >> Nombre;
            NombreDeColumnas[i] = Nombre;
        }
    }

    void InsertarDatos() {
        F[NumeroDeFilas] = new Fila<T>(NumeroDeColumnas);
        string Datos;
        for (int i = 0; i < NumeroDeColumnas; ++i) {
            cout << "Ingrese datos para " << NombreDeColumnas[i] << ": ";
            cin >> Datos;
            F[NumeroDeFilas]->agregaPos(Datos, i);
        }
        ++NumeroDeFilas;
        cout << "\nPRESIONE UNA TECLA"; getch();
    }

    void IndexarDatos(int ColOrdenar, Fila<T>** tabla) {
        auto prueba = [ColOrdenar](Fila<T>* a) { return a->obtenerPos(ColOrdenar); };
        Arbol = new Indexador<Fila<T>*, T>(prueba);

        for (int i = 0; i < NumeroDeFilas; ++i) {
            Arbol->Ingresar(tabla[i]);
        }
    }

    void SeleccionarDatos() {
        cout << "Ingrese el nombre de la columna a mostrar: ";
        string NomColumna;
        cin >> NomColumna;
        int NumColumna;
        for (int i = 0; i < NumeroDeColumnas; ++i) {
            if (NomColumna == NombreDeColumnas[i]) NumColumna = i;
        }
        cout << NombreDeColumnas[NumColumna] << endl;
        for (int i = 0; i < NumeroDeFilas; ++i) {
            cout << F[i]->obtenerPos(NumColumna) << endl;
        }
        cout << "\nPRESIONE UNA TECLA"; getch();
    }

    void FiltrarDatos() {
        Fila<T>** auxFD = new Fila<T>*;
        for (int i = 0; i < NumeroDeFilas; ++i) {
            auxFD[i] = new Fila<T>(NumeroDeColumnas);
            for (int j = 0; j < NumeroDeColumnas; ++j) {
                auxFD[i]->agregaPos(F[i]->obtenerPos(j), j);
            }
        }
        while (1) {
            cout << "Ingrese el nombre de la columna a filtrar: ";
            string NomColumna;
            cin >> NomColumna;
            int NumColumna;
            for (int i = 0; i < NumeroDeColumnas; ++i) {
                if (NomColumna == NombreDeColumnas[i]) NumColumna = i;
            }
            IndexarDatos(NumColumna, auxFD);
            cout << "Ingrese el valor para el filtro: ";
            string palabra;
            cin >> palabra;
            int cont = NumeroDeColumnas;
            int prueba = 0;
            auto GuardarFiltros = [cont, &auxFD, &prueba, NumColumna](Fila<T>* a) {
                cout << a->obtenerPos(NumColumna) << endl;
                auxFD[prueba] = a;
                prueba++;
            };
            cout << "Indique el tipo de filtrado: " << endl;
            cout << "1. Mayor" << endl;
            cout << "2. Menor" << endl;
            cout << "3. Contenido en" << endl;
            cout << "4. No contenido en" << endl;
            cout << "5. Inicia con" << endl;
            cout << "6. Finaliza Con" << endl;
            int OpcionDeFiltrado;
            cin >> OpcionDeFiltrado;
            cout << NombreDeColumnas[NumColumna] << endl;
            switch (OpcionDeFiltrado) {
            case 1: Arbol->Mayor(palabra, GuardarFiltros);
                break;
            case 2: Arbol->Menor(palabra, GuardarFiltros);
                break;
            case 3: Arbol->ContenidoEn(palabra, GuardarFiltros);
                break;
            case 4: Arbol->NoContenidoEn(palabra, GuardarFiltros);
                break;
            case 5: Arbol->IniciaCon(palabra, GuardarFiltros);
                break;
            case 6: Arbol->FinalizaCon(palabra, GuardarFiltros);
                break;
            default: break;
            }
            for (int i = prueba; i < NumeroDeFilas; ++i) {
                for (int j = 0; j < NumeroDeColumnas; ++j) {
                    auxFD[i]->modificarPos("", j);
                }
            }
            cout << "Filtrar la tabla filtrada? Si(1) o No(0): ";
            bool segundo;
            cin >> segundo;
            if (!segundo) break;    cout << "\nPRESIONE UNA TECLA"; getch();
        }
        FiltradoF = auxFD;
    }

    void OrdenarDatos() {
        Fila<T>** auxOD = new Fila<T>*;
        for (int i = 0; i < NumeroDeFilas; ++i) {
            auxOD[i] = new Fila<T>(NumeroDeColumnas);
            for (int j = 0; j < NumeroDeColumnas; ++j) {
                auxOD[i]->agregaPos(F[i]->obtenerPos(j), j);
            }
        }
        cout << "Ingrese el nombre de la columna a ordenar: ";
        string NomColumna;
        cin >> NomColumna;
        int NumColumna;
        for (int i = 0; i < NumeroDeColumnas; ++i) {
            if (NomColumna == NombreDeColumnas[i]) NumColumna = i;
        }
        IndexarDatos(NumColumna, auxOD);
        int cont = NumeroDeColumnas;
        int prueba = 0;
        auto GuardarOrdenado = [cont, &auxOD, &prueba](Fila<T>* a) {
            for (int i = 0; i < cont; ++i) {

                cout << a->obtenerPos(i) << " ";
            }
            cout << endl;
            auxOD[prueba] = a;
            prueba++;
        };
        Arbol->inOrder(GuardarOrdenado);
        OrdenadoF = auxOD;
        cout << "\nPRESIONE UNA TECLA"; getch();

    }

    void ExportarDatos() {
        //Principal
        cout << "Tabla Principal" << endl;
        for (int i = 0; i < NumeroDeColumnas; ++i) {
            cout << NombreDeColumnas[i] << " ";
            GuardarArchivo(NombreDeColumnas[i] + "\t\t");

        }
        GuardarArchivo("\n------------------------------------------------------------------\n");
        cout << endl;
        for (int i = 0; i < NumeroDeFilas; ++i) {
            for (int j = 0; j < NumeroDeColumnas; ++j) {
                cout << F[i]->obtenerPos(j) << " ";
                GuardarArchivo(F[i]->obtenerPos(j) + "\t\t\t");
            }          
            GuardarArchivo("\n\n");
            cout << endl;
        }
        GuardarArchivo("\n\n");

        //Ordenada
        cout << "Tabla Ordenada" << endl;
        GuardarArchivo("\nTabla Ordenada");
        for (int i = 0; i < NumeroDeColumnas; ++i) {
            cout << NombreDeColumnas[i] << " ";
            GuardarArchivo(NombreDeColumnas[i] + "\t\t");
        }
        GuardarArchivo("\n------------------------------------------------------------------\n");
        cout << endl;
        for (int i = 0; i < NumeroDeFilas; ++i) {
            for (int j = 0; j < NumeroDeColumnas; ++j) {
                cout << OrdenadoF[i]->obtenerPos(j) << " ";
                GuardarArchivo(OrdenadoF[i]->obtenerPos(j) + "\t\t\t");
            }
            GuardarArchivo("\n\n");
            cout << endl;
        }
        GuardarArchivo("\n\n");
        //Filtrada
        cout << "Tabla Filtrada" << endl;
        GuardarArchivo("\nTabla Filtrada");
        for (int i = 0; i < NumeroDeColumnas; ++i) {
            cout << NombreDeColumnas[i] << " ";
            GuardarArchivo(NombreDeColumnas[i] + "\t\t");
        }
        GuardarArchivo("\n------------------------------------------------------------------\n");
        cout << endl;
        for (int i = 0; i < NumeroDeFilas; ++i) {
            for (int j = 0; j < NumeroDeColumnas; ++j) {
                cout << FiltradoF[i]->obtenerPos(j) << " ";
                GuardarArchivo(FiltradoF[i]->obtenerPos(j) + "\t\t\t");
            }
            GuardarArchivo("\n\n");
            cout << endl;
        }
        GuardarArchivo("\n\n");
        cout << "\nPRESIONE UNA TECLA"; getch();

    }
};

class Controlador {
    Tabla<string>** TablaNueva;
    string* NombreDeTablas;
    int NumeroDeTablas;
public:
    Controlador() {
        TablaNueva = new Tabla<string>*;
        NombreDeTablas = new string[10];
        NumeroDeTablas = 0;
    }
    ~Controlador() {}

    void CrearTabla() {
        cout << "Ingrese nombre de tabla: ";
        string NombreDeTabla;
        cin >> NombreDeTabla;
        NombreDeTablas[NumeroDeTablas] = NombreDeTabla;
        cout << "Ingrese cantidad de columnas: ";
        int Columnas;
        cin >> Columnas;
        TablaNueva[NumeroDeTablas] = new Tabla<string>(Columnas);
        TablaNueva[NumeroDeTablas]->NombrarCabeceras();
        NumeroDeTablas++;
        cout << "\nPRESIONE UNA TECLA"; getch();

    }

    void InsertarDatos() {
        int a = GetNumeroDeTabla();
        TablaNueva[a]->InsertarDatos();
    }

    void SeleccionarDatos() {
        int a = GetNumeroDeTabla();
        TablaNueva[a]->SeleccionarDatos();
    }
    void FiltrarDatos() {
        int a = GetNumeroDeTabla();
        TablaNueva[a]->FiltrarDatos();
    }

    void OrdenarDatos() {
        int a = GetNumeroDeTabla();
        TablaNueva[a]->OrdenarDatos();
    }

    void ExportarDatos() {
        int a = GetNumeroDeTabla();
        TablaNueva[a]->ExportarDatos();
    }

    int GetNumeroDeTabla() {
        cout << "Ingrese el nombre de tabla a usar: ";
        string NomTabla;
        cin >> NomTabla;
        int NumTabla;
        for (int i = 0; i < NumeroDeTablas; ++i) {
            if (NomTabla == NombreDeTablas[i]) NumTabla = i;
        }
        return NumTabla;
    }
};

void Menu(Controlador* a) {
    int ucan6with4 = 0;
    int ucan6with5 = 0;
    int Opcion;
    while (1) {
    Console::Clear();
    cout << "Bienvenido! Escoga una función" << endl;
    cout << "1. Crear tabla" << endl;
    cout << "2. Insertar datos" << endl;
    cout << "3. Seleccionar datos" << endl;
    cout << "4. Filtrar datos" << endl;
    cout << "5. Ordenar datos" << endl;
    cout << "6. Exportar datos" << endl;
        cin >> Opcion;
        if (Opcion == 4&&ucan6with4==0) ucan6with4 = 1;
        if (Opcion == 5&&ucan6with5==0) ucan6with5 = 1;
        if (Opcion == 6)
    { 
        if (ucan6with4 == 1 && ucan6with5 == 1)
            { 
        Opcion = 6;
            }
        else
        {
            cout << "Ingresa una opción distinta a 6 porque aún no has filtrado u ordenado. " << endl;
            cin >> Opcion;
        }
    }
        switch (Opcion) {
        case 1: a->CrearTabla();
            break;
        case 2: a->InsertarDatos();
            break;
        case 3: a->SeleccionarDatos();
            break;
        case 4: a->FiltrarDatos();
            break;
        case 5: a->OrdenarDatos();
            break;
        case 6: a->ExportarDatos();
            break;
        default: break;
        }
    }
};

int main() {
    Controlador* M = new Controlador();
    Menu(M);
    return 0;
}