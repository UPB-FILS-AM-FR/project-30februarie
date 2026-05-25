# LED Music Visualizer

| | |
|-|-|
|`Author` | Ionita Alexandra Maria

## Description
Acest proiect reprezintă un **sistem electronic de monitorizare și vizualizare dinamică a intensității acustice**, realizat în timp real cu ajutorul tehnologiei microcontrolerelor. Scopul său principal este de a capta undele sonore din mediul ambiental și de a le converti instantaneu într-o reprezentare grafică luminoasă, funcționând ca un analizor de ritm (VU-meter) de înaltă precizie.

Procesul tehnologic din spatele sistemului urmează un flux logic bine definit:

* **Captarea acustică:** Senzorul de sunet detectează vibrațiile aerului prin intermediul unei membrane sensibile. Cipul amplificator de pe modul transformă aceste unde mecanice în variații fine de tensiune electrică (semnal analogic).
* **Procesarea digitală:** Placa Arduino Uno preia acest semnal prin convertorul său analog-digital. Printr-un algoritm bazat pe o fereastră fixă de eșantionare (măsurată în milisecunde), microcontrolerul calculează diferența dintre valoarea minimă și cea maximă a undei sonore, determinând volumul real (amplitudinea peak-to-peak).
* **Afișarea luminoasă:** Valoarea calculată este mapată matematic în funcție de numărul total de LED-uri adresabile. Prin intermediul unui singur fir de date, Arduino transmite instrucțiuni unice fiecărui cip din banda WS2812B.

Rezultatul este un efect vizual fluid și extrem de reactiv: banda LED se extinde și se restrânge spectral pe un cod de culori standardizat. Primele LED-uri se aprind în **verde** (semnalând un zgomot ambiental redus), zona de mijloc trece în **galben/portocaliu** (pentru intensitate medie), iar vârfurile de volum, cum sunt bătăile de bass sau aplauzele puternice, declanșează aprinderea ultimelor LED-uri în **roșu**, oferind o dinamică vizuală spectaculoasă.


## Motivation
Am ales să realizez acest proiect din pasiune pentru muzică și din dorința de a aduce o schimbare tehnologică în propriul meu spațiu. Întotdeauna am avut benzi LED clasice în cameră, însă ele aveau un comportament monoton sau rulau jocuri de lumini repetitive, complet deconectate de atmosfera din jur. Mereu mi-am dorit un sistem capabil să „simtă” ritmul melodiilor mele preferate și să reacționeze inteligent la ele, nu doar să clipească haotic.

Acest proiect a fost oportunitatea perfectă de a trece de la statutul de simplu utilizator de tehnologie comercială la cel de creator. Am fost motivat să înțeleg cum pot folosi electronica aplicată pentru a da viață sunetului: de la captarea vibrațiilor prin microfon și eșantionarea lor în timp real pe placa Arduino, până la controlul precis al culorilor pe banda adresabilă. Dincolo de satisfacția tehnică de a scrie codul și de a potrivi firele pe breadboard, proiectul are o puternică motivație personală: am reușit să-mi transform camera într-un spațiu complet interactiv, unde muzica pe care o ascult prinde formă și culoare în timp real.


## Architecture
Arhitectura proiectului definește structura bloc-în-bloc a sistemului și modul în care informația și energia circulă între componente. Aceasta este împărțită în trei niveluri principale: **Hardware**, **Software** și **Alimentare/Energie**.

---

### 1. Arhitectura Hardware (Fluxul de Date)

Sistemul este configurat după o topologie de tip **Liniară / Serie**, unde datele circulă într-un singur sens, de la achiziție până la execuție:

* **Blocul de Achiziție (Intrare):** Senzorul de sunet (Microfonul) captează undele sonore analogice și le transmite prin pinul `A0` către creierul sistemului.
* **Blocul de Procesare (Central):** Placa **Arduino Uno** preia tensiunea variabilă, o convertește în format digital și calculează volumul.
* **Blocul de Execuție (Ieșire):** Prin pinul digital `6`, Arduino trimite un flux serial de date (instrucțiuni binare) către pinul `DIN` al **Bandei LED WS2812B** pentru a comanda fiecare pixel în parte.

