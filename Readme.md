# Utilisation de l'API Task #

## Introduction ##

L'API Task est utilisée pour réaliser une succession de
fonctions de façon asynchrone et multi-threadée.
Le système fonctionne à partir d'une file de tâches à laquelle
on ajoute des structures contenants les infos pour réaliser la
fonction à accomplir (un pointeur sur cette fonction et ses
paramètres notamment).

## Utilisation dans un programme ##

Dans le main du programme qui utilisera l'API Task, il faut :
*   Inclure le .h de l'API situé dans le dossier include
*   Lancer le gestionnaire de tâches
*   Ajouter une ou plusieurs tâches
*   Arréter le gestionnaire des tâches

##  Creation de nouvelles tâches ##

Pour créer une nouvelle tâche et étendre l'API, il faut :
*   dans un fichier .c dont le nom termine par Task :
    *   inclure le .h de l'API + les autres tâches utiles
    *   une structure contenant les infos persos à passer à la fonction
    *   une fonction pour créer la tâche à ajouter dans la file
    *   la fonction de la tâche
    *   eventuellement ajouter une nouvelle tâche à la liste
    *   libérer la structure allouée pour les infos
*   dans un fichier .h de même nom :
    *   les prototypes des fonctions afin de pouvoir être appelé dans une autre tâche ou un main

## Exemple ##

Un programme d'exemple est fourni. Pour l'essayer :
`make` à la racine du projet puis `cd sample && make`.
`./sample/sample` pour l'exécuter.
