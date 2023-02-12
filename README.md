# ANT 3000
## Projet réalisé par Loan ALOUACHE et Alexis HESLOUIN
Ce projet est une simulation d'exploration de terrain par des fourmis. Celles-ci doivent trouver de la nourriture sur un plateau inconnu et la rapporter à la colonie.

Des fourmis hostiles parcourent également le plateau, tentant de nuire à la colonie en volant nourriture et larves.

---

## Installation du projet
- Lancer le projet avec CLion, configuré pour compiler à l'aide du fichier CMakeList.txt
- Télécharger la librairie SFML (https://www.sfml-dev.org/download/sfml/2.5.1/), placer le dossier SFML à la racine du projet et le nommer "SFML".

**Exemple d'architecture du projet final**
```
.
├── assets
├── includes
├── SFML
│   ├── include
│   ├── lib
│   └── share
└── src
```

## Lecture statistiques
Le fichier de statistiques est créé automatiquement **à la fin** de la simulation. Si exécuté avec CLion, il se trouvera dans le dossier cmake-build-debug/stats.dat.

Pour exploiter ce fichier avec GNUPlot, se placer à la racine du projet :
```
gnuplot -c stats_script -p
```