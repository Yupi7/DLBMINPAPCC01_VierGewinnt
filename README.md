# Vier gewinnt – C++17-Spiele-Engine

**IU-Modul:** DLBMINPAPCC01 – Projekt: Allgemeine Programmierung mit C/C++  
**Projekt:** Vier gewinnt (Phase 3, Finalisierung)

## Voraussetzungen

- C++17-kompatibler Compiler
- CMake ab Version 3.16
- Terminal mit UTF-8-Unterstützung; für Farben und Animation möglichst ANSI-kompatibel
- macOS oder Linux; andere Terminals können Farben, Unicode-Zeichen und Signalton abweichend darstellen

## Funktionen

- **Spieler gegen Spieler:** zwei Personen spielen abwechselnd an einem Terminal.
- **Spieler gegen Computer** mit drei Schwierigkeitsstufen:
  - **Amateur:** zufällige gültige Spalte
  - **Profi:** erkennt sofortige Gewinne und Blockaden; bewertet Drohungen, Gabelmöglichkeiten und Positionen
  - **Legende:** Minimax mit Alpha-Beta-Pruning, Suchtiefe sieben Halbzüge
- 6 × 7 Spielfeld mit horizontaler, vertikaler und diagonaler Gewinnprüfung
- Eingabevalidierung bei ungültigen Werten, belegten Spalten und leeren Namen
- Farbige Spielsteine, Unicode-Spielfeld, Fallanimation und terminalabhängiger Signalton
- Speicherung abgeschlossener Partien, Anzeige früherer Spiele und schrittweises Replay
- Spielerstatistik aus gespeicherten Partien
- Automatisierte Komponentenprüfungen über CTest

## Projektstruktur

```text
src/              C++-Quellcode und Headerdateien
tests/tests.cpp   Automatisierte Testfälle
data/games.dat    Gespeicherte Partien (wird lokal erzeugt, nicht ins Git übernommen)
CMakeLists.txt    Build-Konfiguration
README.md         Diese Anleitung
```

## Bauen, starten und testen

Alle Befehle beginnen **im Hauptordner des Projekts**:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

**Wichtig für den Speicherpfad:** Die Anwendung verwendet momentan den relativen Pfad `../data/games.dat`. Starte sie daher **aus dem Build-Ordner**, damit gespeicherte Partien in `data/games.dat` innerhalb des Projekts landen:

```bash
mkdir -p data
cd build
./VierGewinnt
```

Nach dem Spielen gelangst du mit `cd ..` zurück zum Projektordner. Um die Tests aus dem Build-Ordner zu starten:

```bash
ctest --output-on-failure
```

## Bedienung

1. **Spieler gegen Spieler:** zwei Spielernamen eingeben.
2. **Spieler gegen Computer:** Namen und Schwierigkeit (1 = Amateur, 2 = Profi, 3 = Legende) auswählen.
3. **Gespeicherte Spiele anzeigen:** bisherige Partien und Ergebnisse ansehen.
4. **Spiel wiederholen:** gespeicherte Partie auswählen; mit Enter zum nächsten Zug.
5. **Spielerstatistik:** Spiele, Siege, Niederlagen und Unentschieden je Name.
6. **Programm beenden:** Anwendung schließen.

Während des Spiels mit einer Zahl von **1 bis 7** die Spalte auswählen. Die Steine fallen automatisch auf das unterste freie Feld. Vier gleiche Steine in einer Reihe gewinnen; ein volles Brett ohne Sieg ergibt ein Unentschieden.

## Teststrategie

`ctest` führt das Testprogramm `VierGewinntTests` aus. Darin sind mehrere automatisierte Prüfungen enthalten, unter anderem für Gewinnrichtungen, volle Spalten, Zugrücknahme, KI-Gewinn/Blockade und Statistik. Die ursprünglichen zwölf manuellen Testfälle und die vollständige Testmatrix sind im Portfolio dokumentiert.

Die Terminaldarstellung, die akustische Ausgabe, das Replay und die Menübedienung sollten zusätzlich interaktiv geprüft werden.

## Technischer Ansatz und Grenzen

`Board` verwaltet das Spielfeld und die Spielregeln; `Game` steuert den Ablauf; `GameRepository` speichert Partien; `Replay` rekonstruiert Züge; `ComputerPlayer` wählt KI-Züge; `Statistics` berechnet spielübergreifende Ergebnisse.

Bei der festen Größe von 6 × 7 ist der Aufwand der normalen Spielfeldoperationen praktisch konstant begrenzt. Die Suche von **Legende** hat ohne Beschneidung im schlechtesten Fall exponentielles Wachstum in der Suchtiefe, näherungsweise `O(7^d)`; Alpha-Beta-Pruning reduziert die tatsächlich untersuchten Knoten. Die Suche ist absichtlich auf sieben Halbzüge begrenzt und garantiert deshalb kein perfektes Spiel.

Farben, Fallanimation, UTF-8-Zeichen und Terminalton hängen von der Terminalumgebung ab. Für die Ausführung ist kein Internetzugang notwendig.

## Abgabepaket

Für die finale IU-Abgabe gehören der Quellcode (`src/`), `tests/`, `CMakeLists.txt`, diese README, die erforderliche Dokumentation und die Bildschirmaufnahme in das ZIP-Archiv. **Nicht nötig:** `.git/`, `build/`, `.idea/`. Eine `games.dat` kann optional als anonymisierter Testdatensatz beigelegt werden.
