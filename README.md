Génération du code en "Release"
```ssh
mkdir Release
cd Release
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j4

```

### TO DO LIST

-Implémenter classe audio
-Tester traitement .wav
-Trouver une structure pour graphes
-Implémenter classe fr
-Implémenter classe morse
-Rédiger documentation
-Faire une série de test
-Faire une interface utilisateur
-Extraction tailles des données à refaire
-rajouter de la souplesse si jamais les échantillon sont codés sur plusieurs octets

### QUESTIONS

-Comment indiquer un retour de fonction de type array ?
-Conversion string vers entier ?
-Obliger de lire des char ?
-Lecture .WAV ???