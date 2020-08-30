#include <stdio.h>
#include <stdlib.h>

#define SUBMARINO     'S'
#define DESTROYER     'D'
#define CRUZADOR      'C'
#define PORTA_AVIAO   'P'
#define HIDRO_AVIAO   'H'
#define BARCO         'B'
#define EXPLOSAO      '*'
#define AGUA          'a'
#define RASTRO        '.'
#define ESQUERDA      'e'
#define BAIXO         'b'
#define DIREITA       'd'
#define CIMA          'c'

#define MAXLINHAS     20
#define MAXCOLUNAS    20
#define MAXNOME       64
#define TRUE           1
#define FALSE          0

int coluna_inicial_barco(char mapa[MAXLINHAS][MAXCOLUNAS])
{
  int j;
  for (j = 1; j <= MAXCOLUNAS; j++)
  {
    if (mapa [1][j] == BARCO)
    {
      return j;
    }
  }
  printf ("ERRO NA POSICAO INICAL DO BARCO");
  return 0;
}

void escreva_mapa_tela(int no_linhas, int no_colunas, char mapa[MAXLINHAS][MAXCOLUNAS])
{
  int i, j, cont_col;

  printf ("\nMAPA DA BATALHA\n\n");
  printf (" ");

  for (cont_col = 1; cont_col <= no_colunas; cont_col++)
  {
      /* números maiores que 10 ocupam mais espaço na impressão */
      if (cont_col < 10) printf ("   %d", cont_col);
      else printf ("  %d", cont_col);
  }
  printf ("\n  ");

  for (cont_col = 1; cont_col <= no_colunas; cont_col++) printf ("+---");
  printf ("+\n");

  for ( i = 1; i <= no_linhas; i++)
  {
    /* números maiores que 10 ocupam mais espaço na impressão */
    if (i < 10) printf ("%d |", i);
    else printf ("%d|", i);
    for (j = 1; j <= no_colunas; j++)
    {
      if (mapa [i][j] == BARCO || mapa [i][j] == RASTRO || mapa [i][j] == AGUA || mapa [i][j] == EXPLOSAO || mapa [i][j] == 's' ||
          mapa [i][j] == 'd' || mapa [i][j] == 'c' || mapa [i][j] == 'p' || mapa [i][j] == 'h' || mapa[i][j] == 'X') printf ( " %c |" , mapa [i][j]);
      else printf ("   |");
    }
  printf ("\n  ");

  for (cont_col = 1; cont_col <= no_colunas; cont_col++) printf ("+---");

  printf ("+\n");
  }
}

int acertou_embarcacao(char ch)
{
   if (ch == SUBMARINO || ch == DESTROYER || ch == CRUZADOR || ch == PORTA_AVIAO || ch == HIDRO_AVIAO) return TRUE;
   else return FALSE;
}

