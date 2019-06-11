 $ gcc -o test final.c -lgmp
$ ./test



En executant le programme, nous aurons comme affichage un Menu avec 5 options. Nous choissirons
une option parmi les 5.

* pour choisir l'option "chiffrement homomorphe simple":
- On saisit 1
- Entrer la taille de la clé secrete: 					1024 	(exemple)

- Entrer la taille de q (veuillez respecter les normes de la taille): 	55 	(exemple)     

- Entrer la taille du bruit r (rappel:r<p/4): 				7	(exemple)

- Le programme genere la cle secrete P
 
           ----------------------------------------
           :            Messages en Clair         :
           ----------------------------------------

// On introduit le message en claire

Message en clair(bit) M1: 1      

Message en clair(bit) M2: 0

cin (La retenue initiale = 0): 0 (On introduit la retenue initiale)

- On execute en faisant Enter pour avoir le resultat.


* pour choisir l'option "Full adder 4-bits":
- on saisit 2
- on introduit les parametres et les messages en clairs pour faire le Full adder de ces 4 bits

Choisir une option:2

           -----------------------------------------
           :            Entrer Parametres          :
           -----------------------------------------


Entrer la taille de la clé secrete: 1024

Entrer la taille de q (veuillez respecter les normes de la taille): 55

Entrer la taille du bruit r (rappel:r<p/4): 7

cin (La retenue initiale = 0): 0

           ----------------------------------------
           :           Generation des clés        :
           ----------------------------------------

Private Key :== p= 5891572246297868253412624759745406795585333619437698636102450190718985181854272934901524
35322851422543099170385277604802889653755029236812037203221021105101436906347320960924369464080027575296132
71536307927837223545322777240018954252741320474283752983445102922773653761893093283466588488022478739526104459909 ==

           ------------------------------------------
           :          FULL ADDER de 4- bits         :
           ------------------------------------------

Introduire les bits du M1
-------------------------

Ecrire bit 1: 1

Ecrire bit 2: 0

Ecrire bit 3: 1

Ecrire bit 4: 0

Introduire les bits du M2
-------------------------

Ecrire bit 1: 0

Ecrire bit 2: 0

Ecrire bit 3: 1

Ecrire bit 4: 1

- Le programme affichera le resultat sur le full adder et le calcul sur la somme des chiffres
- Le programme dechiffre la somme des chiffres pour comparer avec la somme de full adder


* L'option 3 consiste a chiffrer un bit

* L'option 4 consiste a dechiffrer un bit

* L'option 5 permet de quitter le programme

