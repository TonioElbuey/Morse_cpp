Génération du code en "Release"
```ssh
mkdir Release
cd Release
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j4

```

### TO DO LIST

-Tester traitement .wav
-Rédiger documentation
-Faire une série de test
-Faire une interface utilisateur
-Intégrer l'ouverture et la fermeture de fichier dans les constructeurs et destructeurs
-En morse : 1 espace = séparation inter-caracrères / 3 espaces = séparation inter-mots
-Générer un son avec un sinus (signal "propre")
-Durées :
    dot_duration : quelconque
    dash_duration = 3*_dot_duration
    intra_letter_duration : quelconque
    inter_letter_duration = 3*_intra_letter_duration
    inter_word_duration = 7*_intra_letter_duration

### QUESTIONS

-Comment indiquer un retour de fonction de type array ?
-Conversion string vers entier ?
-Obliger de lire des char ?
-Lecture .WAV ?
-Créer un namespace ?
-Qu'est-ce que la commande "reinterpret_cast" ?
-Pointeur type possible pour souplesse d'écriture ?