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
-Implémenter classe morse
-Rédiger documentation
-Faire une série de test
-Faire une interface utilisateur
-Rajouter de la souplesse si jamais les échantillon sont codés sur plusieurs octets
-Refaire la création du namespace et la gestion des dicos
-Gérer les majuscules et autres caractères (espaces)
-Problème taille de l'entête
-Faire du beau son
-Intégrer l'ouverture et la fermeture de fichier dans les constructeurs et destructeurs
-En morse : 1 espace = séparation inter-caracrères / 3 espaces = séparation inter-mots
-Générer un son avec un sinus (signal "propre")
-Données de l'entête à mettre dans une classe fille

### QUESTIONS

-Comment indiquer un retour de fonction de type array ?
-Conversion string vers entier ?
-Obliger de lire des char ?
-Lecture .WAV ?
-Créer un namespace ?
-Qu'est-ce que la commande "reinterpret_cast" ?
-Pointeur type possible pour souplesse d'écriture ?