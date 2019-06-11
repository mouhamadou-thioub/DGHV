#include <math.h>
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MR_REP 20 /* Une constante qui est utilisée pour la génération du nombre premier*/
void gen_alea_intervalle(mpz_t alea,int n,gmp_randstate_t state);
void gen_premier_alea_intervalle(mpz_t prime,int n,gmp_randstate_t state);
void chiffrement_DGHV(mpz_t chiffre,mpz_t m,int taille_p, mpz_t p,int taille_q,int taille_r);
void dechiffrer_DGHV(mpz_t chiffre,mpz_t key);		/*procedure pour dechiffrer*/
void FA(mpz_t sum,mpz_t b1,mpz_t b2,mpz_t cin);		/*procedure pour FUll Adder*/
void somxor(mpz_t s,mpz_t c1,mpz_t c2);			/*procedure XOR*/
void somor(mpz_t s,mpz_t c1,mpz_t c2);			/*procedure OR*/
void prodand(mpz_t p,mpz_t b1,mpz_t b2);		/*procedure AND*/
void HA(mpz_t sum,mpz_t b1,mpz_t b2);			/*procedure Half Adder*/
void carryout(mpz_t car,mpz_t b1,mpz_t b2,mpz_t cin);	/*procedure Retenue */
void somme_bit(mpz_t s,mpz_t c1,mpz_t c2);		/*procedure somme bit*/
int somxor1(int c1,int c2);				/*Fonction XOR*/
int somor1(int c1,int c2);				/*Fonction OR*/
int main(int argc,char* argv[]){

		  /* DEclaration des variables   */
		    int time = 0;
		    int opc;
		    int n,taille_q,taille_r;
		    gmp_randstate_t state;
		    gmp_randinit_default (state);
		    mpz_t prime,m,c,c1,c2,s,p;
		    mpz_t chiffreadd,chiffremult,chiffre1,chiffre2,cin;


  		   /*	initialisation	*/
		    mpz_init(chiffreadd);
		    mpz_init(chiffremult);
		    mpz_init(chiffre1);
		    mpz_init(chiffre2);
		    mpz_init(prime);
		    mpz_init(m);
		    mpz_init(c1);
		    mpz_init(c);
		    mpz_init(c2);
		    mpz_init(s);
		    mpz_init(p);mpz_init(cin);


while (opc !=5){


	printf("                   MENU OPTION\n");
	printf("           ------------------------------\n");
	printf("           : 1. CHIFFREMENT HOMO-Simple :\n");
	printf("           : 2. FULL_ADDER 4-Bits       :\n");
	printf("           : 3. CHIFFREMENT             :\n");
	printf("           : 4. DECHIFFREMENT           :\n");
	printf("           : 5. QUITTER                 :\n");
	printf("           :                            :\n");
	printf("           :-----------------------------\n");

	printf("\nChoisir une option:");
	scanf("%d",&opc);


	if (opc==1)

		{
		    // Chiffrement Homomorphe Simple
		    // demander messages en clair, taille parametres
 		    printf("\n");
                    printf("           -----------------------------------------\n");
		    printf("           :            Entrer Parametres          :\n");
 		    printf("           -----------------------------------------\n");
 		    printf("\n");

		    printf("\nEntrer la taille de la clé secrete: ");
		    scanf("%d",&n);

		    printf("\nEntrer la taille de q (veuillez respecter les normes de la taille): ");
		    scanf("%d",&taille_q);

		    printf("\nEntrer la taille du bruit r (rappel:r<p/4): ");
		    scanf("%d",&taille_r);


		    // Generation des clés
 		    printf("\n");
                    printf("           ----------------------------------------\n");
		    printf("           :           Generation des clés        :\n");
 		    printf("           ----------------------------------------\n");
 		    printf("\n");

		    gen_premier_alea_intervalle(prime,n,state);/*on genere ici une clé qui est un nombre premier*/

		    gmp_printf ("votre clé  est p=%Zd\n",prime );/*on affiche la clé*/

		    // Demander messages en clair

 		    printf("\n");
                    printf("           ----------------------------------------\n");
		    printf("           :            Messages en Clair         :\n");
 		    printf("           ----------------------------------------\n");
 		    printf("\n");
		    printf("\nMessage en clair(bit) M1: ");
		    gmp_scanf("%Zd",&c1);
		    printf("\nMessage en clair(bit) M2: ");
		    gmp_scanf("%Zd",&c2);
		    printf("\ncin (La retenue initiale = 0): ");
		    gmp_scanf("%Zd",&cin);

		    // Operation sur des messages en clair

 		    printf("\n");
                    printf("           ------------------------------------------\n");
		    printf("           :   Operation sur des Messages en Clair  :\n");
 		    printf("           ------------------------------------------\n");
 		    printf("\n");

		    printf("SOMME ");
 		    printf("\n------\n");
		    FA(s,c1,c2,cin);			/* Appel de la fonction Full Adder*/
		    carryout(c,c1,c2,cin);
		    gmp_printf ("%Zd + %Zd = %Zd    \n",c1,c2,s);
 		    printf("\n");


		    printf("PRODUIT\n");
 		    printf("-------\n");
		    mpz_mul(p,c1,c2);
		    gmp_printf ("%Zd * %Zd = %Zd\n",c1,c2,p);


		    // chiffrer messages
 		    printf("\n");
                    printf("           ------------------------------------------\n");
		    printf("           :            CHIFFREMENT DGHV            :\n");
 		    printf("           ------------------------------------------\n");
 		    printf("\n");
		    chiffrement_DGHV(chiffre1,c1,n,prime,taille_q,taille_r );/*fonction chiffrement_DGHV pour chiffrer le message*/
		    chiffrement_DGHV(chiffre2,c2,n,prime,taille_q,taille_r );/*fonction chiffrement_DGHV pour chiffrer le message*/

 		    gmp_printf ("C1  : %Zd\n",chiffre1);
 		    gmp_printf ("C2  : %Zd\n",chiffre2);

               	    // Addition homomorphique
		    printf("\n");
		    printf("\n******************************************************************************");
		    printf("\nAddition des chiffrés\n");
   		    printf("----------------------\n");
 		    printf("\n");

		    if ( (taille_r+1)<(n-1)){

			// donner le resultat chiffré
			printf("C1 + C2\n");
   		    	printf("-------\n");
    			mpz_add(chiffreadd,chiffre1,chiffre2);
			gmp_printf ("%Zd + %Zd = %Zd\n",chiffre1,chiffre2,chiffreadd);

			// verification: dechiffrer le resultat
		    	printf("\nDechiffrement de la somme\n");
   		    	printf("-------------------------\n");
 			printf("\n");
			//gmp_printf (" Dechiffrement_DGHV( %Zd)=",chiffreadd);
			dechiffrer_DGHV(chiffreadd,prime);


		    	// comparer avec addition en clair
			printf("\n");
		    	printf("comparer avec addition en clair\n");
   		    	printf("-------------------------------\n");
 			printf("\n");
			gmp_printf (" %Zd + %Zd = %Zd   \n",c1,c2,s);}

		    else

			{  printf("\n"); printf("\nla propriété homomorphe est perdue pour laddition\n");}


		   // Multiplication homomorphique
		    printf("\n********************************************************************************");
		    printf("\n");
		    printf("Multiplication des chiffrés\n");
   		    printf("---------------------------\n");

		    if ( (2*taille_r)<(n-1)){

			// donner le resultat chiffré
 			printf("\n");
			printf("C1 * C2\n");
   		    	printf("-------\n");
 			printf("\n");
    			mpz_mul(chiffremult,chiffre1,chiffre2);
			gmp_printf ("%Zd * %Zd = %Zd\n",chiffre1,chiffre2,chiffremult);

			// verification: dechiffrer le resultat
 			printf("\n");
			printf("Dechiffrement du produit\n");
   		    	printf("------------------------\n");
 			printf("\n");
			//gmp_printf (" Dechiffrement_DGHV( %Zd)=",chiffremult);
			dechiffrer_DGHV(chiffremult,prime);



		    	// comparer avec multiplication en clair
			printf("\n");
		    	printf("comparer avec multiplication en clair\n");
   		    	printf("-------------------------------------\n");
 			printf("\n");
			gmp_printf (" %Zd * %Zd = %Zd\n",c1,c2,p); }


		    else
			{  printf("\n"); printf("\nla propriété homomorphe est perdue pour la multiplication\n"); }

			printf("\n***********************************************************************************");}


	if (opc==2)

		{

		   /* DEclaration des variables */
 		    int num,i,j,t;
		    int soma[4];
		    int C1[4],C2[4];

		    mpz_t c1a,c2a,c3a,c4a;
		    mpz_t c1b,c2b,c3b,c4b,cretenue,cin;
		    mpz_t sum1,sum2,sum3,sum4;
		    mpz_t car,car1,car2;
		    mpz_t chiffre1a,chiffre1b,chiffre2a,chiffre2b;
		    mpz_t chiffre3a,chiffre3b,chiffre4a,chiffre4b;
			mpz_t ccar,ccar1,ccar2;
			mpz_t csum1,csum2,csum3,csum4;


			mpz_init(ccar);
			mpz_init(ccar1);
			mpz_init(ccar2);

		    mpz_init(c1a);
		    mpz_init(c2a);
		    mpz_init(c3a);
		    mpz_init(c4a);
		    mpz_init(c1b);
		    mpz_init(c2b);
		    mpz_init(c3b);
		    mpz_init(c4b);

		    mpz_init(cretenue);
		    mpz_init(cin);

		    mpz_init(chiffre1a);
		    mpz_init(chiffre2a);
		    mpz_init(chiffre3a);
		    mpz_init(chiffre4a);
		    mpz_init(chiffre1b);
		    mpz_init(chiffre2b);
		    mpz_init(chiffre3b);
		    mpz_init(chiffre4b);

	    	    mpz_init(sum1);
		    mpz_init(sum2);
		    mpz_init(sum3);
		    mpz_init(sum4);

	    	    mpz_init(csum1);
		    mpz_init(csum2);
		    mpz_init(csum3);
		    mpz_init(csum4);

		    mpz_init(car);
		    mpz_init(car1);
		    mpz_init(car2);


		// demander messages en clair, taille parametres
 		    printf("\n");
                    printf("           -----------------------------------------\n");
		    printf("           :            Entrer Parametres          :\n");
 		    printf("           -----------------------------------------\n");
 		    printf("\n");

		    printf("\nEntrer la taille de la clé secrete: ");
		    scanf("%d",&n);

		    printf("\nEntrer la taille de q (veuillez respecter les normes de la taille): ");
		    scanf("%d",&taille_q);

		    printf("\nEntrer la taille du bruit r (rappel:r<p/4): ");
		    scanf("%d",&taille_r);

    		    printf("\ncin (La retenue initiale = 0): ");
		    gmp_scanf("%Zd",&cin);

		// Generation des clés
 		    printf("\n");
                    printf("           ----------------------------------------\n");
		    printf("           :           Generation des clés        :\n");
 		    printf("           ----------------------------------------\n");
 		    printf("\n");

		    gen_premier_alea_intervalle(prime,n,state);/*on genere ici une clé qui est un nombre premier*/

		    gmp_printf ("Private Key :== p= %Zd ==\n",prime );/*on affiche la clé*/

  			// Addition Binaire

 			printf("\n");
                    	printf("           ------------------------------------------\n");
		    	printf("           :          FULL ADDER de 4- bits         :\n");
 		    	printf("           ------------------------------------------\n");
 		    	printf("\n");
			num=4;

 			/* Introduire les Messages en Clair pour le premier tableau */
			printf("Introduire les bits du M1\n");
			printf("-------------------------");
			printf("\n");
			t=1;
			while ( t<=num)
			{

				printf("\nEcrire bit %d: ",t);
				scanf("%d",&C1[t]);
				t=t+1;
			   }


			/* Introduire les Messages en Clair pour le deuxieme tableau */

			printf("\n");
			printf("Introduire les bits du M2\n");
			printf("-------------------------");
			printf("\n");

			j=1;
			while ( j<=num)
			{
				printf("\nEcrire bit %d: ",j);
				scanf("%d",&C2[j]);
				j=j+1;
			}

			// Affectation à des variables avec GMP

			mpz_set_ui(c1a,C1[1]);
			mpz_set_ui(c1b,C2[1]);
			mpz_set_ui(c2a,C1[2]);
			mpz_set_ui(c2b,C2[2]);
			mpz_set_ui(c3a,C1[3]);
			mpz_set_ui(c3b,C2[3]);
			mpz_set_ui(c4a,C1[4]);
			mpz_set_ui(c4b,C2[4]);

			// Calcul de Full adder et carryout des bits de ce deux tableau


			 gmp_printf ("C1[1]  : %Zd\n",c1a);
			 gmp_printf ("C2[1]  : %Zd\n",c1b);
			 gmp_printf ("C1[2]  : %Zd\n",c2a);
			 gmp_printf ("C2[2]  : %Zd\n",c2b);
			 gmp_printf ("C1[3]  : %Zd\n",c3a);
			 gmp_printf ("C2[3]  : %Zd\n",c3b);
			 gmp_printf ("C1[4]  : %Zd\n",c4a);
			 gmp_printf ("C2[4]  : %Zd\n",c4b);


  			//Full Adder 4-bits

			mpz_xor(sum4,c4a,c4b);
			mpz_mul(car1,c4a,c4b);
			mpz_mul(car2,sum4,cin);
			mpz_xor(sum4,sum4,cin);
			mpz_ior(car,car1,car2);


			//Somme bits 3
			mpz_xor(sum3,c3a,c3b);
			mpz_mul(car1,c3a,c3b);
			mpz_mul(car2,sum3,car);
			mpz_xor(sum3,sum3,car);
			mpz_ior(car,car1,car2);



			//Somme bits 2

			mpz_xor(sum2,c2a,c2b);
			mpz_mul(car1,c2a,c2b);
			mpz_mul(car2,sum2,car);
			mpz_xor(sum2,sum2,car);
			mpz_ior(car,car1,car2);



			//Somme bits 1
			mpz_xor(sum1,c1a,c1b);
			mpz_mul(car1,c1a,c1b);
			mpz_mul(car2,sum1,car);
			mpz_xor(sum1,sum1,car);
			mpz_ior(car,car1,car2);




			// donner le resultat chiffré

			printf("\nSomme des Messages en Clair \n");
	 		printf("\n----------------------------\n");
			printf("\n");

			gmp_printf ("    %Zd  %Zd  %Zd  %Zd \n",c1a,c2a,c3a,c4a);
			gmp_printf ("+   %Zd  %Zd  %Zd  %Zd \n",c1b,c2b,c3b,c4b);
			gmp_printf("-------------------- \n");
 			gmp_printf ("%Zd  %Zd  %Zd  %Zd  %Zd\n",car,sum1,sum2,sum3,sum4);

	 		printf("\n");



			    printf("\n");
		            printf("           ------------------------------------------\n");
			    printf("           :            CHIFFREMENT DGHV            :\n");
	 		    printf("           ------------------------------------------\n");
	 		    printf("\n");


			// chiffrer messages

		    chiffrement_DGHV(chiffre1a,c1a,n,prime,taille_q,taille_r );/*fonction chiffrement_DGHV pour chiffrer le message*/
		    chiffrement_DGHV(chiffre1b,c1b,n,prime,taille_q,taille_r );/*fonction chiffrement_DGHV pour chiffrer le message*/

		    chiffrement_DGHV(chiffre2a,c2a,n,prime,taille_q,taille_r );/*fonction chiffrement_DGHV pour chiffrer le message*/
		    chiffrement_DGHV(chiffre2b,c2b,n,prime,taille_q,taille_r );/*fonction chiffrement_DGHV pour chiffrer le message*/

		    chiffrement_DGHV(chiffre3a,c3a,n,prime,taille_q,taille_r );/*fonction chiffrement_DGHV pour chiffrer le message*/
		    chiffrement_DGHV(chiffre3b,c3b,n,prime,taille_q,taille_r );/*fonction chiffrement_DGHV pour chiffrer le message*/

		    chiffrement_DGHV(chiffre4a,c4a,n,prime,taille_q,taille_r );/*fonction chiffrement_DGHV pour chiffrer le message*/
		    chiffrement_DGHV(chiffre4b,c4b,n,prime,taille_q,taille_r );/*fonction chiffrement_DGHV pour chiffrer le message*/

		    chiffrement_DGHV(cretenue,cin,n,prime,taille_q,taille_r );/*fonction chiffrement_DGHV pour chiffrer le message*/

 		    gmp_printf ("C1[1]  : %Zd\n",chiffre1a);
 		    gmp_printf ("C2[1]  : %Zd\n",chiffre1b);

 		    gmp_printf ("C1[2]  : %Zd\n",chiffre2a);
 		    gmp_printf ("C2[2]  : %Zd\n",chiffre2b);

 		    gmp_printf ("C1[3]  : %Zd\n",chiffre3a);
 		    gmp_printf ("C2[3]  : %Zd\n",chiffre3b);

 		    gmp_printf ("C1[4]  : %Zd\n",chiffre4a);
 		    gmp_printf ("C2[4]  : %Zd\n",chiffre4b);

		    gmp_printf ("Cret	: %Zd\n",cretenue);

  		    printf("\n");
		    printf("\n******************************************************************************");
		    printf("\nAddition des chiffrés\n");
   		    printf("----------------------\n");
 		    printf("\n");


			//Somme chiffr


		  mpz_add(csum4,chiffre4a,chiffre4b);
			mpz_mul(ccar1,chiffre4a,chiffre4b);
			mpz_mul(ccar2,csum4,cretenue);
			mpz_add(csum4,csum4,cretenue);
			mpz_add(ccar,ccar1,ccar2);

			printf ("\n");
			printf ("\n");

			gmp_printf ("sum4  : %Zd\n",csum4);
			gmp_printf ("car4  : %Zd\n",ccar);

			//Somme bits 3
			mpz_add(csum3,chiffre3a,chiffre3b);
			mpz_mul(ccar1,chiffre3a,chiffre3b);
			mpz_mul(ccar2,csum3,ccar);
			mpz_add(csum3,csum3,ccar);
			mpz_add(ccar,ccar1,ccar2);

			printf ("\n");
			printf ("\n");

			gmp_printf ("sum3  : %Zd\n",csum3);
			gmp_printf ("car3  : %Zd\n",ccar);

			//Somme bits 2
			mpz_add(csum2,chiffre2a,chiffre2b);
			mpz_mul(ccar1,chiffre2a,chiffre2b);
			mpz_mul(ccar2,csum2,ccar);
			mpz_add(csum2,csum2,ccar);
			mpz_add(ccar,ccar1,ccar2);

			printf ("\n");
			printf ("\n");

			gmp_printf ("sum2  : %Zd\n",csum2);
			gmp_printf ("car2  : %Zd\n",ccar);

			//Somme chiffr1
			mpz_add(csum1,chiffre1a,chiffre1b);
			mpz_mul(ccar1,chiffre1a,chiffre1b);
			mpz_mul(ccar2,csum1,ccar);
			mpz_add(csum1,csum1,ccar);
			mpz_add(ccar,ccar1,ccar2);

			printf ("\n");
			printf ("\n");

			gmp_printf ("sum1  : %Zd\n",csum1);
			gmp_printf ("car1  : %Zd\n",ccar);

 		   if ( (taille_r+1)<(n-1)){

			// verification: dechiffrer le resultat

		    	printf("\nDechiffrement de la somme\n");
   		    	printf("-------------------------\n");
 			printf("\nLa retenue\n");
			printf("------------\n");
			printf("\n");
			dechiffrer_DGHV(ccar,prime);
			printf("===========\n");
			printf("\n");
			dechiffrer_DGHV(csum1,prime);
			dechiffrer_DGHV(csum2,prime);
			dechiffrer_DGHV(csum3,prime);
			dechiffrer_DGHV(csum4,prime);



			}

		    else

			{  printf("\n"); printf("\nla propriété homomorphe est perdue pour laddition\n");}


 	}

	if (opc==3)
		{
		   /*initialise random state*/
		    int n,taille_q,taille_r;
		    gmp_randstate_t state;
		    gmp_randinit_default (state);
		    mpz_t prime,m;
		    mpz_t chiffre;
		    mpz_init(chiffre);
		    mpz_init(prime);
		    mpz_init(m);

 		    // FONCTION CODAGE
		    printf("\n");
                    printf("           ----------------------------------------\n");
		    printf("           :                  CHIFFREMENT              :\n");
 		    printf("           ----------------------------------------\n");
 		    printf("\n");
		    // Introduire la taille des parametres
 		    printf("\n");
                    printf("           -----------------------------------------\n");
		    printf("           :            Entrer Parametres          :\n");
 		    printf("           -----------------------------------------\n");
 		    printf("\n");

		    printf("\nEntrer la taille de la clé secrete: ");
		    scanf("%d",&n);

		    printf("\nEntrer la taille de q (veuillez respecter les normes de la taille): ");
		    scanf("%d",&taille_q);

		    printf("\nEntrer la taille du bruit r (rappel:r<p/4): ");
		    scanf("%d",&taille_r);


		    // Generation des clés
 		    printf("\n");
                    printf("           ----------------------------------------\n");
		    printf("           :           Generation des clés        :\n");
 		    printf("           ----------------------------------------\n");
 		    printf("\n");

		    gen_premier_alea_intervalle(prime,n,state);/*on genere ici une clé qui est un nombre premier*/

		    gmp_printf ("votre clé  est p=%Zd\n",prime );/*on affiche la clé*/


		    // Demander messages en clair

 		    printf("\n");
                    printf("           ----------------------------------------\n");
		    printf("           :            Message en Clair         :\n");
 		    printf("           ----------------------------------------\n");
 		    printf("\n");

		    printf("\nMessage en clair(bit) m: ");
		    gmp_scanf("%Zd",&m);

		    // chiffrement message
 		    printf("\n");
                    printf("           ------------------------------------------\n");
		    printf("           :            CHIFFREMENT DGHV            :\n");
 		    printf("           ------------------------------------------\n");
 		    printf("\n");
		    chiffrement_DGHV(chiffre,m,n,prime,taille_q,taille_r );/*fonction chiffrement_DGHV pour chiffrer le message*/
    		    gmp_printf ("Le chiffré de votre message est : %Zd" ,chiffre);
		    printf("\n");
		    }

	if (opc==4)
		{
		    // DECHIFFREMENT DU MESSAGE

		    mpz_t message,key;
    		    mpz_init(message);
		    mpz_init(key);
 		    printf("\n");
                    printf("           ------------------------------------------\n");
		    printf("           :            DECHIFFREMENT DGHV          :\n");
 		    printf("           ------------------------------------------\n");
 		    printf("\n");
		    printf("\nEntrer le message à dechiffrer:");
		    gmp_scanf("%Zd",message);
		    printf("\nEntrer la clé secrète:");
		    gmp_scanf("%Zd",key);
		    dechiffrer_DGHV(message,key);

		    }

}
		time = clock();
    		printf("\nTemps d'execution = %d  ms\n", time);
 return 0;
}