void afunda_embarcacao(int linha, int coluna, char mapa[MAXLINHAS][MAXCOLUNAS])
{
   int i, j, i_aux = 0, j_aux = 0; /* variáveis auxiliares */
   char ch; /* tipo de embarcação */

   ch = mapa[linha][coluna];
   mapa[linha][coluna] = '0'; /* evita com que o laço considere também a posição sendo analisada */

   if (ch != HIDRO_AVIAO) /* apenas embarcações lineares */
   {
     for (i = linha - 1; i <= linha + 1; i++)
     {
        for (j = coluna - 1; j <= coluna + 1; j++)
        {
            if (mapa[i][j] == ch)
            {
               i_aux = i;
               j_aux = j;
            }
         }
     }

     if (i_aux == linha) /* quando a embarcação está na vertical */
     {
        for (j_aux = coluna + 1; mapa[linha][j_aux] == ch; j_aux++) mapa[linha][j_aux] = ch + 32;
        for (j_aux = coluna - 1; mapa[linha][j_aux] == ch; j_aux--) mapa[linha][j_aux] = ch + 32;
     }

     if (j_aux == coluna) /* quando a embarcação está na horizontal */
     {
        for (i_aux = linha + 1; mapa[i_aux][coluna] == ch; i_aux++) mapa[i_aux][coluna] = ch + 32;
        for (i_aux = linha - 1; mapa[i_aux][coluna] == ch; i_aux--) mapa[i_aux][coluna] = ch + 32;
     }

     else /* quando a embarcação está na diagonal */
     {
        for (i_aux = linha + 1, j_aux = coluna + 1 ; mapa[i_aux][j_aux] == ch; i_aux++, j_aux++) mapa[i_aux][j_aux] = ch + 32;
        for (i_aux = linha + 1, j_aux = coluna - 1 ; mapa[i_aux][j_aux] == ch; i_aux++, j_aux--) mapa[i_aux][j_aux] = ch + 32;
        for (i_aux = linha - 1, j_aux = coluna + 1 ; mapa[i_aux][j_aux] == ch; i_aux--, j_aux++) mapa[i_aux][j_aux] = ch + 32;
        for (i_aux = linha - 1, j_aux = coluna - 1 ; mapa[i_aux][j_aux] == ch; i_aux--, j_aux--) mapa[i_aux][j_aux] = ch + 32;
     }
   }

   else /* no caso do hidro-avião */
   {
      if (mapa[linha + 1][coluna + 1] == ch)
      {
         mapa[linha + 1][coluna + 1] = ch + 32;
         if (mapa[linha - 1][coluna + 1] == ch) mapa[linha - 1][coluna + 1] = ch + 32;
         if (mapa[linha + 1][coluna - 1] == ch) mapa[linha + 1][coluna - 1] = ch + 32;
         if (mapa[linha + 2][coluna] == ch) mapa[linha + 2][coluna] = ch + 32;
         else mapa[linha][coluna + 2] = ch + 32;
      }

      if (mapa[linha + 1][coluna - 1] == ch)
      {
         mapa[linha + 1][coluna - 1] = ch + 32;
         if (mapa[linha - 1][coluna - 1] == ch) mapa[linha - 1][coluna - 1] = ch + 32;
         if (mapa[linha + 2][coluna] == ch) mapa[linha + 2][coluna] = ch + 32;
         else mapa[linha][coluna - 2] = ch + 32;
      }

      if (mapa[linha - 1][coluna - 1] == ch)
      {
         mapa[linha - 1][coluna - 1] = ch + 32;
         if (mapa[linha - 2][coluna] == ch) mapa[linha - 2][coluna] = ch + 32;
         else mapa [linha - 1][coluna + 1] = ch + 32;
      }

      else  mapa[linha - 1][coluna] = mapa[linha][coluna + 2] = ch + 32;
   }
   mapa[linha][coluna] = ch;
}

void inicializa_gerador(int semente)
{
  srand(semente);
}

int no_aleatorio(int n)
{
  return  1 + (rand()/(RAND_MAX+1.0))*n;
}

void sorteie_posicao(int no_linhas, int no_colunas, int *linha, int *coluna)
{
  *linha  = no_aleatorio(no_linhas);
  *coluna = no_aleatorio(no_colunas);
}

void leia_ate_barra_n(FILE *arq)
{
  char ch;

  fscanf(arq, "%c", &ch);
  while (ch != '\n')
    {
      fscanf(arq, "%c", &ch);
    }
}

