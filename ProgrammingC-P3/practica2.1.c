/***********************************************
*
* @Proposito: Práctica 2.1
* @Autor/es: Yannick Suchy Viñolo
* @Fecha creacion: 28/02/2024
* @Fecha ultima modificacion: 29/02/2024
*
************************************************/

//definir las distintas librerias que se van a utilizar
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//definir las constantes que se van a utilizar y sus valores
#define MAX_OBJECTS 50
#define MAX_STRING 100
#define MAX_CHAR 50
#define MAX_BIDS 50

//definir las estructuras que se van a utilizar
//estructura para las pujas, donde nos guardamos el nombre y el precio de la puja
typedef struct {
    char name[MAX_STRING];
    float price;
} Pujas;

//estructura para los objetos, donde nos guardamos el nombre del objeto, el precio minimo, el id, el numero de pujas, si esta activo o no y las pujas
typedef struct {
    char name_object[MAX_STRING];
    float minprice;
    int id;
    int bidnum;
    int active;
    Pujas pujas[MAX_STRING];
} Objeto;

//estructura para las pujas del fichero, donde nos guardamos el id del usuario, el id del objeto y el precio de la puja
typedef struct {
    char user_id[MAX_CHAR];
    int object_id;
    float bid_price;
} FileBid;

/***********************************************
*
* @Finalidad: regresar la palabra de una cadena de palabras
* @Parametros:  char input[]    = cadena de caracteres
                char word[]     = palabra que se va a almacenar
                int pos         = numero de la posicion en la cadena
                char sep        = caracter que nos dice el separador
* @Retorno: nos devuelve la posicion de la cadena
*
************************************************/

int parseString (char input[], char word[], int pos, char sep) {

    //Variables que se van a utilizar
    int i = 0;

    //Bucle while que nos crea una palabra a partir de una cadena de caracteres hasta que llega al final de la cadena o se encuentra con el sepoarador
    while (input[pos] != sep && input[pos] != '\0') {
        word[i] = input[pos];
        i++;
        pos++;
    }

    word[i] = '\0';

    //condicion que nos dice si el separador es el final de la cadena
    if (input[pos] != '\0') {
        pos++;
    }

    return pos;
}

/***********************************************
*
* @Finalidad: convertir un numero de una cadena de caracteres a un entero
* @Parametros:  char num[]  = cadena de caracteres
* @Retorno: nos devuelve el numero en forma de entero
*
************************************************/

int myAtoi (char num[]) {

    //Variables que se van a utilizar
    int number = 0, i = 0;

    //Bucle while que nos convierte una cadena de caracteres a un entero
    while (num[i] != '\0') {
        number = number * 10 + (num[i] - '0');
        i++;
    }

    return number;
}

/***********************************************
*
* @Finalidad: convertir un numero de una cadena de caracteres a un flotante
* @Parametros: char num[]  = cadena de caracteres
* @Retorno: nos devuelve el numero en forma de flotante
*
************************************************/

float myAtof (char num[]) {

    //Variables que se van a utilizar
    float number = 0, res = 0;
    int i = 0, divisor = 1, decimalFound = 0;

    //Bucle while que nos convierte una cadena de caracteres a un flotante, si encuentra un punto, nos dice que ha encontrado un decimal
    while (num[i] != '\0') {
        //condicion que nos dice si ha encontrado un punto
        if (num[i] == '.') {
            decimalFound = 1;
        } else {
            number = number * 10 + (num[i] - '0');
            //condicion que nos dice si ha encontrado un decimal, si lo ha encontrado, multiplica el divisor por 10
            if (decimalFound) {
                divisor *= 10;
            }
        }
        i++;
    }

    //dividir el numero entre el divisor
    res = number / divisor;

    return res;
}

/***********************************************
*
* @Finalidad: leer el fichero de texto de los distintos objetos que se subastan
* @Parametros:  Objeto objeto[] = estructura de los objetos
                int *aux        = puntero que nos dice la cantida de objetos que hay
* @Retorno: nos devuelve 1 si el fichero se ha leido correctamente y si existe y 0 si no se ha leido correctamente y no existe
*
************************************************/

