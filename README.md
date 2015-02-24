# Lamps

Projekt implementujący eksperyment 1023 alternatyw Seibela w wersji z lampami.

## Wymagania

cmake 2.8
gcc 4.8.3
Qt 5.4.0

## Komponenty

### Panel eksperymentatora

##### Maksymalny czas eksperymentu w sekundach

##### Ze sprzężeniem zwrotnym
Jeśli tak, to przy nietrafionym kliknięciu pojawia się dźwięk z błędem.

##### Z odliczaniem czasu
Jeśli tak, to lampki palą się przez 'czas palenia się lampki', potem zawsze gasną.

##### Czas palenia się lampki
Lampka gaśnie samoczynnie po tym czasie.

##### Wczytaj sesję
Wczytuje odpowiedni plik .csv.

##### Start
Jeśli wczytany został plik .csv, to wczytywane są ustawienia i eksperyment jest ponowiony.
W przeciwnym wypadku uruchamia się panel użytkownika.

### Panel użytkownika

##### Pseudonim

##### Start
Rozpoczyna eksperyment.

### Eksperyment

##### Skróty klawiszowe
W lewym górnym rogu znajdują się skróty klawiszowe, które można wykorzystać.
W tym:
* rozpoczęcie/ponowienie sesji Ctrl+Shift+D
* wstrzymanie/zakończenie sesji Ctrl+Shift+S
* zakończenie programu Ctrl+Shift+Q

##### Rodzaj sesji
Na górze ekranu znajduje się napis oznaczający rodzaj sesji: próbna lub główna.

##### Lampki
Lampka ma stan: zapalona lub zgaszona.
Pod każdą lampką znajduje się przypisany jej klawisz.
Jeśli lampka jest zapalona i wciśnięty zostanie przypisany jej klawisz, lampka gaśnie.

### Pliki z danymi

Pliki te mają format .csv. Nazwa pliku to <pseudonim><data_rozpoczęcia_eksperymentu>.

Na początku znajduje się header zawierający informacje, takie jak:
* pseudonim
* maks. czas eksperymentu
* sprzężenie zwrotne (tak/nie)
* z odliczaniem czasu (tak/nie)
* timeout - czas palenia się lampki (ms)

Po każdej sesji eksperymentalnej zapisywane są statystyki:
* data
* numer sesji
* czas rozpoczęcia
* czas zatrzymania
* czas trwania
* liczba poprawnych kliknięć (zgaszeń lampki)
* liczba niepoprawnych kliknięć
* liczba pominiętych kliknięć - w przypadku odliczania czasu
* dla każdej lampki wartość w ms oznaczająca opóźnienie w kliknięciu w stosunku do zapalenia się lampki;
  w przypadku odliczania czasu wartość '-1' oznacza, że kliknięcie było pominięte.