void leia_mapa(int *no_linhas, int *no_colunas, char mapa[MAXLINHAS][MAXCOLUNAS], int *c_barco)
{
  FILE *arq;
  char nome_arquivo[MAXNOME];
  int no_l, no_c, c_bar, i, j, codigo;

  printf("MSG do QG: preparando para leitura do mapa.\n");

  printf("MSG do QG: forneca nome do arquivo que contem o mapa: ");
  scanf("%s", nome_arquivo);

  arq = fopen(nome_arquivo, "r");
  if (arq == NULL)
    {
      printf("MSG do QG: erro na abertura do arquivo %s.\n", nome_arquivo);
      printf("MSG do QG: MISSAO ABORTADA!\n\n");
      system("pause");
      exit(-1);
    }
  printf("MSG do QG: arquivo %s foi encontrado.\n", nome_arquivo);

  printf("MSG do QG: mapa esta sendo lido do arquivo %s.\n", nome_arquivo);
  fscanf(arq, "%d %d %d", &no_l, &no_c, &codigo);
  leia_ate_barra_n(arq);
  printf("MSG do QG: mapa tem %d linhas e %d colunas.\n", no_l, no_c);
  printf("MSG do QG: codigo de ataque: %d\n", codigo);


  inicializa_gerador(codigo);


  for (i = 1; i <= no_l; i++)
    {
      for (j = 1; j <= no_c; j++)
        {
          fscanf(arq, "%c", &mapa[i][j]);
        }
      leia_ate_barra_n(arq);
    }


  c_bar = coluna_inicial_barco(mapa);

  printf("MSG do QG: posicao inicial do barco e' (1,%d).\n", c_bar);

  fclose(arq);
  printf("MSG do QG: mapa lido com sucesso.\n");

  *no_linhas  = no_l;
  *no_colunas = no_c;
  *c_barco    = c_bar;
}

void escreva_mapa_arquivo(int no_linhas, int no_colunas, char mapa[MAXLINHAS][MAXCOLUNAS])
{
  FILE *arq;
  int i, j, cont_col;

  arq = fopen("secreto.dat","w");
  if (arq == NULL)
    {
      printf("MSG do QG: "
             "erro na criacao do arquivo secreto.dat.\n");
      printf("MSG do QG: MISSAO ABORTADA!\n\n");
      exit(-1);
    }

  fprintf(arq, "    MAPA SECRETO DA BATALHA\n\n");
  fprintf(arq, "    no. linhas = %d     no. colunas = %d\n\n", no_linhas,  no_colunas);

  fprintf (arq, "    ");

  for (cont_col = 1; cont_col <= no_colunas; cont_col++) fprintf (arq, "%d   ", cont_col);
  fprintf (arq, "\n  ");

  for (cont_col = 1; cont_col <= no_colunas; cont_col++) fprintf (arq, "+---");
  fprintf (arq, "+\n");

  for (i = 1; i <= no_linhas; i++)
  {
    fprintf (arq, "%d |", i);

    for ( j = 1; j <= no_colunas; j++) fprintf (arq, " %c |" , mapa [i][j]);
    fprintf (arq, "\n  ");

    for (cont_col = 1; cont_col <= no_colunas; cont_col++) fprintf (arq, "+---");
    fprintf (arq, "+\n");
  }

  fprintf(arq, "\n\nFIM DO ARQUIVO.");
  fclose(arq);
}

