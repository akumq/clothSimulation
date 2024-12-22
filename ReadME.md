# Simulation de Tissu

Une simulation de tissu interactive utilisant SFML et la méthode d'intégration de Verlet.

## Description

Ce projet implémente une simulation de tissu en 2D avec les caractéristiques suivantes :
- Simulation physique basée sur l'intégration de Verlet
- Grille de particules interconnectées par des contraintes
- Interaction utilisateur pour couper le tissu
- Collision avec les bords de la fenêtre
- Points d'ancrage configurables

## Prérequis

- CMake (version 3.10 minimum)
- SFML 2.5
- Compilateur C++ supportant C++11

## Installation

1. Clonez le dépôt :

```bash
git clone [url-du-repo]
```

2. Créez un répertoire de build :

```bash
cd clothSimulation
```

3. Générez le projet avec CMake :

```bash
cmake .
make
./clothSimulation
```

ou 

```bash
sh launch.sh
```

## Utilisation

- Utilisez les flèches haut et bas pour ajuster le rayon de coupe.
- Cliquez sur le bouton gauche de la souris pour couper le tissu.
- Appuyez sur la touche R pour réinitialiser la simulation.

## Remarques

- Le rayon de coupe est initialement de 10 pixels.
- La simulation est initialisée avec une grille de 100x100 particules.
- Les particules sont initialement ancrées à la première ligne.
- La simulation est limitée à 60 FPS pour des raisons de performance.


## Fonctionnement

La simulation utilise :
- Des particules (classe `Particle`) pour représenter les points du tissu
- Des contraintes (classe `Constraint`) pour maintenir les distances entre les particules
- L'intégration de Verlet pour la simulation physique
- Une grille de 100x100 particules par défaut

## Licence

[Licence](Licence)