# DLBMINPAPCC01 – Vier gewinnt

C++17-Konsolenprojekt für das IU-Modul **DLBMINPAPCC01 – Allgemeine Programmierung mit C/C++**.

## Funktionen
- Spieler gegen Spieler
- Spieler gegen Computer mit drei Schwierigkeitsstufen: **Amateur**, **Profi**, **Legende**
- Legende verwendet Minimax mit Alpha-Beta-Pruning
- farbige Konsolendarstellung mit durchgehenden Textgrafiklinien
- Fallanimation und Terminalton beim Setzen eines Spielsteins
- persistente Speicherung abgeschlossener Spiele
- Replay gespeicherter Partien
- spielübergreifende Statistik anhand der Spielernamen
- automatisierte Tests mit CTest

## Build
```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

## Start
```bash
./VierGewinnt
```

## Tests
```bash
ctest --output-on-failure
# oder direkt:
./VierGewinntTests
```

## Komplexität
Das 6x7-Spielfeld besitzt eine konstante Größe. Normale Board-Operationen und die Gewinnprüfung sind daher im praktischen Einsatz konstant begrenzt. Die Schwierigkeitsstufe **Legende** durchsucht mit Minimax einen Spielbaum bis zu einer begrenzten Tiefe von 7 Halbzügen; Alpha-Beta-Pruning und eine Center-first-Zugreihenfolge reduzieren die tatsächlich untersuchten Knoten erheblich.
