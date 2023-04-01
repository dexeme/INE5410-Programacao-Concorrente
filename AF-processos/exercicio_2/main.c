#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

//                          (principal)
//                               |
//              +----------------+--------------+
//              |                               |
//           filho_1                         filho_2
//              |                               |
//    +---------+-----------+          +--------+--------+
//    |         |           |          |        |        |
// neto_1_1  neto_1_2  neto_1_3     neto_2_1 neto_2_2 neto_2_3

// O processo principal crie 2 processos filhos.
// Cada um dos processos filhos deve, por sua vez, criar mais três processos.
// Cada processo filho (tanto do processo principal quanto dos criados no passo anterior) 
// deve imprimir "Processo XXX, filho de YYY", onde XXX é o PID do processo em questão e YYY o PID do processo que o criou (use as funções getpid() e getppid() para isso).
// Os processos netos (filhos dos filhos do processo principal) devem, após imprimir esta mensagem, aguardar 5 segundos antes de terminar (use a função sleep() para isso) 
// Os processos que criaram filhos devem aguardar que seus filhos terminem de executar (utilize a função wait()).
// Todos os processos filhos devem imprimir, ao finalizar, "Processo XXX finalizado", onde XXX é o PID do processo em questão. O processo principal deve imprimir 
// "Processo principal XXX finalizado", onde XXX é o PID do processo principal.

// ~~~ printfs  ~~~
//      principal (ao finalizar): "Processo principal %d finalizado\n"
// filhos e netos (ao finalizar): "Processo %d finalizado\n"
//    filhos e netos (ao inciar): "Processo %d, filho de %d\n"

// Obs:
// - netos devem esperar 5 segundos antes de imprmir a mensagem de finalizado (e terminar)
// - pais devem esperar pelos seu descendentes diretos antes de terminar

/*************************************************
 * Dicas:                                        *
 * 1. Leia as intruções antes do main().         *
 * 2. Faça os prints exatamente como solicitado. *
 * 3. Espere o término dos filhos                *
 *************************************************/

int main(int argc, char** argv) {
    for (int i = 0; i < 2; i++) {
        pid_t filho = fork();
        if (filho == 0) { 
            printf("Processo %d, filho de %d\n", getpid(), getppid());
            for (int j = 0; j < 3; j++) {
                pid_t neto = fork();
                if (neto == 0) { // Neto
                    printf("Processo %d, filho de %d\n", getpid(), getppid());
                    sleep(5); // Espera 5 segundos antes de terminar
                    printf("Processo %d finalizado\n", getpid());
                    return 0;
                }
         while(wait(NULL) >= 0);  
           }
            printf("Processo %d finalizado\n", getpid());
            return 0;
        }
    }
    while(wait(NULL) >= 0);    
    printf("Processo principal %d finalizado\n", getpid());
    return 0;
}