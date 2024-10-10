Blajin Madlena 312CB

TEMA 1 SDA

Problema costa in crearea unui trenulet de tip |#| care sa fie implementat ca o lista dubla 
inlantuita circulara cu santinela si adresa mecanicului, care initial indica spre primul vagon |#|.
In continuare, voi prezenta logica operatiilor pe care le putem efectua asupra trenuletului.

Initial am initializat trenul cu ajutorul functieit InitT() in care am creat structura necesara. 
1. Operatii de tip UPDATE
MOVE_RIGHT - functia efectueaza deplasarea mecanicului in dreapta. Daca mecanicul se afla in ultimul vagon, alocam
un vagon nou cu caracterul # si mutam mecanicul in acel vagon. 
MOVE_LEFT - functia efectueaza deplasarea mecanicului in stanga. Daca mecanicul se afla in primul vagon trebuie sa il mutam in ultimul => tren->s->pre
WRITE<C> - functia care scrie un caracter in vagonul mecanicului => tren->mecanic->info = val (unde val este caracterul transmis din fisier)
CLEAR_CELL - functia care sterge nodul/vagonul in care se afla mecanicul. Dupa ce refacem legaturile dintre vagonele tren->m->pre si tren->m->urm, mecanicul va indica deja spre vagonul din stanga. Daca mecanicul se afla in primul vagon, mecanicul se va muta in ultimul vagon, deci verificam daca tren->m->pre este santinela
CLEAR_ALL - functia care va elibera toata vagoanele din tren si va initializa din nou trenul
INSERT_RIGHT<C>  - functia va insera un nod nou la dreapta vagonului in care se afla mecanicul. Daca mecanicul se afla in ultimul vagon, atunci vom crea un nod nou cu valoarea <C> si il vom cupla de restul listei, refacand toate legaturile. Mecanicul va indica spre vagonul inserat.
INSER_LEFT<C> - functia va insera un nod la stanga mecanicului. Daca vagonul in care se afla mecanicul este primul vagon atunci vom afisa ERROR in fisierul de iesire 
2. Operatii SEARCH
SEARCH <S> - functia efectueaza o cautare circulara a unui sir citit din fisier. Conditia principala a acestei functii este o singura parcurgere a listei. Am implementat functia setand aux la pozitia mecanicului, ulterior intr-un ciclu do-while am setat cateva conditii pentru implementarea corecta. Daca aux ajunge pe pozitia santinelei, atunci 
aux trebuie sa se mute la urmatoarea celula. Totodata, am cercetat si cazul in care un caracter nu se potriveste dar verificam daca inceputul - inc se reseteaza pe urmatoarea pozitie, cand i devine 0. Daca nu gasim sirul se afiseaza ERROR. Am folosit, de asemenea, o variabila inc pentru a memora inceputul secventei. 
SEARCH_LEFT<S> - functia implementeaza asemanator aceeasi logica ca si SEARCH, cu exceptia faptului ca vom cauta sirul in partea stanga a mecanicului pana cand intalnim santinela, pozitionand mecanicul la inceputul sirului gasit. Daca nu gasim sirul se afiseaza ERROR
SEARCH_RIGHT<S> - functia implementeaza asemanator aceeasi logica ca si SEARCH, cu exceptia faptului ca vom cauta sirul in partea dreapta a mecanicului pana cand intalnim santinela, pozitionand mecanicul la inceputul sirului gasit. Daca nu gasim sirul se afiseaza ERROR
3. Operatii QUERY
SHOW_CURRENT - functia printeaza caracterul de pe pozitia mecanicului 
SHOW - functia care afiseaza intreg trenul si delimiteaza mecanicul prin | |
SWITCH - functia care inverseaza toate operatiile care se afla in coada.

* Pentru introducere operatiilor, am folosit o structura TOp pentru a memora si operatia si valoarea. In cazul in care operatia nu are o valoare, se introduce un sir vid. Coada este o lista dublu inlantuita cu 2 pointri spre sfarsit si inceput. Astfel citim din fisier operatiile si valorile, le introucem in lista si formam coada

EXECUTE - functia care se ocupa de efectuarea opertiilor stocate in coada si anume operatiile de UPDATE si SEARCH. Odata ce am extras operatia, elibberam celula din coada. 
La final, nu uitam sa eliberam structurile alocate dinamic: coadaOp si tren.