void gen_alea_intervalle(mpz_t alea,int n,gmp_randstate_t state) /*on genere un nombre compris entre min et max*/
{
     mpz_t max;
     mpz_init(max);
     mpz_ui_pow_ui(max,2,n);
     mpz_t min;
     mpz_init(min);
     mpz_ui_pow_ui(min,2,n-1);
     mpz_urandomm(alea,state,max);

    do
     {
         mpz_urandomm(alea,state,max);
     }while(mpz_cmp(alea,min) > 0);

    return;
}

// trouver un nombre premier compris entre min et max à l'aide du nombre généré
void gen_premier_alea_intervalle(mpz_t prime,int n,gmp_randstate_t state)
{
  mpz_t prime2;
  mpz_init(prime2);
  gen_alea_intervalle(prime,n,state);

  do /*on utilise une fonction qui en fonction de miler rabin nous donne un nombre premier plus grand que prime génére précédement et  cette fonction génére un nombre premier selon le test de miller rabin.Ce dernier etant probabiliste on le repete 5 fois*/
    {
      mpz_nextprime(prime,prime);
      //mpz_sub_ui(prime2,prime,1);        	/* prime2=(Prime-1)/2 */
      //mpz_divexact_ui(prime2,prime2,2);		/* div exact car 2 | Prime2-1 */

    }while( !mpz_probab_prime_p(prime,MR_REP));	/* tests de Miller-Rabin*/
	    //||
	    //!mpz_probab_prime_p(prime2,MR_REP)

  return;
}



