# Project eInk Lib
*Projet d'Informatique Industrielle mené par Rida LALI dans le cadre du module 441-ENS du M1 E3A*

*Utilisation de la carte LPC804 pour implémenté un système embarqué utilisant divers connexions*

Ce projet a pour but de réinvestir un maximum de connaissances du cours d'Informatique Industrielle dans le but de faire un système embarqué utilisant un écran eInk, un module bluetooth, une horloge en temps réel ainsi que des outils de commande.

Ce README fait une review de ce que contient le projet à l'heure actuelle.

## Module bluetooth BTBM78

Un module bluetooth (modèle Bluetooth Microchip BM78) est utilisé. Ce dernier communique via une liaison série avec le controlleur.

Les fonctions implémentées sont dans le fichier "serie_bluetooth.(c/h)". 

Dans ce projet, le module permet de pouvoir paramétrer à distance le controlleur (par exemple via un smartphone).

## Horloge temps-reel DS1307

Une horloge temps-réel est utilisé dans ce projet. Cette dernière est reliée en liaison I2C au micro-controlleur.

Les fonctions implémentées sont dans le fichier "i2c_clock.(c/h)".

Dans ce projet, le module permet de gérer une horloge en la configurant basiquement puis en consultant l'heure en envoyant et en décodant les trames envoyées via la liaison I2C.

### Configuration d'une sonnerie

L'horloge permet de pouvoir configurer une sonnerie qui sonne (sur le code, il s'agit d'une sonnerie périodique toutes les 30 secondes, mais cela peut être réglé comme un réveil).

La sonnerie utilise le MRT et la fréquence peut être réglable via le menu.

## L'échec d'un écran eInk

Le projet se repose aussi sur l'utilisation d'un écran eInk. Cependant, malgré le temps passé à chercher sur Internet une bibliothèque permettant d'utiliser plus facilement l'écran eInk, le seul guide trouvé -et pertinant pour le projet- est le manuel d'utilisateur, permettant de bien configurer la liaison SPI et de savoir les bits qu'il faut envoyer pour afficher.

Le problème est le temps que prend l'implémentation l'affichage caractère par caractère, l'écran étant un afficheur qui est géré par l'allumage ou l'extinction d'un pixel et non, comme un écran LCD, où chaque caractère à sa forme pré-enregistrée dans la mémoire.

### Le module bluetooth, un moyen de secours

Face à cet échec, afin d'afficher un menu sans avoir recours à l'écran LCD, j'ai utilisé le module bluetooth afin de faire afficher sur l'écran du terminal le menu ainsi que les paramètres lorsqu'il faut régler la fréquence de la sonnerie où afficher l'heure (et la date) en direct.

## Conclusion et Leçons tirées

Ce projet m'a permis de réinvestir un maximum de connaissances (voire d'améliorer ce qui a pu être pas/mal compris durant le suivi de l'UE) et d'entrer plus en profondeur d'une part dans la structuration du projet (séparation des différents modules en plusieurs fichiers) et d'autre part dans la lecture du manuel utilisateur et datasheet que ce soit de la LPC804 mais aussi dans le module Bluetooth ainsi que l'horloge en Temps-Réel.
 
Bien que le module d'écran eInk n'a pas été implémenté, j'ai tout de même recherché que ce soit sur Internet pour comprendre les modules utilisés et décortiquer le manuel utilisateur lié à l'écran ou bien dans le manuel utilisateur de la LPC804 pour comprendre comment fonctionne la liaison SPI.

Afin d'améliorer le projet, on pourrait essayer d'améliorer la gestion de la liaison I2C (en effet, l'utilisation de cette liaison par l'horloge empêche le bon fonctionnement de l'écran LCD, notamment pour la commande lcd_position), et on peut essayer de recréer tout un module d'affichage pour l'écran eInk en essayant de limiter l'occupation de la mémoire.