---

### 2. Arhitectura de Alimentare (Managementul Energiei)

Pentru a asigura stabilitatea și a preveni arderea microcontrolerului, alimentarea este **separată pe două magistrale**, dar conectată printr-o **masă comună**:

* **Sursa de Putere:** Sursa de 5V/2A alimentează direct **Modulul de Breadboard**, care distribuie curentul pe șinele lungi.
* **Magistrala de Mare Putere (5V):** Banda LED consumă mult curent, motiv pentru care este legată direct la șinele modulului de alimentare, ocolind circuitele interne ale Arduino.
* **Magistrala de Logică / Semnal:** Placa Arduino și Microfonul sunt alimentate din tensiunea stabilizată (prin cablul USB sau pinii dedicați).
* **Masa Comună (GND):** Toate bornele de Minus (`GND`) de la Arduino, bandă LED, microfon și modulul de alimentare sunt legate împreună. Fără această masă comună, semnalul de date nu ar avea un punct de referință și LED-urile ar pâlpâi haotic.

---

### 3. Arhitectura Software (Logica Codului)

Codul rulat pe Arduino urmează o arhitectură de tip **Loop Secvențial în Timp Real**, structurat în trei mari etape repetitive:

```
[ Fereastră Eșantionare (40ms) ] ➡️ [ Calcul Amplitudine (Peak-to-Peak) ] ➡️ [ Mapare & Afișare Spectru ]

```

1. **Eșantionarea (Fereastra de 40ms):** Timp de 40 de milisecunde, Arduino citește continuu pinul `A0` și reține cea mai mică și cea mai mare valoare a undei de sunet detectate.
2. **Procesarea semnalului:** Se face diferența dintre valoarea maximă și cea minimă. Rezultatul ne dă amplitudinea curată a sunetului (volumul), eliminând zgomotul de fond static.
3. **Maparea și Actualizarea:** Valoarea obținută este convertită matematic în număr de LED-uri (folosind funcția `map`). Algoritmul aplică măștile de culoare (Verde, Galben, Roșu) în funcție de înălțimea pragului și trimite comanda finală prin funcția `strip.show()`.


### Block diagram

<img width="1787" height="1164" alt="image" src="https://github.com/user-attachments/assets/2baec3e4-e86b-4c3b-a0c8-eb8af98620ef" />


### Schematic

<img width="1442" height="1003" alt="image" src="https://github.com/user-attachments/assets/2b71c15e-a968-498e-a77c-a1316ddd70e2" />


### Components


<!-- This is just an example, fill in with your actual components -->

| Device | Usage | Price |
|--------|--------|-------|
| Arduino Uno | Proceseaza datele | [55 RON] |
| Banda LED | Afiseaza culorile | [99 RON] |
| Senzor sunet | Capteaza sunet | [6 RON] |
| Sursa priza |Ofera puetere| [12 RON] |
| Modul alimentare | Distribuie curent | [15 RON] |
| Rezistor | Protejeaza circuitul | [5 RON] |
| Fire | Transporta semnalul | [15 RON] |

### Libraries

| Library | Description | Usage |
| :--- | :--- | :--- |
| [Arduino](https://www.arduino.cc/reference/en/) | Core-ul sistemului și funcții de bază | Citire analogică și gestionarea timpului |
| [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel) | Controlul LED-urilor adresabile WS2812B | Gestionarea culorilor și afișarea spectrului |

## Log

<!-- write every week your progress here -->

### Week 6 - 12 May

### Week 7 - 19 May

### Week 20 - 26 May


## Reference links

<!-- Fill in with appropriate links and link titles -->

[Tutorial 1](https://www.youtube.com/watch?v=wdgULBpRoXk&t=1s&ab_channel=BenEater)

[Article 1](https://www.explainthatstuff.com/induction-motors.html)

[Link title](https://projecthub.arduino.cc/)