int main()
{
  int m_linhas, m_colunas, /* número de linhas e colunas do mapa */
  i = 1, j, /* variáveis auxiliares */
  i_atual, j_atual, /* coordenadas atuais do barco */
  i_exp, j_exp, /* coordenadas dos locais do bombardeio */
  cont, /* contador auxiliar */
  encalhou = 0, /* verifica se o barco está encalhado */
  atingiu = 0; /* verifica se o barco foi bombardeado */

  char m[MAXLINHAS][MAXCOLUNAS], /* matriz do mapa */
  mov; /* movimento escolhido para o barco */

  printf ("MSG do QG: prepare-se para a missao.\n");

  leia_mapa(&m_linhas, &m_colunas, m, &j);

  i_atual = i;
  j_atual = j;

  printf ("MSG do QG: segue mapa da batalha.\n");

  escreva_mapa_tela(m_linhas, m_colunas, m);

  printf ("MSG do QG: preparando artilharia para lhe dar cobertura.\n");
  printf ("MSG do QG: cuidado com fogo amigo...\n");
  printf ("MSG do QG: preparados para iniciar bombardeio da frota inimiga.\n");
  printf ("MSG do QG: permissao para iniciar a missao concedida.\n");
  printf ("MSG do QG: a sua posicao e' (%d, %d).\n", i, j);
  printf ("MSG do QG: Boa sorte!\n\n");

  while (i_atual < m_linhas && encalhou < 3 && atingiu == 0)
  {
    printf ("MSG do QG: escolha movimento ('e'=esquerda,'b'=baixo,'d'=direita,'c'=cima): ");
    scanf (" %c", &mov);

    if (mov == ESQUERDA)
    {
      printf ("MSG do QG: direcao escolhida: %c.\n", mov);
      if (1 <= j - 1 && m[i][j - 1] != SUBMARINO && m[i][j - 1] != DESTROYER &&
          m[i][j - 1] != CRUZADOR && m[i][j - 1] != PORTA_AVIAO && m[i][j - 1] != HIDRO_AVIAO) j_atual = j - 1;
      if (m[i][j - 1] == SUBMARINO || m[i][j - 1] == DESTROYER || m[i][j - 1] == CRUZADOR ||
          m[i][j - 1] == PORTA_AVIAO || m[i][j - 1] == HIDRO_AVIAO) printf ("MSG do QG: ha uma embarcacao em (%d, %d).\n", i, j - 1);
      else printf ("MSG do QG: tentou sumir do mapa pela coluna -1.\n");
    }
    if (mov == BAIXO)
    {
      printf ("MSG do QG: direcao escolhida: %c.\n", mov);
      if (m[i + 1][j] != SUBMARINO && m[i + 1][j] != DESTROYER &&
          m[i + 1][j] != CRUZADOR && m[i + 1][j] != PORTA_AVIAO && m[i + 1][j] != HIDRO_AVIAO) i_atual = i + 1;
      else printf ("MSG do QG: ha uma embarcacao em (%d, %d).\n", i + 1, j);
    }
    if (mov == DIREITA)
    {
      printf ("MSG do QG: direcao escolhida: %c.\n", mov);
      if (j + 1 <= m_colunas && m[i][j + 1] != SUBMARINO && m[i][j + 1] != DESTROYER &&
          m[i][j + 1] != CRUZADOR && m[i][j + 1] != PORTA_AVIAO && m[i][j + 1] != HIDRO_AVIAO) j_atual = j + 1;
      if (m[i][j + 1] == SUBMARINO || m[i][j + 1] == DESTROYER || m[i][j + 1] == CRUZADOR ||
          m[i][j + 1] == PORTA_AVIAO || m[i][j + 1] == HIDRO_AVIAO) printf ("MSG do QG: ha uma embarcacao em (%d, %d).\n", i, j + 1);
      else printf ("MSG do QG: tentou sumir do mapa pela coluna %d.\n", m_colunas + 1);
    }
    if (mov == CIMA)
    {
      printf ("MSG do QG: direcao escolhida: %c.\n", mov);
      if (1 <= i - 1 && m[i - 1][j] != SUBMARINO && m[i - 1][j] != DESTROYER &&
          m[i - 1][j] != CRUZADOR && m[i - 1][j] != PORTA_AVIAO && m[i][j] != HIDRO_AVIAO) i_atual = i - 1;
      if (m[i - 1][j] == SUBMARINO || m[i - 1][j] == DESTROYER || m[i - 1][j] == CRUZADOR ||
          m[i - 1][j] == PORTA_AVIAO || m[i - 1][j] == HIDRO_AVIAO) printf ("MSG do QG: ha uma embarcacao em (%d, %d).\n", i - 1, j);
      else printf ("MSG do QG: tentou sumir do mapa pela linha -1.\n");
    }
    m[i][j] = RASTRO;
    m[i_atual][j_atual] = BARCO;

    if (i == i_atual && j == j_atual)
    {
       printf ("MSG do QG: ficou parado em (%d, %d).\n", i, j);
       encalhou ++;
    }

    else
    {
       printf ("MSG do QG: moveu-se para (%d, %d).\n", i_atual, j_atual);
       encalhou = 0;
    }

    i = i_atual;
    j = j_atual;

    for (cont = 3; cont > 0; cont --) /* laço do bombardeio */
    {
      sorteie_posicao(m_linhas, m_colunas, &i_exp, &j_exp);

      acertou_embarcacao(m[i_exp][j_exp]);

      if (acertou_embarcacao(m[i_exp][j_exp]) == FALSE)
      {
        if (m[i_exp][j_exp] == ' ' || m[i_exp][j_exp] == AGUA || m[i_exp][j_exp] == EXPLOSAO || m[i_exp][j_exp] == 's' ||
            m[i_exp][j_exp] == 'd' || m[i_exp][j_exp] == 'c' || m[i_exp][j_exp] == 'p' || m[i_exp][j_exp] == 'h')
            /* bomba na água ou em embarcações afundadas */
        {
           m[i_exp][j_exp] = AGUA;
           printf ("MSG do QG: posicao (%d, %d), CHUA... AGUA\n", i_exp, j_exp);
        }

        if (m[i_exp][j_exp] == BARCO) /* bomba no barco */
        {
           m[i_exp][j_exp] = 'X';
           atingiu = 1;
           printf ("MSG do QG: posicao (%d, %d), BUUMM\n", i_exp, j_exp);
           printf ("MSG do QG: posicao (%d, %d), opsssss... voce foi atingido\n", i_exp, j_exp);
        }
      }

      else /* bomba em embarcação ainda não afundada */
      {
         afunda_embarcacao(i_exp, j_exp, m);
         printf ("MSG do QG: posicao (%d, %d), BUUMM\n", i_exp, j_exp);
         if (m[i_exp][j_exp] == SUBMARINO) printf ("MSG do QG: posicao (%d, %d), submarino atingido.\n", i_exp, j_exp);
         if (m[i_exp][j_exp] == DESTROYER) printf ("MSG do QG: posicao (%d, %d), destroyer atingido.\n", i_exp, j_exp);
         if (m[i_exp][j_exp] == CRUZADOR) printf ("MSG do QG: posicao (%d, %d), cruzador atingido.\n", i_exp, j_exp);
         if (m[i_exp][j_exp] == PORTA_AVIAO) printf ("MSG do QG: posicao (%d, %d), porta avioes atingido.\n", i_exp, j_exp);
         if (m[i_exp][j_exp] == HIDRO_AVIAO) printf ("MSG do QG: posicao (%d, %d), hidro-aviao atingido.\n", i_exp, j_exp);
         m[i_exp][j_exp] = EXPLOSAO;

      }
    }
    printf ("MSG do QG: Segue o mapa da batalha.\n");
    escreva_mapa_tela(m_linhas, m_colunas, m);
  }
  escreva_mapa_arquivo (m_linhas, m_colunas, m);

  if (encalhou == 3)
  {
     printf ("MSG do QG: infelizmente voce ficou encalhado em (%d, %d).\n", i_atual, j_atual);
     printf ("MSG do QG: VOCE FRACASSOU EM SUA MISSAO... FICA PARA A PROXIMA.\n");
  }

  if (atingiu == 1)
  {
      if (j_atual == m_colunas) printf ("MSG do QG: infelizmente voce morreu na praia... em (%d, %d).\n", i_atual, j_atual);
      else printf ("MSG do QG: infelizmente voce foi destruido em (%d, %d).\n", i_atual, j_atual);
      printf ("MSG do QG: VOCE FRACASSOU EM SUA MISSAO... FICA PARA A PROXIMA.\n");
  }

  if (encalhou < 3 && atingiu == 0)
  {
      printf ("MSG do QG: PARABENS!!! Voce chegou a (%d, %d).\n", i_atual, j_atual);
      printf ("MSG do QG: VOCE COMPLETOU A SUA MISSAO COM PICARDIA.\n");
  }
  return 0;
}