int readFile (Objeto objeto[], int *aux) {

    //Variables que se van a utilizar
    FILE *file;
    char filename[MAX_STRING], trash[MAX_STRING], trash2;
    int i = 0, n = 0;

    //Pedimos el nombre del fichero de texto
    printf("Enter auction file name: ");
    scanf("%s", filename);

    //abrir el fichero de texto
    file = fopen(filename, "r");

    //condicion que nos dice si el fichero existe o no
    if (file == NULL) {
        printf("\n(ERROR) Auction file not found\n");
    } else {
        
        //Prelectura del fichero
        fscanf(file, "%d", &n);
        fgets(trash, MAX_STRING, file);

        //Bucle for que nos lee el fichero de texto y nos guarda los datos en la estructura de los objetos
        for (i = 0; i < n; i++) {
            fscanf(file, "%s", trash);
            fscanf(file, "%c", &trash2);
            fgets(objeto[i].name_object, MAX_STRING, file);
            objeto[i].name_object[strlen(objeto[i].name_object)-1] = '\0';
            objeto[i].active = 1;
            objeto[i].bidnum = 0;
            fscanf(file, "%s", trash);
            fscanf(file, "%d", &objeto[i].id);
            fscanf(file, "%s", trash);
            fscanf(file, "%s", trash);
            fscanf(file, "%f", &objeto[i].minprice);
            fscanf(file, "%s", trash);
        }

        //Puntero que nos da el valor de la cantidad de objetos que se subastan
        *aux = n;

        //cerrar el fichero de texto
        fclose(file);
        return 1;
    }

    return 0;
}

/***********************************************
*
* @Finalidad: mostrar los objetos que se estan subastando
* @Parametros:  Objeto objeto[] = estructura de los objetos
                int n           = cantidad de objetos que se susbastan
* @Retorno: ---.
*
************************************************/

void showObjects (Objeto objeto[], int n) {

    //Variables que se van a utilizar
    int i = 0;

    //Mostrar los objetos que se estan subastando
    printf("\nObjects in auction:\n");

    //Bucle for que nos muestra los objetos que se estan subastando
    for (i = 0; i < n; i++) {
        //condicion que nos dice si el objeto esta activo o no, si esta activo se muestra, si no, no se muestra
        if (objeto[i].active == 1) {
            printf("\t%d\t(%d bids)\t%s\n", objeto[i].id, objeto[i].bidnum, objeto[i].name_object);
        }
    }
}

/***********************************************
*
* @Finalidad: introducir una puja en un objeto
* @Parametros:  Objeto objeto[] = estructura de los objetos
                int n           = cantidad de objetos que se susbastan
* @Retorno: ---.
*
************************************************/

void enterBid (Objeto objeto[], int n) {

    //Variables que se van a utilizar
    char bid[MAX_STRING], name[MAX_STRING], id[MAX_STRING], price[MAX_STRING];
    int i = 0, pos = 0, idaux = 0, flag = 0;
    float priceaux = 0.0;

    //Pedimos el nombre de la puja
    printf("\nEnter bid: ");
    fgets(bid, MAX_STRING, stdin);
    bid[strlen(bid)-1] = '\0';

    //Bucle while que nos lee la puja
    while (bid[pos] != '\0') {
        pos = parseString(bid, name, pos, ' ');
        pos = parseString(bid, id, pos, ' ');
        pos = parseString(bid, price, pos, ' ');
        idaux = myAtoi(id);
        priceaux = myAtof(price);
    }

    //Bucle for que nos introduce la puja en el objeto, si el objeto existe se añade la puja, si no, nos dice que el objeto no existe
    for (i = 0; i < n; i++) {
        //condicion que nos dice si el objeto existe o no
        if (objeto[i].id == idaux) {
            //condicion que nos dice si el objeto esta activo o no, si esta activo se añade la puja, si no, nos dice que la subasta esta cerrada
            if (objeto[i].active == 1) {
                //condicion que nos dice si la el precio de la puja es mayor que el precio minimo, si es mayor se añade la puja, si no, nos dice que la puja no es valida
                if (priceaux > objeto[i].minprice) {
                    objeto[i].pujas[objeto[i].bidnum].price = priceaux;
                    strcpy(objeto[i].pujas[objeto[i].bidnum].name, name);
                    objeto[i].bidnum++;
                flag = 1;
                } else {
                    flag = 3;
                }
            } else {
                flag = 2;
            }
        }
    }

    //condiciones que nos dicen si el objeto existe o no, si la puja es valida o no y si la subasta esta cerrada o no
    if (flag == 0) {
        printf("\n(ERROR) This object does not exist\n");
    } else if (flag == 2) {
        printf("\n(ERROR) The auction for this object is already closed\n");
    } else if (flag == 3) {
        printf("\n(ERROR) The bid is not valid\n");
    }
}

