#include "music.h"

/* Auxiliary functions ****************************************************/

//find_instrument(): Busca un instrumento en una estructura tMusicStore y lo retorna un puntero a un tipo tInstrument
tInstrument *find_instrument (tMusicStore m, int code){
    //CREAMOS UNA VARIABLE QUE SERVIRA PARA EL RETURN
    tInstrument *instrumento ;
    instrumento = NULL;
    //VARIABLE PARA CONTROLAR LAS ITERACIONES
    int i = 0;

    //WHILE PARA RECORRER EL CATALOGO HASTA ENCONTRAR EL INSTRUMENTO
    //mientras no hemos acabado de recorrer todos los instrumentos y el instrumento sea NULL (no tenga valor)
    while ((i < m.numInst) && (instrumento == NULL)){
        if (m.catalogue[i].id == code){
            instrumento = &(m.catalogue[i]);
        } else {
            i++;
        }
    }
    return instrumento;
}


/*Retorna el stock del instrumento con id pasado por parametro existente en la tienda 
 * (el stock es un tipo de dato del tipo tInstrumentSet(int idInst y int units)*/
tInstrumentSet *find_instrument_stock (tMusicStore *m, int code){

    tInstrumentSet *stockInstrumento;
    int i;

    stockInstrumento = NULL;
    i = 0;

    while ((i < m->numStock) && (stockInstrumento == NULL)){
        if (m->stock[i].idInst == code){
            stockInstrumento = &(m->stock[i]);
        } else {
            i++;
        }
    }
    return stockInstrumento;
}

//Actualiza el status de un instrumento, high, medium, low o none
void set_availability (tInstrument *ins, int units){
    tStatus status;
    //chequeamos el numero de unidades
    if (units > L3) status = high;
    else if (units > L2) status = medium;
    else if (units > L1) status = low;
    else status = none;
    //actualizamos el valor de la disponibilidad
    ins->availability = status;
    printf("set_availability CORRECTO\n");
}

/* Demanded functions ****************************************************/
/*Dada una estructura del tipo tMusicStore, la
inicializa correctamente dejando los campos internos vacíos.*/
void init_music_store (tMusicStore *m){
    //REVISAMOS LA PRE CONDICIONES
    assert (m != NULL);
    //INICIALIZAMOS A CERO LOS VALORES ENTEROS
    m->numInst = 0;
    m->numStock = 0;
    m->numOrd = 0;
    //¿¿¿¿¿PORQUE LOS PUNTEROS NO SE TOCAN?????
    //printf("init_music_store CORRECTO");
}

/*Dada una estructura del tipo tMusicStore,
añade en el catálogo un nuevo modelo de instrumento con un código,
una descripción y su precio. Inicialmente, el stock no tiene ninguna
unidad del nuevo modelo. Si ya existe el código del modelo en el
catálogo, entonces no se añade y se muestra un mensaje de error.*/
void new_instrument (tMusicStore *m, int id, string desc, float price){
    //REVISAMOS LA PRE CONDICIONES
    assert (m != NULL);
    assert (id > 0);
    assert (price >= 0);

    //1 Buscar si existe el id en el catalogo, si existe dar error, sino seguir!
    tInstrument *instrumento = NULL;
    instrumento = find_instrument (*m, id);
    //if (find_instrument (*m, id) != NULL) //profe
    if (instrumento != NULL){
        printf("ERROR: Instrument %d is already in the catalogue\n", id);
    } else {
        //SABEMOS QUE NO EXISTE ESTE INSTRUMENTO

        if (m->numInst == 0) {
            //SI NO HAY INSTRUMENTOS, HACEMOS ESPACIO PARA 1 INSTRUMENTO
            m->catalogue = (tInstrument *) malloc (sizeof(tInstrument));
        } else {
            //SI YA HAY INSTRUMENTOS, HACEMOS ESPACIO PARA UN INSTRUMENTO MAS
            m->catalogue = (tInstrument *) realloc (m->catalogue, sizeof(tInstrument)* (m->numInst+1));
        }
        /*If it is ok, then add the instrument to the catalogue*/
        if (m->catalogue == NULL)
            printf("ERROR: Memory error\n");
        else {
            m->catalogue[m->numInst].id 		  = id;
            m->catalogue[m->numInst].price 		  = price;
            m->catalogue[m->numInst].availability = none;
            strcpy(m->catalogue[m->numInst].description, desc);
            m->numInst++;
        }
    }
}