/* Chiffrement d'un bit donné en entré*/
void  chiffrement_DGHV(mpz_t chiffre,mpz_t m,int taille_p, mpz_t p,int taille_q,int taille_r)
{
    mpz_t q,r,prod,inter;
    mpz_init(prod);
    mpz_init(inter);
    mpz_init(q);
    mpz_init(r);
    mpz_init(chiffre);
    /*initialise random state*/
    gmp_randstate_t state;
    gmp_randinit_default (state);

    mpz_urandomb (r, state, taille_r);
    mpz_urandomb (q, state, taille_q);
    mpz_mul(prod,q,p);
    mpz_add(r,r,r);
    mpz_add(chiffre,prod,r);
    mpz_add(chiffre,chiffre,m);

return;

}

// Procedure pour dechiffrer
void dechiffrer_DGHV(mpz_t chiffre,mpz_t key)
{
     mpz_t x;
     mpz_t y;
     mpz_init(y);
     mpz_t dechiffre;
     mpz_init(dechiffre);
     mpz_init(x);
     mpz_set_str(x, "1", 10);
     mpz_set_str(y,"2",10);
     mpz_powm (dechiffre, chiffre , x , key);
     mpz_powm(dechiffre,dechiffre,x,y);
     gmp_printf ("Dechiffrement_DGHV (%Zd)= %Zd\n",chiffre,dechiffre);
return;
}


