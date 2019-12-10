#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h> // Usar kbhit
#include <unistd.h> // Usar sleep.
#include <time.h> // Gerar aleatoriedade.
#define tlin 12//Padr�o 9.
#define tcol 12//Padr�o 9.
//Movimento da cobra.
int main()
{
    //Inicializa��o.
    int l, c, lins = tlin/2, cols = tcol/2 - 2;//Linha/Coluna da snake. Posi��o linha/coluna iniciais.
    int linm = tlin/2, colm = tcol/2 + 2;//Posi��o da ma��.
    int tcau = 0, linc = linm, colc = colm;//Tamanho da cauda, linha/coluna da cauda.
    int tdel = (tlin - 2)*(tcol - 2), ppd = tdel, pld = tdel, flagD = 0;//posi��o de preenchimento/leitura de delay, flag de delay.
    char delay[tdel];//delay do movimento da cauda.
    char matriz[tlin][tcol];
    int ocp[tdel - 1][2];
    int i;//Contador.
    delay[0] = 'a';
    srand(time(NULL));
    int vel = 70;

    /*printf("Digite a velocidade da cobra. Recomendado: 60.\n30 - Muito r�pido\n500 - Lento\n");
    scanf("%d", &vel);
    while(vel < 30 || vel > 500)
    {
        system("cls");
        printf("Digite a velocidade da cobra. Recomendado: 60\n30 - Muito r�pido\n500 - Muito lento\n");
        scanf("%d", &vel);
    }
    system("cls");*/

    //Alterar dificuldade.
    char dif;
    printf("1 - Facil\n2 - Medio\n3 - Dificil\n\n");
    dif = getch();
    printf("%c\n", dif);
    Sleep(50);
    while(dif != '1' && dif != '2' && dif != '3')
    {
        system("cls");
        printf("1 - Facil\n2 - Medio\n3 - Dificil\n\n");
        dif = getch();
        printf("%c\n", dif);
        Sleep(50);
    }
    if(dif == '1')
        vel = 300;
    if(dif == '2')
        vel = 150;
    if(dif == '3')
        vel = 60;
    Sleep(500);
    system("cls");

    for(l = 0; l < tlin; l++)//Preencher matriz inicial.
    {
        for(c = 0; c < tcol; c++)
        {
            if(c == 0 || c == tcol - 1 || l == 0 || l == tlin - 1)
                matriz[l][c] = 'X';
            else
                matriz[l][c] = ' ';
        }
    }
    matriz[lins][cols] = '>';
    matriz[linm][colm] = 'M';
    printf("SNAKE V.1.0\n\n'q' - SAIR\n'p' - PAUSE\n\n");
    for(l = 0; l < tlin; l++)//Printar matriz (inicial).
    {
        for(c = 0; c < tcol; c++)
        {
            printf("%c ", matriz[l][c]);
        }
        printf("\n");
    }
    printf("Pontos: %d\n", tcau);
    //Fim da inicializa��o.
    char seta = getch();
    while(seta != -32)
    {
        if(seta == 'q')
        {
            printf("\nSAIU\n");
            Sleep(1000);
            getch();
            return 0;
        }
        seta = getch();
    }
    char sent = getch();
    char aux;
    //Fim da primeira instru��o.
    while(1 == 1)
    {
        if(kbhit())
        {
            seta = getch();
            if(seta == -32)
            {
                aux = getch();
                if(aux - sent != 2 && aux - sent != -2 && aux - sent != 8 && aux - sent != -8)
                    sent = aux;
            }
        }
        //Sentido do movimento recebido.
        if(tcau == 0)
            matriz[lins][cols] = ' ';
        if(sent == 'H')
            lins--;
        if(sent == 'M')
            cols++;
        if(sent == 'P')
            lins++;
        if(sent == 'K')
            cols--;
        //Cabe�a movida.
        if(tcau == 1 && matriz[lins][cols] == 'C')
        {
            printf("\nGAME OVER\n");
            Sleep(1000);
            getch();
            return 0;
        }
        //Mover a cauda.
        if(tcau > 0)
        {
            if(flagD == 0)
            {
                matriz[linc][colc] = ' ';
                if(delay[pld%tdel] == 'H')
                    linc--;
                if(delay[pld%tdel] == 'M')
                    colc++;
                if(delay[pld%tdel] == 'P')
                    linc++;
                if(delay[pld%tdel] == 'K')
                    colc--;
                pld++;
            }
            else
                flagD--;
            delay[ppd%tdel] = sent;
            ppd++;
            matriz[linc][colc] = 'C';
        }
        //Cauda movida.
        if(lins == 0 || lins == tlin - 1 || cols == 0 || cols == tcol - 1 || matriz[lins][cols] == 'O' || matriz[lins][cols] == 'P' || matriz[lins][cols] == 'C')
        {
            printf("\nGAME OVER\n");
            Sleep(1000);
            getch();
            return 0;
        }
        //Comeu a ma��.
        if(lins == linm && cols == colm)
        {
            //Preencher ocupado(ocp).
            i = 0;
            for(l = 1; l < tlin - 2; l++)
            {
                for(c = 1; c < tcol - 2; c++)
                {
                    if(matriz[l][c] == ' ')
                    {
                        ocp[i][0] = l;
                        ocp[i][1] = c;
                        i++;
                    }

                }
            }
            tcau++;
            flagD++;
            i = rand()%i;
            linm = ocp[i][0];
            colm = ocp[i][1];
        }
        //Ma�� atualizada.
        //Preencher matriz.
        if(sent == 'H')
            matriz[lins][cols] = '^';
        if(sent == 'M')
            matriz[lins][cols] = '>';
        if(sent == 'P')
            matriz[lins][cols] = 'V';
        if(sent == 'K')
            matriz[lins][cols] = '<';
        /*while(matriz[linm][colm] == 'O' || matriz[linm][colm] == 'X' || matriz[linm][colm] == 'C' || matriz[linm][colm] == '^' || matriz[linm][colm] == '>' || matriz[linm][colm] == 'V' || matriz[linm][colm] == '<')
        {
            linm = (rand()% (tlin - 2)) + 1;
            srand(time(NULL));
            colm = (rand()% (tcol - 2)) + 1;
        }*/
        matriz[linm][colm] = 'M';
        //Printar a matriz.
        Sleep(vel);//Padr�o 50.
        system("cls");
        printf("SNAKE V.1.0\n\n'q' - SAIR\n'p' - PAUSE\n\n");
        for(l = 0; l < tlin; l++)
        {
            for(c = 0; c < tcol; c++)
            {
                printf("%c ", matriz[l][c]);
            }
            printf("\n");
        }
        matriz[lins][cols] = 'O';
        printf("Pontos: %d\n", tcau);
        if(kbhit())
        {
            seta = getch();
            if(seta == -32)
            {
                aux = getch();
                if(aux - sent != 2 && aux - sent != -2 && aux - sent != 8 && aux - sent != -8)
                    sent = aux;
            }
            if(seta == 'q')
            {
                printf("\nSAIU\n");
                Sleep(1000);
                getch();
                return 0;
            }
            if(seta == 'p')
            {
                printf("\nPAUSE\n");
                getch();
            }
        }
    }
    return 0;
}
//Obs: Impossibilitar volta. Usar file para salvar recorde. Implementar reiniciar. Movimento com wdsa. Trocar corpo para 'l' e '-'. Anim��o para comer a ma��.
//Tempo, recorde, anim�ao quando come a ma��. Mudar corpo para 'l' e '-' ou '='.
//Programa fecha derrepente.
//Implementar reiniciar.
/*
Aumentar efici�ncia:
    Printar a matriz at� onde o 'O' est�.
    Usar ponteiro e malloc.
*/
/*
� H cima.
� M direita.
� P esquerda.
� K baixo.
*/
