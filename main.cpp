#include <iostream>
#include <chrono>
#include <random>

using namespace std;

/********************************************************
* nazwa funkcji:       pomiar
* opis funkcji:        Mierzy czas wykonania przekazanej operacji w milisekundach.
* parametry:           op - obiekt funkcyjny (lambda) reprezentujący operację do zmierzenia
* zwracany typ i opis: double - czas wykonania operacji w milisekundach
* autor:               [Twój numer PESEL lub Imię i Nazwisko]
********************************************************/
template <typename Func>
double pomiar(Func op) {
    auto start = chrono::steady_clock::now();
    op();
    auto end = chrono::steady_clock::now();
    chrono::duration<double, milli> elapsed = end - start;
    return elapsed.count();
}

/********************************************************
* nazwa struktury:     lista
* opis struktury:      Reprezentuje pojedynczy węzeł listy jednokierunkowej.
* pola:                id - wartość liczbowa przechowywana w węźle
*                      next - wskaźnik na następny element listy
* autor:               [Twój numer PESEL lub Imię i Nazwisko]
********************************************************/
struct lista {
    int id;
    lista *next;
};

/********************************************************
* nazwa struktury:     lista2
* opis struktury:      Reprezentuje pojedynczy węzeł listy dwukierunkowej.
* pola:                liczba - wartość liczbowa przechowywana w węźle
*                      next - wskaźnik na następny element listy
*                      prev - wskaźnik na poprzedni element listy
* autor:               [Twój numer PESEL lub Imię i Nazwisko]
********************************************************/
struct lista2 {
    int liczba;
    lista2 *next;
    lista2 *prev;
};

/********************************************************
* nazwa funkcji:       insert_sort
* opis funkcji:        Sortuje rosnąco tablicę za pomocą algorytmu przez wstawianie.
* parametry:           begin - wskaźnik na pierwszy element tablicy
*                      end - wskaźnik za ostatni element tablicy
* zwracany typ i opis: brak (void)
* autor:               [Twój numer PESEL lub Imię i Nazwisko]
********************************************************/
template <typename T>
void insert_sort(T* begin, T* end) {
    if (begin == end) return;

    for (T* i = begin + 1; i != end; ++i) {
        T klucz = *i;
        T* j = i;

        // Przesuwanie elementów większych od klucza w prawo
        while (j > begin && *(j - 1) > klucz) {
            *j = *(j - 1);
            --j;
        }
        *j = klucz;
    }
}

/********************************************************
* nazwa funkcji:       insert_sort
* opis funkcji:        Sortuje rosnąco listę jednokierunkową przez wstawianie (przepinanie wskaźników).
* parametry:           head - referencja do wskaźnika na początek (głowę) listy
* zwracany typ i opis: brak (void)
* autor:               [Twój numer PESEL lub Imię i Nazwisko]
********************************************************/
void insert_sort(lista*& head) {
    if (!head || !head->next) return;

    lista* ogonPosortowanej = head;

    while (ogonPosortowanej->next != nullptr) {
        lista* obecny = ogonPosortowanej->next;

        if (obecny->id >= ogonPosortowanej->id) {
            ogonPosortowanej = obecny;
        }
        else if (obecny->id <= head->id) {
            // Wstawienie elementu na początek listy przed głowę
            ogonPosortowanej->next = obecny->next;
            obecny->next = head;
            head = obecny;
        }
        else {
            // Wyszukanie właściwego miejsca w posortowanej części listy
            lista* szukaj = head;
            while (szukaj->next->id < obecny->id) {
                szukaj = szukaj->next;
            }
            ogonPosortowanej->next = obecny->next;
            obecny->next = szukaj->next;
            szukaj->next = obecny;
        }
    }
}

