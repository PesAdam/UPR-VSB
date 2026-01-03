# League of Legends Statistics Generator

Tento projekt slúži na spracovanie štatistík z hry League of Legends (🔫). Program funguje nasledovne: Hlavný modul main.c riadi celý proces. Najprv pomocou modulu loader.c načíta históriu zápasov a
mená hráčov zo vstupných textových súborov do pamäťových štruktúr spravovaných v player.c. Po skompletizovaní dát modul output.c vypočíta štatistiky (napr. K/D ratio, Win Rate), zoradí hráčov a
vygeneruje finálny HTML report (output.html).

## Súbory

* `main.c`: Hlavný vstupný bod programu.
* `player.c`: Správa hráčov (pridávanie, vyhľadávanie).
* `loader.c`: Načítanie dát zo súborov (`matches.txt`, `players.txt`).
* `output.c`: Generovanie výsledného HTML súboru.
* `player.h`, `loader.h`, `output.h`: Hlavičkové súbory.
* `Makefile`: Súbor pre automatizáciu prekladu.

## Požiadavky

* GCC kompilátor
* Make

## Kompilácia

Program je možné preložiť pomocou príkazu `make` v termináli:

```bash
make
```

Tento príkaz vytvorí spustiteľný súbor `lol-stats`.
Preklad zahŕňa AddressSanitizer pre detekciu pamäťových chýb.

## Spustenie

Program sa spúšťa s tromi argumentmi:

1. Cesta k súboru so zápasmi (napr. `matches.txt`)
2. Cesta k súboru s prezývkami hráčov (napr. `players.txt`)
3. Cesta k výstupnému HTML súboru (napr. `output.html`)

Príklad:

```bash
./lol-stats matches.txt players.txt output.html
```

## Formát vstupných súborov

### Matches file (`matches.txt`)
Obsahuje sériu zápasov. Každý zápas začína riadkom `match` a nasleduje 5 riadkov dát:
1. ID hráčov červeného tímu (oddelené čiarkou)
2. Štatistiky červeného tímu (K;A;D pre každého hráča)
3. ID hráčov modrého tímu
4. Štatistiky modrého tímu
5. Výťazný tím (`red` alebo `blue`)

### Players file (`players.txt`)
Obsahuje priradenie ID k prezývkam v formáte:
`ID,Nickname`

## Výstup

Program vygeneruje HTML súbor s tabuľkami obsahujúcimi:
* Celkové štatistiky všetkých hráčov (Kills, Assists, Deaths, Winrate, atď.)
* Top 3 hráčov podľa počtu zabití (Kills)
* Top 3 hráčov podľa počtu výhier (Wins)
