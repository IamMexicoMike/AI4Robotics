#include <stdio.h>

#define ROWS 4
#define COLS 5

double sensor_success = 0.7;
double move_success = 0.8;

/*Dos dimensiones
 El compilador guarda los arreglos multidimensionales como un solo block de memoria unidimensional.
*/

void sensar_y_actualizar(double *probs, int* estados, int val) {
for(int i=0; i< ROWS*COLS; i++) {
//Si hay un match entre el estado actual y el valor que sensamos
if(*(estados+i)==val) *(probs+i)=*(probs+i)*sensor_success;
//Si no lo hay:
else *(probs+i)=*(probs+i)*(1-sensor_success);
}
//normalizalo
double suma=0;
for(int i=0; i< ROWS*COLS; i++)suma+=*(probs+i);
for(int i=0; i< ROWS*COLS; i++)*(probs+i)/=suma;
}


void mover(double *p, char direccion) {
double move_fail = 1 - move_success;
double copia[ROWS][COLS];
for(int i=0;i<ROWS*COLS; i++)*((double*)copia +i)=(*(p+i));
/*es una marranada pero facilita el acceso*/

double p2[ROWS][COLS];

switch(direccion) {

case 'r': //DERECHA

for(int i=0; i < ROWS; i++)
for(int j=0; j<COLS; j++) {
        if(j==0) p2[i][j] = move_success*copia[i][COLS-1]+move_fail*copia[i][j];
        else p2[i][j] = move_success*copia[i][j-1]+move_fail*copia[i][j];
        }
    break;

case 'l': //IZQ

for(int i=0; i < ROWS; i++)
for(int j=0; j<COLS; j++) {
        if(j==COLS-1) p2[i][j] = move_success*copia[i][0]+move_fail*copia[i][j];
        else p2[i][j] = move_success*copia[i][j+1]+move_fail*copia[i][j];
}
break;

case 'u': //ARRIBA

for(int i=0; i < ROWS; i++)
for(int j=0; j<COLS; j++) {
        if(i==ROWS-1) p2[i][j] = move_success*copia[0][j]+move_fail*copia[i][j];
        else p2[i][j] = move_success*copia[i+1][j]+move_fail*copia[i][j];
}
break;

case 'd': //ABAJO

for(int i=0; i < ROWS; i++)
for(int j=0; j<COLS; j++) {
        if(i==0) p2[i][j] = move_success*copia[ROWS-1][j]+move_fail*copia[i][j];
        else p2[i][j] = move_success*copia[i-1][j]+move_fail*copia[i][j];
}
break;
default: printf("\ndefault\n");
}

for(int i=0;i<ROWS*COLS; i++) *(p+i)=(*((double*)p2+i));
}

int main(){

double p[ROWS][COLS];
for(int i=0; i < ROWS*COLS; i++) *((double*)p+i)=(1/(double)(ROWS*COLS));
for(int i=0; i<ROWS; i++) {
        printf("\n");
    for(int j=0; j<COLS;j++)
    printf("%lf ,",p[i][j]);
}
int estados[ROWS][COLS] = {{0,1,1,0,0},{0,0,1,0,0},{0,0,1,1,0},{0,0,0,0,0}};

//actualizar con 1 (porque sensaste 1) [funciona correctamente]
//Recuerda que p es exactamente lo mismo que &p[0]

/*---------actualizar-------*/
printf("\n\nSensar 1 y actualizar:\n");
sensar_y_actualizar((double*)p,(int*)estados,1);

/*for(int i=0; i<ROWS; i++) {
        printf("\n");
    for(int j=0; j<COLS;j++)
    printf("%lf ,",p[i][j]);
}*/
/*-----------mover----------*/
printf("\n\nMover:\n");
mover(&p[0][0], 'r');
sensar_y_actualizar((double*)p,(int*)estados,1);
mover(&p[0][0], 'd');
sensar_y_actualizar((double*)p,(int*)estados,1);
mover(&p[0][0], 'd');
sensar_y_actualizar((double*)p,(int*)estados,1);
mover(&p[0][0], 'r');
sensar_y_actualizar((double*)p,(int*)estados,1);

for(int i=0; i<ROWS; i++) {
        printf("\n");
    for(int j=0; j<COLS;j++)
    printf("%lf ,",p[i][j]);
}

return 0;
}