/********************************************************
* nazwa funkcji:       insert_sort
* opis funkcji:        Sortuje rosnąco listę dwukierunkową przez wstawianie (przepinanie wskaźników).
* parametry:           head - referencja do wskaźnika na początek (głowę) listy
* zwracany typ i opis: brak (void)
* autor:               [Twój numer PESEL lub Imię i Nazwisko]
********************************************************/
void insert_sort(lista2*& head) {
    if (!head || !head->next) return;

    lista2* obecny = head->next;

    while (obecny != nullptr) {
        lista2* nastepny = obecny->next;
        lista2* szukaj = obecny->prev;

        // Cofanie się w lewo w poszukiwaniu elementu mniejszego lub równego
        while (szukaj != nullptr && szukaj->liczba > obecny->liczba) {
            szukaj = szukaj->prev;
        }

        if (szukaj != obecny->prev) {
            // Wypięcie elementu z dotychczasowej pozycji
            obecny->prev->next = obecny->next;
            if (obecny->next != nullptr) {
                obecny->next->prev = obecny->prev;
            }

            // Wpięcie elementu na nową pozycję
            if (szukaj == nullptr) {
                obecny->prev = nullptr;
                obecny->next = head;
                head->prev = obecny;
                head = obecny;
            } else {
                obecny->next = szukaj->next;
                obecny->prev = szukaj;
                if (szukaj->next != nullptr) {
                    szukaj->next->prev = obecny;
                }
                szukaj->next = obecny;
            }
        }
        obecny = nastepny;
    }
}

/********************************************************
* nazwa funkcji:       usunListe
* opis funkcji:        Zwalnia pamięć zaalokowaną dla listy jednokierunkowej.
* parametry:           l - wskaźnik na początek listy jednokierunkowej
* zwracany typ i opis: brak (void)
* autor:               [Twój numer PESEL lub Imię i Nazwisko]
********************************************************/
void usunListe(lista *l) {
    while (l != nullptr) {
        lista *do_usuniecia = l;
        l = l->next;
        delete do_usuniecia;
    }
}

/********************************************************
* nazwa funkcji:       usunListe2
* opis funkcji:        Zwalnia pamięć zaalokowaną dla listy dwukierunkowej.
* parametry:           l - wskaźnik na początek listy dwukierunkowej
* zwracany typ i opis: brak (void)
* autor:               [Twój numer PESEL lub Imię i Nazwisko]
********************************************************/
void usunListe2(lista2 *l) {
    while (l != nullptr) {
        lista2 *do_usuniecia = l;
        l = l->next;
        delete do_usuniecia;
    }
}

/********************************************************
* nazwa funkcji:       main
* opis funkcji:        Funkcja główna programu generująca dane testowe i mierząca czas sortowania.
* parametry:           brak
* zwracany typ i opis: int - kod zakończenia programu (0 oznacza poprawne wykonanie)
* autor:               [Twój numer PESEL lub Imię i Nazwisko]
********************************************************/
int main() {
    const int N = 50000;

    mt19937 gen(42);
    uniform_int_distribution<int> dist(1, 1000000);

    int* tab = new int[N];
    lista* l1 = nullptr;
    lista* ogon1 = nullptr;
    lista2* l2 = nullptr;
    lista2* ogon2 = nullptr;

    // Wypełnienie struktur identycznym zestawem losowych danych
    for (int i = 0; i < N; ++i) {
        int losowa = dist(gen);
        tab[i] = losowa;

        lista* nowy1 = new lista{losowa, nullptr};
        if (l1 == nullptr) {
            l1 = nowy1;
            ogon1 = nowy1;
        } else {
            ogon1->next = nowy1;
            ogon1 = nowy1;
        }

        lista2* nowy2 = new lista2{losowa, nullptr, nullptr};
        if (l2 == nullptr) {
            l2 = nowy2;
            ogon2 = nowy2;
        } else {
            ogon2->next = nowy2;
            nowy2->prev = ogon2;
            ogon2 = nowy2;
        }
    }

    double czasTablica = pomiar([&]() {
        insert_sort(tab, tab + N);
    });
    cout << "Czas sortowania tablicy: " << czasTablica << " ms" << endl;

    double czasLista1 = pomiar([&]() {
        insert_sort(l1);
    });
    cout << "Czas sortowania listy 1-kierunkowej: " << czasLista1 << " ms" << endl;

    double czasLista2 = pomiar([&]() {
        insert_sort(l2);
    });
    cout << "Czas sortowania listy 2-kierunkowej: " << czasLista2 << " ms" << endl;

    cout << "\nKontrola: " << tab << " | " << l1->id << " | " << l2->liczba << endl;

    delete[] tab;
    usunListe(l1);
    usunListe2(l2);

    return 0;
}
