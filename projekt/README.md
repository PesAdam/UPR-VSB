# LoL Štatistiky - Projekt UPR

Toto je projekt na predmet UPR (Úvod do programovaní). Vybral som si League of Legends štatistiky. V mojom programe najskôr načítam dáta zo suborov matches.txt a players.txt potom naásledne spracujeme tieto dáta a vytvoríme prehladné štatistiky vo formate HTML (možnosť otvoriť si vo webe).

## Ako projekt funguje
Program funguje ako konzolová aplikácia, ktorá prijíma tri argumenty:
1.  Cesta k súboru so zápasmi (`matches.txt`)
2.  Cesta k súboru s hráčmi (`players.txt`)
3.  Cesta k výstupnému HTML súboru (`output.html`)

**Príklad spustenia:**
```bash
make
./lol-stats matches.txt players.txt output.html
```

Aplikácia najprv načíta databázu prezývok, následne spracuje všetky zápasy a validuje ich. Ak sú dáta v poriadku, vygeneruje sa HTML súbor

---

## Testovanie a validácia

Aby som zabezpečil, že program funguje správne a odolá aj chybným vstupom, vytvoril som automatizovaný testovací systém.

### Ako fungujú testy
Testy spúšťam pomocou skriptu `tester.sh`, ktorý som napísal v Bashi. Tento skript:
1.  Automaticky skompiluje projekt pomocou `make`.
2.  Prechádza všetky podadresáre v priečinku `tests/` (napr. `01_zaklad`, `04_duplicitne_id`).
3.  Pre každý test spustí môj program s príslušnými `.txt` súbormi.
4.  **Overenie úspechu:** Ak v priečinku testu existuje súbor `expected_output.html`, skript porovná môj vygenerovaný výstup s týmto referenčným súborom (pomocou príkazu `diff`).
5.  **Overenie chyby:** Ak `expected_output.html` neexistuje, skript očakáva, že môj program zlyhá (vráti exit code != 0). Toto používam na testovanie nevalidných vstupov (zlé formáty, duplicity).

### Kde nájdem výstupy?
- **Pri manuálnom spustení:** Výstupný HTML súbor sa vytvorí tam, kde určíte v 3. argumente (napr. v koreňovom priečinku ako `output.html`).
- **Pri automatických testoch:** Skript generuje dočasné súbory priamo v priečinkoch testov.

Ak si chcem porovnať môj výstup s očakávaným manuálne, môžem použiť:
```bash
diff output.html tests/01_zaklad/expected_output.html
```
Alebo si jednoducho oba súbory otvorím v prehliadači a vizuálne skontrolujem.

---

## Popis súborov a implementácie

Projekt som rozdelil do modulov pre lepšiu prehľadnosť a správu kódu.

### `main.c` (Hlavný riadiaci modul)
Toto je vstupný bod programu.
- **Logika:** Zabezpečuje kontrolu počtu argumentov príkazového riadku.
- **Poradie volaní:** 
    1.  Najprv volám `load_nicknames`, aby som naplnil databázu známych hráčov.
    2.  Následne volám `load_matches`, kde parsujem zápasy a kontrolujem, či sa ID zhodujú.
    3.  Nakoniec volám `validate_data`, ktorá skontroluje, či každý aktívny hráč má priradené meno.
    4.  Ak všetko prejde, volám `generate_html`.

### `loader.c` (Načítanie a parsovanie dát)
Tento súbor obsahuje logiku pre prácu so súbormi a textom.
- **`load_nicknames`:** Číta súbor po riadkoch. Používam `sscanf` na extrakciu ID a mena. Ak hráč s daným ID neexistuje, vytvorím ho a nastavím mu `has_nickname = 1`.
- **`load_matches`:** Implementoval som parser, ktorý číta zápasy v blokoch po 5 riadkoch (po kľúčovom slove "match").
    - **Validácia:** Pridal som kontroly formátu. Kontrolujem, či sa ID v rámci jedného zápasu neopakujú (vnorený cyklus pre unikátnosť 6 hráčov) a či je víťaz iba "red" alebo "blue".
    - **Spracovanie:** Ak sú dáta validné, aktualizujem štatistiky (kills, deaths, assists, wins...) v poli `players`.
- **`validate_data`:** Táto funkcia prejde všetkých hráčov a overí, či neexistuje taký, ktorý má odohrané zápasy (`games_played > 0`), ale nemá načítanú prezývku (`has_nickname == 0`).

### `player.c` a `player.h` (Dátové štruktúry)
Tu definujem, ako vyzerá hráč v pamäti.
- **`struct Player`:** Obsahuje všetko potrebné – ID, nickname, štatistiky (K/D/A), počty hier za strany atď. Pridal som sem aj pomocnú premennú `has_nickname` pre validáciu.
- **Globálne pole:** Dáta držím v statickom poli `players[MAX_PLAYERS]`.
- **Funkcie:** Implementoval som `find_player` (lineárne vyhľadávanie podľa ID) a `add_player` (pridanie nového hráča do poľa).

### `output.c` (Generovanie HTML)
Tento modul má na starosti prezentáciu výsledkov.
- **Dizajn:** Rozhodol som sa nepoužiť len čisté HTML, ale pridal som CSS štýly pre "Dark Mode" (tmavé pozadie, svetlý text), aby to vyzeralo pekne a moderne.
- **Logika výpisov:**
    - Generujem hlavnú tabuľku so všetkými štatistikami.
    - Počítam K/D pomer.
    - **Top 3 rebríčky:** Pre sekcie "Top 3 Kills" a "Top 3 Wins" používam jednoduchý triediaci algoritmus (Bubble Sort) nad poľom indexov, aby som nezmenil poradie v hlavnom poli hráčov.
### `Makefile`
Jednoduchý skript pre kompiláciu. Používam flagy `-Wall -Wextra -std=c99` pre zachovanie štandardov a `-fsanitize=address` pre odhalenie pamäťových chýb počas testovania.

### `Readme`
Na vytvorenie readme súboru som použil https://markdownlivepreview.com/