/*Dada una estructura del tipo tMusicStore, un
código de modelo de instrumento, y un número de unidades, añade el
número de unidades del modelo al stock. Si el código no se encuentra
en el catálogo, devuelve un mensaje de error. Si el stock ya dispone
de alguna unidad de este modelo, entonces simplemente se
incrementa el número de unidades; en caso contrario, añade el
modelo con las unidades al stock. Si no hay espacio en el stock,
entonces devuelve un mensaje de error.*/

void add_stock(tMusicStore *m, int id, int units){

    /* Check PRE conditions */
    assert (m != NULL);
    assert (id > 0);
    assert (units > 0);

    tInstrument    *instrument;    // int id; string description; float price; tStatus availability;
    tInstrumentSet * instrumentSet; // int id; int units;


    //BUSCAMOS EL INSTRUMENTO EN EL CATALOGO
    instrument = find_instrument(*m, id);
    if (instrument == NULL)
        printf("ERROR: Instrument %d does not appear in the catalogue\n", id);
    else {
        //SABEMOS QUE EXISTE, ENTONCES BUSCAMOS EL STOCK(ID Y UNIDADES)
        instrumentSet = find_instrument_stock(m, id);
        if (instrumentSet != NULL){
            //EXISTE EL STOCK, AÑADIMOS LAS UNIDADES
            instrumentSet->units += units;
            //ACTUALIZAMOS LA DISPONIBILIDAD, ALTA, MEDIA, BAJA O NONE
            set_availability (instrument, units);
        } else {
            //SI NO EXISTE, ANTES DE AÑADIRLO VAMOS A VER SI HAY ESPACIO EN EL ALMACEN
            if (m->numStock >= MAX_STOCK)
                printf("ERROR: The stock is full\n");
            else {
                //HAY ESPACIO, AÑADIMOS EL STOCK (EL ID Y LAS UNIDADES)
                //copiamos la direccion de memoria que va a ir alojado el stock, para poder modificarlo
                instrumentSet = &(m->stock[m->numStock]);
                //aqui lo modificamos
                instrumentSet->idInst = id;
                instrumentSet->units = units;
                //ACTUALIZAMOS LA DISPONIBILIDAD
                set_availability(instrument, instrumentSet->units);
                m->numStock++;
            }
        }

    }
}


/*Dada una estructura del tipo tMusicStore,
muestra todos los modelos de instrumentos que se encuentran en el
catálogo de la tienda. Por cada modelo se muestra su código, su
descripción, su precio (con dos decimales) y su disponibilidad.*/

void print_stock (tMusicStore m){

    int i;
    tInstrument ins;
    printf("\n");
    /**/
    for (i = 0; i<m.numInst; i++){
        printf ("%d \t", m.catalogue[i].id);
        printf ("%s \t", m.catalogue[i].description);
        printf ("%f \t", m.catalogue[i].price);

        if (m.catalogue[i].availability == high) printf("high");
        else if (m.catalogue[i].availability == medium) printf("medium");
        else if (m.catalogue[i].availability == low) printf("low");
        else printf("none");
        printf("\n");
    }

    /*for (i=0; i<m.numInst; i++)
  {
       for each instrument in the catalogue 
      ins = m.catalogue[i];

      printf("%d.\t%s\t%.2f\t", ins.id, ins.description, ins.price);
      if (ins.availability == high) printf("high");
      else if (ins.availability == medium) printf("medium");
      else if (ins.availability == low) printf("low");
      else printf("none");
      printf("\n");
  }*/


}

/*  ESTRUCTURA DE TMUSICSOTRE
   typedef struct {
	tInstrument *catalogue; //es un array?????
	int numInst;
	tInstrumentSet stock[MAX_STOCK]; 
	int numStock;
	tOrder *orders;
	int numOrd;
} tMusicStore;
 
  ESTRUCTURA DE UN INSTRUMENTO: con un numero identificador, la descripcion el precio y la disponibilidad
   typedef struct {
	int     id;
	string  description;
	float   price;
	tStatus availability;
} tInstrument;
  * 
  * 
  * typedef struct {
	int idInst;
	int units;
} tInstrumentSet;
 */