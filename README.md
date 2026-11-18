# Moon Landing Simulation

Symulacja lądowania lądownika księżycowego (grawitacja $g = 1.6\text{ m/s}^2$) napisana w języku C wraz ze skryptem w Pythonie do wizualizacji przebiegu lotu.

## Struktura projektu

* `main.c` – główny program symulujący opadanie, automatyczne sterowanie silnikiem hamującym oraz zapisujący dane do pliku CSV.
* `plot.py` – skrypt generujący wykresy wysokości i prędkości w funkcji czasu.
* `run.sh` – skrypt automatyzujący kompilację, przygotowanie środowiska Python, uruchomienie symulacji oraz wygenerowanie wykresów.
* `requirements.txt` – lista wymaganych bibliotek Pythona (`pandas`, `matplotlib`).
* `results/` – katalog wyjściowy zawierający dane symulacji (`results.csv`) oraz wygenerowane wykresy (`charts.png`).

## Wymagania

* Kompilator języka C (`gcc`)
* Python 3 (z modułem `venv` oraz `pip`)

## Uruchomienie

1. Nadaj uprawnienia wykonywania skryptowi (jednorazowo):
   ```bash
   chmod +x run.sh