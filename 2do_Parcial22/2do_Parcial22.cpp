#include <iostream>
#include "stdio.h"
#include "stdlib.h"

int* toBin2(unsigned char dato, int* p) {
    int resto = 0, bin = 0;
    int j = 8, i;

    for (i = 0; i < 8; i++) {
        p[i] = 0;
    }

    while (dato > 0) {
        resto = dato % 2;
        j -= 1;
        p[j] = resto;
        dato = dato / 2;
    }
    return p;
}

int main()
{
    FILE* f;
    int j = 0, op, p[8] = { 0,0,0,0,0,0,0,0 }, e = 0;
    unsigned char valores[384], reales[64], seg, min, hora;


    f = fopen("myfile.bin", "rb");

    if (f == NULL) {
        printf("\nError al abrir el archivo");
        return 1;
    }

    fread(valores, sizeof(unsigned char), 384, f); //en mi vector "valores" tengo todos los valores del archivo

    if (fclose(f) != 0) {
        printf("\nError al cerrar"); //cierro porque ya se leyo todo el archivo
        return NULL;
    }
    /*//Imprimo para ver todos los valores leidos
        for (int i = 0; i < 384; i++) {

            printf("Registro %d: 0x%02hhx \n", i + 1, valores[i]);

        }

        */
        //Organizo los valores en un vector de [64]
    for (int g = 383; g > 319; g--) {
        reales[e] = valores[g];
        e++;
    }

    /*
       printf("---------------------------------------\n");

       //Imprimo los 64 valores del nuevo vector
       for (int i = 0; i < 64; i++) {

           printf("Registro %d: 0x%02hhx ", i, reales[i]);
           toBin2(reales[i], p);
           for (int k = 0; k < 8; k++) { //imprimo en binario
               printf("%d", p[k]);
           }
           printf("\n");
       }
   */
   /* //Ejemplo mencionado en el parcial para comprobar el funcionamiento de toBin2
   unsigned char ejem = 0x27;
   toBin2(ejem, p);
   for (int k = 0; k < 8; k++) { //imprimo en binario
       printf("%d", p[k]);
   }
   printf("\n");
   */
   //----------------------- Menu -------------------------
    do
    {
        printf("Ingrese la opcion que desee realizar\n");
        printf("1-Mostrar valores (dec, hexa y bin)\n");
        printf("2-Programar alarma\n");
        printf("3-MSB y LSB\n");
        printf("4-Salir\n");
        scanf("%d", &op);

        switch (op) {
        case 1:
            printf("Registro   ||   Decimal    ||   Hexa    ||   Binario");
            printf("\n\n");
            for (int i = 0; i < 14; i++) {

                printf("Registro %02d:     %02d     |     0x%02hhx     |     ", i, reales[i], reales[i]); //imprimo los 14 valores en hexadecimal

                toBin2(reales[i], p);
                for (int k = 0; k < 8; k++) { //imprimo en binario
                    printf("%d", p[k]);
                }
                printf("\n");
            }
            break;
        case 2:
            printf("Ingrese la hora de alarma :");
            scanf("%hhx", &hora);
            printf("\n");
            printf("Ingrese los minutos de la alarma:");
            scanf("%hhx", &min);
            printf("\n");
            printf("Ingrese los segundos de la alarma:");
            scanf("%hhx", &seg);
            printf("\n");

            //Guardo los valores en mi vector RTC
            reales[1] = seg;//0x01
            reales[3] = min;//0x03
            reales[5] = hora;//0x05

            //printf("Anio: %02hhx%02hhx Hora: %02hhx:%02hhx:%02hhx\n", an1, an2, hora, min, seg);
            printf("Registro 1:     %d     |     0x%02hhx     |     ", reales[1], reales[1]);
            toBin2(reales[1], p);
            for (int k = 0; k < 8; k++) { //imprimo en binario
                printf("%d", p[k]);
            }
            printf("\n");
            printf("Registro 3:     %d     |     0x%02hhx     |     ", reales[3], reales[3]);
            toBin2(reales[3], p);
            for (int k = 0; k < 8; k++) { //imprimo en binario
                printf("%d", p[k]);
            }
            printf("\n");
            printf("Registro 5:     %d     |     0x%02hhx     |     ", reales[5], reales[5]);
            toBin2(reales[5], p);
            for (int k = 0; k < 8; k++) { //imprimo en binario
                printf("%d", p[k]);
            }
            printf("\n");

            break;
        case 3:

            for (int i = 0; i < 64; i++) { //recorro los 64 valores

                toBin2(reales[i], p); // paso  a binario todos
                if (p[0] == 1 && p[7] == 1) { //impongo la condicion 
                    printf("Registro %d:     %d     |     0x%02hhx     |     ", i, reales[i], reales[i]);
                    for (int k = 0; k < 8; k++) { //imprimo en binario
                        printf("%d", p[k]);
                    }
                    printf("\n");
                }
            }
            break;
        case 4:
            printf("Saliste del programa\n");
            break;
        default: printf("error\n");
        }
    } while (op != 4);


    return 0;
}

/*--------------------------Preguntas--------------------------*/
/*
1- La senal clock es una onda cuadrada que permite que todos los componentes esten sincronizados.
La senal clock se transmite a traves del "Bus de control".

2- La formula de la frecuencia es: f=1/T siendo T el periodo.

Si la senal tiene una frecuencia de 5GHz (5*10^9 Hz) entonces:

    f=1/T => T=1/f => T=1/(5 GHz) => T=1/(5*10^9 Hz) => [Hz]=[1/seg] => T=2*10^-10 seg

    El periodo T es el tiempo que tarda en repetirse la senal (y la frecuencia es la inversa del periodo).
 */