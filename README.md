# Benchmark Sortowania przez Wstawianie (Insertion Sort) w C++

Projekt porównujący wydajność algorytmu **Insertion Sort** (O(n²)) na trzech fundamentalnych strukturach danych w C++: **tablicy dynamicznej**, **liście jednokierunkowej** oraz **liście dwukierunkowej**. 

Celem repozytorium jest zbadanie w praktyce, jak lokalność pamięci (*CPU Cache Locality*), sposób alokacji węzłów oraz optymalizacje kompilatora wpływają na rzeczywisty czas wykonania tego samego algorytmu.

---

## Kluczowe wnioski z eksperymentu

Mimo identycznej złożoności obliczeniowej O(n²) dla wszystkich struktur, rzeczywiste czasy wykonania różnią się drastycznie:

1. **Tablica dynamiczna (`int*`)** – działa wielokrotnie szybciej dzięki ciągłości danych w pamięci RAM. Procesor pobiera całe bloki danych do szybkiej pamięci podręcznej (*L1/L2 Cache*) i przewiduje kolejne odczyty (*Hardware Prefetching*).
2. **Listy powiązane z klasyczną alokacją (`new`)** – węzły są rozrzucone w losowych miejscach sterty. Przechodzenie po wskaźnikach generuje masowe błędy trafień w pamięć podręczną (*Cache Misses*), zmuszając procesor do czekania na pamięć RAM.
3. **Optymalizacja przez Memory Pool (Arena)** – zaalokowanie wszystkich węzłów list w jednym ciągłym bloku pamięci (`new Node[N]`) przy zachowaniu operacji na wskaźnikach znacząco redukuje zjawisko *Cache Miss* i przyspiesza sortowanie list.
4. **Przepinanie wskaźników zamiast kopiowania** – przeciążenie funkcji `insert_sort` dla struktur `lista*` oraz `lista2*` pozwala na bezpośrednią manipulację wskaźnikami `next` i `prev` bez kopiowania zawartości węzłów.

---

## Architektura projektu

W projekcie zastosowano połączenie **szablonów funkcji** oraz **przeciążania funkcji (Function Overloading)** w celu uzyskania maksymalnej wydajności dla każdej struktury:

* `template <typename T> void insert_sort(T* begin, T* end)` – uniwersalny szablon dla tablic i wskaźników, wykorzystujący klasyczne przesuwanie elementów od końca do początku.
* `void insert_sort(lista*& head)` – dedykowana implementacja dla listy jednokierunkowej, przepinająca wskaźniki `next` bezpośrednio na strukturze.
* `void insert_sort(lista2*& head)` – dedykowana implementacja dla listy dwukierunkowej, wykorzystująca wskaźnik `prev` do cofania się w posortowanej części listy.
* `template <typename Func> double pomiar(Func op)` – precyzyjny miernik czasu oparty na `std::chrono::steady_clock`.

---

## Kompilacja i uruchomienie

Aby uzyskać miarodajne wyniki wydajności, program należy skompilować z włączoną optymalizacją kompilatora (`-O3` lub tryb *Release*):

### Linux / macOS / Windows (g++ / clang++)
```bash
g++ -O3 -std=c++17 main.cpp -o benchmark
./benchmark
```

### Visual Studio
1. Otwórz projekt w Visual Studio.
2. Na górnym pasku narzędzi zmień konfigurację z **Debug** na **Release**.
3. Uruchom program za pomocą `Ctrl + F5`.

> **Uwaga:** Uruchomienie programu w trybie *Debug* (`-O0`) wyłącza rozwijanie funkcji (*inlining*) oraz wektoryzację pętli, co sztucznie wydłuża czas wykonania kilkukrotnie.

---

## Parametry testowe

* **Rozmiar zbioru danych (N):** `50 000` elementów typu `int`.
* **Generator liczb:** `std::mt19937` ze stałym ziarnem (`42`) – gwarantuje pełną powtarzalność testów oraz identyczny zestaw danych wejściowych dla każdej ze struktur.
* **Zakres wartości:** `1` – `1 000 000`.

---

## Przykładowy wynik działania

```text
Czas sortowania tablicy: 24.15 ms
Czas sortowania listy 1-kierunkowej (Memory Pool): 412.80 ms
Czas sortowania listy 2-kierunkowej (Memory Pool): 185.40 ms

Kontrola: 12 | 12 | 12
```
*(Rzeczywiste czasy zależą od modelu procesora, taktowania pamięci RAM oraz użytej flagi optymalizacji).*
