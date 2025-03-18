#include <iostream>

// Estudiantes: Johan Andres Paz Barrantes - Wendy yulisa Diaz Garcia

#include <cstring> 

using namespace std;

struct nodo {
    int id;
    char nombre[30];
    nodo *sig;
};

nodo *cab = NULL, *aux, *aux2;

void registrar() {
    aux = (nodo*) malloc(sizeof(nodo));
    cout << "Ingrese ID del producto: ";
    cin >> aux->id;
    cout << "Ingrese nombre del producto: ";
    cin >> ws;
    cin.getline(aux->nombre, 30);
    aux->sig = NULL;

    if (!cab) {
        cab = aux;
    } else {
        aux2 = cab;
        while (aux2->sig)
            aux2 = aux2->sig;
        aux2->sig = aux;
    }
    cout << "Producto registrado con exito!\n";
}

void mostrar() {
    aux = cab;
    if (!aux) {
        cout << "No hay productos registrados.\n";
        return;
    }
    while (aux) {
        cout << "ID: " << aux->id << " - Nombre: " << aux->nombre << endl;
        aux = aux->sig;
    }
}

nodo* buscar(int id) {
    aux = cab;
    while (aux) {
        if (aux->id == id)
            return aux;
        aux = aux->sig;
    }
    return NULL;
}

void eliminar(int id) {
    nodo *aux = cab, *prev = NULL;
    while (aux && aux->id != id) {
        prev = aux;
        aux = aux->sig;
    }
    if (!aux) {
        cout << "Producto no encontrado.\n";
        return;
    }
    if (!prev) {
        cab = aux->sig;
    } else {
        prev->sig = aux->sig;
    }
    free(aux);
    cout << "Producto eliminado con exito!\n";
}

int contar() {
    int contador = 0;
    aux = cab;
    while (aux) {
        contador++;
        aux = aux->sig;
    }
    return contador;
}

void modificar(int id) {
    aux = buscar(id);
    if (aux) {
        cout << "Ingrese nuevo nombre: ";
        cin >> ws;
        cin.getline(aux->nombre, 30);
        cout << "Producto modificado con exito!\n";
    } else {
        cout << "Producto no encontrado.\n";
    }
}

void liberarMemoria() {
    while (cab) {
        aux = cab;
        cab = cab->sig;
        free(aux);
    }
}

void agregar_nodo_si_no_esta(int id, char nombre[30]) {
    aux = cab;
    while (aux) {
        if (aux->id == id) {
            cout << "El ID ya existe, no se agregara.\n";
            return;
        }
        aux = aux->sig;
    }
    aux = (nodo*) malloc(sizeof(nodo));
    aux->id = id;
    strcpy(aux->nombre, nombre);
    aux->sig = NULL;

    if (!cab) {
        cab = aux;
    } else {
        aux2 = cab;
        while (aux2->sig) {
            aux2 = aux2->sig;
        }
        aux2->sig = aux;
    }
    cout << "Nodo agregado correctamente.\n";
}

int main() {
    int opcion, id;
    char nombre[30];

    do {
        cout << "\nMenu:\n";
        cout << "1. Agregar producto\n";
        cout << "2. Mostrar productos\n";
        cout << "3. Buscar producto\n";
        cout << "4. Eliminar producto\n";
        cout << "5. Contar productos\n";
        cout << "6. Modificar producto\n";
        cout << "7. Salir\n";
        cout << "8. Agregar nodo que no esté\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrar();
                break;
            case 2:
                mostrar();
                break;
            case 3:
                cout << "Ingrese ID del producto a buscar: ";
                cin >> id;
                if (nodo *p = buscar(id)) {
                    cout << "Producto encontrado - ID: " << p->id << " - Nombre: " << p->nombre << endl;
                } else {
                    cout << "Producto no encontrado.\n";
                }
                break;
            case 4:
                cout << "Ingrese ID del producto a eliminar: ";
                cin >> id;
                eliminar(id);
                break;
            case 5:
                cout << "Total de productos registrados: " << contar() << endl;
                break;
            case 6:
                cout << "Ingrese ID del producto a modificar: ";
                cin >> id;
                modificar(id);
                break;
            case 7:
                liberarMemoria();
                cout << "Memoria liberada. Saliendo...\n";
                break;
            case 8:
                cout << "Ingrese el ID: ";
                cin >> id;
                cout << "Ingrese el nombre: ";
                cin >> ws;
                cin.getline(nombre, 30);
                agregar_nodo_si_no_esta(id, nombre);
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 7);

    return 0;
}
