#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Constants *********************************************************/

#define MAX_STOCK  100
#define MAX_LINES   10
#define MAX_CHAR   100
#define L1           0
#define L2           5
#define L3          15

/* Types *************************************************************/

typedef enum {false, true} bool;
typedef enum {high, medium, low, none} tStatus;

typedef char string[MAX_CHAR+1];

typedef struct {
    int day;
    int month;
    int year;
} tDate;

typedef struct {
    int     id;
    string  description;
    float   price;
    tStatus availability;
} tInstrument;

typedef struct {
    int idInst;
    int units;
} tInstrumentSet;

typedef struct {
    int            idCustomer;
    tDate 		   date;
    tInstrumentSet line[MAX_LINES];
    int 		   numLines;
}tOrder;

typedef struct {
    tInstrument    *catalogue;
    int            numInst;
    tInstrumentSet stock[MAX_STOCK];
    int            numStock;
    tOrder         *orders;
    int            numOrd;

} tMusicStore;

/* Headers functions**********************************/
void init_music_store (tMusicStore *m);

void new_instrument   (tMusicStore *m, int id, string desc, float price);

void add_stock 		  (tMusicStore *m, int id, int units);

void print_stock 	  (tMusicStore m);

