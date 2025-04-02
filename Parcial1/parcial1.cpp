#include <iostream>

// Integrantes: JOHAN ANDRES PAZ BARRANTES -- ZENEIDA RAMOS PORTOCARRERO

using namespace std;

struct Cliente {
    int codigo;
    char nombre[30];
    int edad;
    char sexo;
    char razon[50];
    Cliente* siguiente;
};

Cliente* clientesEnEspera = NULL;
Cliente* atencionesRealizadas = NULL;
Cliente* nuevoCliente = NULL;
Cliente* actual = NULL;

void agregarCliente() {
    nuevoCliente = (Cliente*)malloc(sizeof(Cliente)); // Cambio aquí

    cout << "Ingrese el codigo del cliente: ";
    cin >> nuevoCliente->codigo;
    cin.ignore();
    cout << "Nombre: ";
    cin.getline(nuevoCliente->nombre, 30);
    cout << "Edad: ";
    cin >> nuevoCliente->edad;
    cout << "Sexo (M/F): ";
    cin >> nuevoCliente->sexo;
    nuevoCliente->sexo = toupper(nuevoCliente->sexo);
    cin.ignore();
    cout << "Razon de la llamada: ";
    cin.getline(nuevoCliente->razon, 50);

    nuevoCliente->siguiente = NULL;

    if (!clientesEnEspera) {
        clientesEnEspera = nuevoCliente;
    } else {
        actual = clientesEnEspera;
        while (actual->siguiente) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoCliente;
    }

    cout << "Cliente añadido con éxito!" << endl;
}

void mostrarClientesEnEspera() {
    actual = clientesEnEspera;
    if (!actual) {
        cout << "No hay clientes en espera." << endl;
        return;
    }

    cout << "\nClientes en espera:" << endl;
    while (actual) {
        cout << "Codigo: " << actual->codigo << endl;
        cout << " | Nombre: " << actual->nombre << endl;
        cout << " | Edad: " << actual->edad << endl;
        cout << " | Sexo: " << actual->sexo << endl;
        cout << " | Razon: " << actual->razon << endl;
        actual = actual->siguiente;
    }
}

void cantidadClientesEnEspera() {
    int contador = 0;
    actual = clientesEnEspera;
    while (actual) {
        contador++;
        actual = actual->siguiente;
    }
    cout << "Clientes en espera: " << contador << endl;
}

void guardarAtencion(Cliente* cliente) {
    cliente->siguiente = atencionesRealizadas;
    atencionesRealizadas = cliente;
}

void atenderCliente() {
    if (!clientesEnEspera) {
        cout << "No hay clientes para atender." << endl;
        return;
    }

    nuevoCliente = clientesEnEspera;
    clientesEnEspera = clientesEnEspera->siguiente;

    if (nuevoCliente->edad < 18) {
        cout << "No se puede atender a menores de edad." << endl;
        nuevoCliente->siguiente = clientesEnEspera;
        clientesEnEspera = nuevoCliente;
        return;
    }

    guardarAtencion(nuevoCliente);

    cout << "Cliente atendido: " << nuevoCliente->nombre << endl;
}

void mostrarHistorialAtenciones() {
    actual = atencionesRealizadas;
    if (!actual) {
        cout << "No hay historial de atenciones." << endl;
        return;
    }

    cout << "\nHistorial de atenciones:" << endl;
    while (actual) {
        cout << "Codigo: " << actual->codigo << " | Nombre: " << actual->nombre
             << " | Edad: " << actual->edad << " | Sexo: " << actual->sexo
             << " | Razon: " << actual->razon << endl;
        actual = actual->siguiente;
    }
}

void deshacerAtencion() {
    if (!atencionesRealizadas) {
        cout << "No hay atenciones previas para revertir." << endl;
        return;
    }

    nuevoCliente = atencionesRealizadas;
    atencionesRealizadas = atencionesRealizadas->siguiente;
    nuevoCliente->siguiente = clientesEnEspera;
    clientesEnEspera = nuevoCliente;

    cout << "Se ha revertido la ultima atencion." << endl;
}

int main() {
    int opcion;
    do {
        cout << "\nMENU" << endl;
        cout << "1. Añadir cliente a la cola" << endl;
        cout << "2. Ver clientes en espera" << endl;
        cout << "3. Contar clientes en espera" << endl;
        cout << "4. Atender al siguiente cliente" << endl;
        cout << "5. Ver historial de atenciones" << endl;
        cout << "6. Revertir ultima atencion" << endl;
        cout << "7. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: agregarCliente(); break;
            case 2: mostrarClientesEnEspera(); break;
            case 3: cantidadClientesEnEspera(); break;
            case 4: atenderCliente(); break;
            case 5: mostrarHistorialAtenciones(); break;
            case 6: deshacerAtencion(); break;
            case 7: cout << "Saliendo del sistema..." << endl; break;
            default: cout << "Opcion invalida. Intente de nuevo." << endl;
        }
    } while (opcion != 7);

    return 0;
}