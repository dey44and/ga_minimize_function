Andrei-Iosif Ioja <br>
Grupa 1408A

**Tema Laborator 3**

1. **Identificare preconditii**
- Vector populatie[], dim(populatie) = 100
- Vector cromozomi[], dim(cromozomi) = 5
- Probabilitatea de incrucisare, 0.2 <= pi <= 0.9
- Probabilitatea de mutatie, 0.01 <= pm <= 0.1
2. **Identificare postconditii**
- Vector best\_cromozomi[], dim(cromozomi) = 5
- f(best\_cromozomi) ~ 0, unde f(x) este functia ce s-a dorit a fi minimizata
3. **Analizarea complexitatii implementarii**
- **Generare populatie =>** operatia dominanta este de generare a unei valori, care se realizeaza in **θ**(DIM\_POPULATIE\*DIM\_CROMOZOM)
- **Antrenare model**
  - Sortarea populatiei se realizeaza in **O**(DIM\_POPULATIE\*log(DIM\_POPULATIE)\*DIM\_CROMOZOM)
  - Alegerea celor mai buni parinti pentru incrucisare se realizeaza in **θ**(DIM\_POPULATIE)
  - Incrucisarea parintilor alesi se realizeaza in **θ**(DIM\_POPULATIE\*DIM\_POPULATIE\*DIM\_CROMOZOM)
  - Aplicarea mutatiei are timpul de executie DIM\_POPULATIE <= T(n) <= DIM\_POPULATIE\*DIM\_CROMOZOM, deci se realizeaza in **O**(DIM\_POPULATIE\*DIM\_CROMOZOM)
  - Ordonarea si alegerea celor mai buni o suta de indivizi se realizeaza in **O**(DIM\_POPULATIE\*log(DIM\_POPULATIE)\*DIM\_CROMOZOM)

**Toate operatiile de mai sus** se executa de un numar variabil de ori, dat de viteza convergentei metodei. Cum solutia are un caracter stohastic, vom nota timpul maxim de executie al operatiilor de mai sus cu **TOTAL\_STEPS.**

**Complexitatea unui pas de antrenare** este in final **O**(DIM\_POPULATIE\*DIM\_POPULATIE\*DIM\_CROMOZOM), deoarece intalnim atat complexitati de caz mediu, cat si de caz defavorabil.

In final, **complexitatea algoritmului de antrenare** este O(TOTAL\_STEPS\*DIM\_POPULATIE\*DIM\_POPULATIE\*DIM\_CROMOZOM).

4. **Demonstrarea complexitatii**

O verificare a corectitudinii se poate realiza prin metode experimentale, generand seturi aleatoare de populatii si aplicand modelul de antrenare pe ele. In acest sens, am salvat datele din timpul antrenarii modelului, asa cum se poate vedea in exemplul de mai jos.
```
Current gen: 1 | Best fitness: -45.455 | Execution time: 0.01s 
Current gen: 2 | Best fitness: -39.7433 | Execution time: 0.008s 
Current gen: 3 | Best fitness: -39.7433 | Execution time: 0.007s 
Current gen: 4 | Best fitness: -32.0403 | Execution time: 0.006s 
Current gen: 5 | Best fitness: -30.6515 | Execution time: 0.006s 
Current gen: 6 | Best fitness: -23.3871 | Execution time: 0.006s 
Current gen: 7 | Best fitness: -23.3871 | Execution time: 0.005s

[...]

Current gen: 3970 | Best fitness: -0.000579898 | Execution time: 0.003s 
Current gen: 3971 | Best fitness: -0.000579898 | Execution time: 0.003s 
Current gen: 3972 | Best fitness: -7.60836e-05 | Execution time: 0.003s 

Best individual = [ 2.54518e-05 -0.000353162 -0.000509552 1.02863e-05 2.31899e-05 ]
Total execution time: 11.9551s
```

O posibila idee de demonstrare a corectitudinii implica analizarea functiei ce se doreste a fi minimizata. Se verifica faptul ca pentru functia aleasa, minimul se atinge in intervalul [-5.12, 5.12] pentru x0 = 0, valoare in care functia este nula. Prin analizarea derivatelor partiale, se poate identifica multimea punctelor critice, apoi folosind matricea hessiana se poate determina punctul de minim.

Alegerea valorilor pentru cromozomi s-a facut folosind o distributie normala, cu media 0 si deviatia standard 5.12. Prin urmare, intervalul de valori generate asigura ca punctele se afla in vecinatatea punctului de minim.

De asemenea, se poate arata ca la fiecare pas, cel mai bun individ va contine cvintuplul [x1, x2, x3, x4, x5] care ofera cea mai mica valoare pentru functia ce se doreste a fi minimizata. Cum distributia normala este centrata in 0, valoarea 0 are probabilitatea cea mai mare de aparitie, asadar mutatia va produce la un moment dat valori de 0 printre genele individului.

In concluzie, in urma aplicarii algoritmului de un numar variabil de ori, genele celui mai bine adaptat individ vor tinde catre 0.