/***********************************************
*
* @Finalidad: leer el fichero binero de las pujas automaticas
* @Parametros:  FileBid filebid[]  = estructura de las pujas automaticas
                Objeto objeto[]    = estructura de los objetos
                int aux            = cantidad de objetos que se susbastan
* @Retorno: ---.
*
************************************************/

void fileBID (FileBid filebid[], Objeto objeto[], int aux) {

    //Variables que se van a utilizar
    FILE *file;
    char filename[MAX_STRING];
    int i = 0, j = 0, k = 0, existe = 0, nexiste = 0, flag = 0;

    //Pedimos el nombre del fichero binario
    printf("\nEnter bids file name: ");
    scanf("%s", filename);

    //abrir el fichero binario
    file = fopen(filename, "rb");

    //Bucle while que nos lee el fichero binario y nos guarda los datos en la estructura de las pujas automaticas
    if (file == NULL) {
        printf("\n(ERROR) Bids file not found\n");
    } else {

        //Prelctura del fichero binario
        fread(&filebid[i], sizeof(FileBid), 1, file);
        //Bucle while que nos lee el fichero binario y nos guarda los datos en la estructura de las pujas automaticas
        while (!feof(file)) {
            i++;
            fread(&filebid[i], sizeof(FileBid), 1, file);
        }

        //Bucles for que nos compara las pujas automaticas con los objetos que se estan subastando
        for (j = 0; j < i; j++) {
            flag = 0;
            for (k = 0; k < aux; k++) {
                //condicion que nos dice si la puja automatica es valida o no
                if ((filebid[j].object_id == objeto[k].id) && (objeto[k].active == 1) && (filebid[j].bid_price > objeto[k].minprice)) {
                    existe++;
                    objeto[k].pujas[objeto[k].bidnum].price = filebid[j].bid_price;
                    strcpy(objeto[k].pujas[objeto[k].bidnum].name, filebid[j].user_id);
                    objeto[k].bidnum++;
                    flag = 1;
                }
            }

            //condicion que nos dice si la puja automatica no existe, si flag es 0
            if (flag == 0) {
                nexiste++;
            }
        }

        //mostrar el numero de pujas automaticas que se han aceptado y el numero de pujas automaticas que se han descartado
        printf("\n%d new bids accepted\n", existe);
        printf("%d new bids discarded\n", nexiste);

        //cerrar el fichero binario
        fclose(file);
    }
}

/***********************************************
*
* @Finalidad: mostrar el estado de un objeto
* @Parametros:  Objeto objeto[]  = estructura de los objetos
                int aux          = cantidad de objetos que se susbastan
* @Retorno: ---.
*
************************************************/

void objectStatus (Objeto objeto[], int aux) {

    //Variables que se van a utilizar
    int id = 0, i = 0, flag = 0, aux2 = 0, aux3 = 0;
    float max = 0;

    //Pedimos el id del objeto
    printf("\nEnter object id: ");
    scanf("%d", &id);

    //Bucle for que va mirando el id de cada objeto
    for (i = 0; i < aux; i++) {
        //condicion que nos dice si el objeto existe o no, dependiendo de si el id coincide
        if (objeto[i].id == id) {
            flag = 1;
            aux2 = i;
        }
    }

    //condicion que nos el objeto existe o no
    if (flag == 0) {
        printf("\n(ERROR) This object does not exist\n");
    } else {
        printf("\nBids for: %s\n", objeto[aux2].name_object);
        //Bucle for que nos muestra las pujas de un objeto
        for (i = 0; i < objeto[aux2].bidnum; i++) {
            //condicion que nos dice si la puja es la mayor o no
            if(objeto[aux2].pujas[i].price > max){
                max = objeto[aux2].pujas[i].price;
                aux3 = i;
            }
        }
        //Bucle for que nos muestra las pujas de un objeto
        for (i = 0; i < objeto[aux2].bidnum; i++) {
            printf("%s\t%.2f", objeto[aux2].pujas[i].name, objeto[aux2].pujas[i].price);
            //condicion que nos muestra la puja mas grande
            if (i == aux3) {
                printf("\t(*)");
            }
            printf("\n");
        }
    }
}

/***********************************************
*
* @Finalidad: cerrar una subasta de un objeto
* @Parametros:  Objeto objeto[]  = estructura de los objetos
                int aux          = cantidad de objetos que se susbastan
* @Retorno: ---.
*
************************************************/