// Procedure pour trouver le XOR de deux bits
void somxor(mpz_t s,mpz_t c1,mpz_t c2)
{
	mpz_t x,y;
 	mpz_init(x);
	mpz_init(y);
	mpz_init(s);
	mpz_cmp(c1, c2);

	if (mpz_cmp(c1, c2)==0){
		mpz_set_ui(s,0);
		;}
	else
		{mpz_add(s,c1,c2);}
}
// Procedure pour trouver le OR de deux bits
void somor(mpz_t s,mpz_t c1,mpz_t c2)
{

	mpz_t x,y;
 	mpz_init(x);
	mpz_init(y);
	mpz_init(s);
mpz_cmp(c1, c2);
	if (mpz_cmp(c1, c2)==0){
		mpz_mul(s,c1,c2);
		}
	else
		{mpz_add(s,c1,c2);}

}


// Calcule le produit de deux bits
void prodand(mpz_t p,mpz_t b1,mpz_t b2)
{

	mpz_mul(p,b1,b2);
		}


// Fonction  Half Full Adder
void HA(mpz_t sum,mpz_t b1,mpz_t b2)
{
	mpz_t car;
 	mpz_init(car);
	somxor(sum,b1,b2);
	prodand(car,b1,b2);
	/*gmp_printf (" %Zd \n",sum);
	gmp_printf (" %Zd \n",car); */

}

