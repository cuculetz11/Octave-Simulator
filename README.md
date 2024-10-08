# Octave-Simulator
Cucu Viorel-Cosmin 314CA

	Tema #2 - Simulator de Octave

## In general

  Pentru a avea un main curat am facut cate o functie numita exec_"comada" 
pentru fiecare comanda in parte. Pentru a baga comenzi pana la intalnirea
lui "Q" cand oprim programul, am bagat toate aceste functii intr-o bucla de 
tip while().
	Inca din inceput am initalizat variabila "dim" cu 1, si am alocat memorie
pentru vectorul de mattrici "m" , vectorul ce retine nr de linii ale matricilor
"lin" si vectorul ce retine nr de coloane ale matricilor "col".  

## Incarcarea in memorie a unei matrice

  Daca carecterul citit este "L" atunci apelam functia exec_L(). In aceasta
vad daca capacitatea este suficienta, iar daca nu este, o dublez si realoc
memorie pentru vectorii "lin" si "col" si pentru vectorul de matrice "m". Apoi 
citesc nr de linii si coloane si apelez functia citire_matrice() in care aloc
memorie pentru matrice si citesc elementele matricei, iar apoi ii spun lui 
matricea ce are indexul corezpunzator sa proiecteze catre matricea alocata
dinamic. La final, cresc "dim" si numarul de matrici cu 1.

## Determinarea dimensiunilor unei matrice

  Daca carecterul citit este "D" atunci apelam functia exec_D(). Citim 
indexul matricei si afisez dimensiunile matricei.

## Afisarea unei matrice

  Daca carecterul citit este "P" atunci apelam functia exec_P(). Unde citim
indexul matricei si apoi apelam functia afisare_mat() ce afiseza normal o
matrice.

## Redimensionarea unei matrice

  Daca carecterul citit este "C" atunci apelam functia exec_C(). In aceasta
citim indexul, numarul de linii, apoi ficare linie ce trebuie sa apara in
matricea noua, analog pentru coloane. Apoi apelez functia resize_mat() ce 
aloca dinamic o matrice cu valorile de pe liniile si coloanele date, apoi
eliberez matricea intiala si o proiectez spre matricea creata.

## Inmultirea a doua matrice

  Daca caracterul citit este "M" atunci apelam functia exec_M(). Citim 
indexul celor doua matrice si vad daca capacitatea este suficienta, iar daca nu
este, o dublez si realoc memorie pentru vectorii "lin" si "col" si pentru 
vectorul de matrice "m". Le dau valori vectorilor ce retin numarul de linii si
de coloane pentru aceasta matrice produs, pe care o sa o pun la coada 
vectorului de matrici. Apelez functia prod_mat() unde aloc memorie pentru
matricea produs si apoi proiectez matricea de la coada vectorului de matrici
spre aceasta.

## Sortarea matricelor

  Daca caracterul citit este "O" atunci apelam functia sortare_mat().Unde 
aplic algoritmul de sorate a unui vector prin selectie,IAR prin functia
s_mat() vad suma tuturor elementelor matricei si le ordonez dupa aceasta, 
facand swap-ul matricelor si a elementelor vectorului "lin"  si "col" cu 
functiile schimbare_mat(), schimbare_vectdim().

## Transpunerea unei matrice

  Daca caracterul citit este "T" atunci apelam functia exec_T(). In aceasta
citesc indexul matricei ce trebuie transpusa, daca exista aceasta apelam
functia transpunere_mat(). In aceasta fac o matrice noua ce este egala cu 
transpusa matricei initiale, apoi eliberez matricea initala si dupa o proiectez
spre matricea creata.

## Ridicarea unei matrice la o putere in timp logaritmic

  Daca caracterul citit este "R" atunci apelam functia exec_R(). Unde citesc
indexul matricei ce trebuie sa o ridic si puterea la care sa o ridic. Daca 
aceasta se poate ridica aplez functia pow_mat(), unde aloc memorie pentru o 
matrice unitate, iar apoi aplic algoritmul de ridicare la putere in timp 
logaritmic. Eliberez matricea si apoi o proiectez spre matricea creata la 
inceputul functiei, acolo aflandu-se rezultatul.

## Eliberarea memoriei unei matrice

 Daca caracterul citit este "F" atunci apelam functia exec_F(). Unde citesc
indexul matricei ce trebuie eliberata si eliminata din vectorul de matrice. 
Eliberez acea matrice, apoi apelez functia eliberare_mat(), unde aduc cu cate 
o pozitie spre stanga toate matricele de la acel index pana la final, la fel 
si vectorii ce retin liniile si coloanele. Scad numarul de matrice si "dim" (
ce reprezinta numarul de matrice - 1), iar  daca cumva "dim" a ajuns la 
jumatate din capacitatea vectorului de matrice, "capacitatea" se injumatateste
si reaoloc vectorii "lin", "col" si vectorul de matrice.

## Inmultirea matricelor folosind algoritmul lui Strassen 

 Daca caracterul citit este "S" atunci apelam functia exec_S(). Unde citesc
indexul celor doua matrice, apoi verific daca se poate efectua acest algoritm. 
In cazul in care se poate efectua vad daca e suficenta memoria pe care o am 
alocata deja pentru ca fac exact ca la inmultirea normala a doua matrice si 
adaug matricea produs la final. Daca nu este suficenta memorie dublez 
"capacitatea" si realoc memorie pentru vectorii "lin" si "col" si pentru 
vectorul de matrice "m". Le dau valori vectorilor ce retin numarul de linii si
de coloane pentru aceasta matrice produs, apoi initializez matricea de la coada
vectorului de matirce unde se va afla matrice produs. Apoi aplic functia 
strassen(). In aceasta functie sparg cele doua matrice ce trebuie inmultite in
patru matrice bloc, aloc memorie pentru fiecare cu functia 
alocare_matpatratice(), apoi le dau valorile caracteristice din matricele mari. 
Pentru a efectua algoritmul lui Strassen avem nevoie de 7 matrice auxiliare pe
care le denumesc "p1","p2"...,"p7", pe care le aloc tot dinamic, apoi mai iau
inca zece matrice auxiliare ce reprezinta operatii de scadere sau adunare din
cele 7 matrice anterioare. Aplic strassen() pentru fiecare matrice auxilara
"p", ceea ce va face acest algoritm recursiv deoarece pana cand ordinul 
matricei nu e 1, inmultirea a oricaror 2 matrice se va face tot cu strassen(),
iar cand oridinul ajunge 1 va fi doar o inmultire de 2 numere. In final dezaloc
tot ce am alocat si la linia 460 verific daca cumva am alocat inainte 
rezultatul inmultirii(adica daca c-ul este alocat).Daca acesta exista il
eliberez.   

## Eliberarea tuturor resurselor

  Daca caracterul citit este "Q" atunci apelam functia exec_Q(). In aceasta
apelez eliberare_mat() ce elibereza o matrice 3d si eliberez vectorii "lin",
"col".