void closeAuction (Objeto objeto[], int aux) {

    //Variables que se van a utilizar
    int id = 0, i = 0, flag = 0, aux2 = 0, aux3 = 0;
    float max = 0;

    //Pedimos el id del objeto
    printf("\nEnter object id: ");
    scanf("%d", &id);

    //Bucle for que va mirando el id de cada objeto
    for (i = 0; i < aux; i++) {
        //condicion que nos dice si el objeto existe o no, dependiendo de si el id coincide
        if (objeto[i].id == id) {
            flag = 1;
            aux2 = i;
        }
    }

    //condicion que nos dice si el objeto existe o no
    if (flag == 0) {
        printf("\n(ERROR) This object does not exist\n");
    } else {
        //condicion que nos dice si la subasta esta cerrada o no
        if (objeto[aux2].active == 0) {
            printf("(ERROR) The auction for this object is already closed\n");
        } else {
            //condicion que nos dice si han subastado 0 personas, si es asi, nos dice que la subasta esta cerrada con 0 pujas
            if (objeto[aux2].bidnum == 0) {
                printf("Auction closed with no bids\n");
                objeto[aux2].active = 0;
            } else {
                //Bucle for que nos mira la puja mas grande
                for (i = 0; i < objeto[aux2].bidnum; i++) {
                    //condicion que nos guarda la puja mas grande
                    if (objeto[aux2].pujas[i].price > max) {
                        max = objeto[aux2].pujas[i].price;
                        aux3 = i;
                    }
                }
                //muestrar el objeto que se ha cerrado y la puja mas grande y las persona que ha ganado
                printf("\nAuction closed for: %s\n", objeto[aux2].name_object);
                printf("Winning bid: %.2f (%s)\n", max, objeto[aux2].pujas[aux3].name);
                objeto[aux2].active = 0;
            }
        }
    }

}

int main () {

    //Variables que se van a utilizar
    Objeto objeto[MAX_OBJECTS];
    FileBid filebid[MAX_BIDS];
    int flag = 0, aux = 0;
    char option[10], trash;

    //condicion que vale 1 si el fichero se ha leido correctamente y si existe y 0 si no se ha leido correctamente y no existe
    if (readFile(objeto, &aux)) {

        //muestra el mensaje de bienvenida
        printf("Welcome to myAuctions!\n");
        scanf("%c", &trash);
        
        //Bucle do while que nos muestra el menu de opciones y nos permite elegir una opcion, se repite hasta que se elige una opcion valida
        do{
            printf("\n1. Show objects | 2. Submit bid | 3. Automatic bids | 4. Object status | 5. Close auction | 6. Quit\n");
            printf("\nEnter option: ");
            scanf("%s", option);
            scanf("%c", &trash);

            //condicion que nos dice si la opcion es valida o no
            if (strcmp(option, "1") == 0 || strcmp(option, "2") == 0 || strcmp(option, "3") == 0 || strcmp(option, "4") == 0 || strcmp(option, "5") == 0 || strcmp(option, "6") == 0) {
                //switch case que escoge la opcion que se ha elegido
                switch (option[0]) {
                    //caso 1 que nos muestra los objetos que se estan subastando
                    case '1':
                        //llamada a la funcion showObjects
                        showObjects(objeto, aux);
                        break;
                    //caso 2 que nos permite introducir una puja en un objeto
                    case '2':
                        //llamada a la funcion enterBid
                        enterBid(objeto, aux);
                        break;
                    //caso 3 que nos permite leer el fichero binero de las pujas automaticas
                    case '3':
                        //llamada a la funcion fileBID
                        fileBID(filebid, objeto, aux);
                        break;
                    //caso 4 que nos permite mostrar el estado de un objeto
                    case '4':
                        //llamada a la funcion objectStatus
                        objectStatus(objeto, aux);
                        break;
                    //caso 5 que nos permite cerrar una subasta de un objeto
                    case '5':
                        //llamada a la funcion closeAuction
                        closeAuction(objeto, aux);
                        break;
                    //caso 6 que nos permite cerrar el programa
                    case '6':
                        //muestra el mensaje de despedida
                        printf("\nSee you in the next auction!");

                        flag = 1;
                        break;
                }
            } else {
                printf("\n(ERROR) Wrong option\n");
            }

        }while (flag == 0) ;
    }

    return 0;
}