// Full Adder de deux bits
void FA(mpz_t sum,mpz_t b1,mpz_t b2,mpz_t cin)
{
	mpz_init(sum);
 	//prodand(car1,b1,b2);
	HA(sum,b1,b2);
	//prodand(car2,sum1,cin);
	HA(sum,sum,cin);
	//somor(car,car1,car2);

	//gmp_printf ("Sum: %Zd\n ",sum);/* retenue*/

}

// Retenue de Full Adder
void carryout(mpz_t car,mpz_t b1,mpz_t b2,mpz_t cin)
{
	mpz_t sum1,car1,car2;
 	mpz_init(sum1);
mpz_init(car1);
mpz_init(car2);
	prodand(car1,b1,b2);
	HA(sum1,b1,b2);
	prodand(car2,sum1,cin);
	//HA(sum,sum1,cin);
	somor(car,car1,car2);

	//gmp_printf ("car: %Zd\n ",car);/* retenue*/

}

// Fonction qui calcule le XOR de deux bits
int somxor1(int c1,int c2)
{
	int som1;
	if ((c1==1) &&(c2==1)){
		som1=0;}
	else
		{som1=c1+c2;}

	return som1;

}

// Fonction qui calcule la somme de deux bits
int somor1(int c1,int c2)
{
	int som2;
	if ((c1==1) &&(c2==1)){
		som2=1;}
	else
		{som2=c1+c2;}

	return som2;

}


void somme_bit(mpz_t s,mpz_t c1,mpz_t c2)
{

	mpz_t x,y;
 	mpz_init(x);
	mpz_init(y);
	mpz_init(s);
	mpz_set_ui(x, 1);
	mpz_set_ui(y, 1);
	if ((c1==x) &&(c2==y)){
		mpz_set_str(s, "0", 10);
		;}
	else
		{mpz_add(s,c1,c2);}



}
