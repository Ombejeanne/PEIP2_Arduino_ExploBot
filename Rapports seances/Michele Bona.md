# Rapport Projet – Michele Bona

## 10/12/2018 – Premier jour :


* Notre groupe de projet est constitué de Michele Bona et Anthony Barna et on a aujourd’hui confirmé que notre projet sera l’ExploBot, une voiture « tout-terrain » (dans la mesure du possible) étudié pour explorer des grottes, des couloirs, les pyramides (avec lumières, caméra, détection d’obstacles, et autres à préciser plus tard).

* Je crée notre compte GitHub et lit le guide en ligne(https://guides.github.com/activities/hello-world/) pour bien comprendre comment on va s’organiser et on a récupéré une manette d’un ancien projet qui nous servira à diriger notre robot. Il faut par contre d’abord qu’on étudie comment elle marche, on a donc coupé et ressoudé les câbles de la manette qu’Anthony branchera sur sa carte Arduino pour étudier son fonctionnement.

![Soudage cables, cf documents/images/ima.jpg](documents/images/ima.jpg)
  
* Je fais des recherches sur le moteur dont on aura besoin selon le poids de notre robot, en effet on veut ajouter de nombreuses fonctionnalités à notre robot dont on n’a pas encore défini certaines donc on ne connait pas encore son poids et on doit commencer à étudier les puissances de moteurs dont on pourrait avoir besoin :

1. On s’est mit d’accord pour rester sur une base de 3 « fonctionnalités » (toutes dirigeables avec un servomoteur) : une caméra, de la lumière et un capteur de distance/d’obstacle.

2. J’ai cherché sur robotshop.com un outil de dimensionnement de moteur : https://www.robotshop.com/community/blog/show/dimensionnement-dun-moteur-dentranement
Je verrais la prochaine fois la dimension necessaire.

* Je fais notre cahier des charges avec un tableau excel, je fais les recherches pour voir ce dont j'aurais besoin pour le support et le moteur de la voiture et je vois combien de temps chaque élément du projet va prendre et je le rajoute au CDC au fur et à mesure.


## 17/12/2018 - Deuxième jour:


* J'ai été malade toute la semaine du 17 et est donc fait mes recherches pendant les vacances et ai perdu mon cahier des charges que j'ai donc refait.

* J'ai choisi les caracteristiques des moteurs nécessaire pour faire tourner nos roues en partant de l'idée que notre robot peserai au grand maximum 1kg (sachant que le servo pèse 55g, une pile de 12V environ 150g et en m'insiprant d'autres projets similaires). On cherche de plus à avoir un vehicule tout terrain, donc on sacrifie la vitesse maximale que j'ai estimé à 0.8 m/s et je choisi un assez grand rayon de roue (4cm). Et en prenant en plus en compte le fait  qu'on a 2 moteurs d'entrainement l'outil de dimensionnement de robotshop nous conseille un moteur avec un couplage de 0.1 Nm et de 2.2 W, ce qui me semble peu mais on peut dire que c'est un minimum et que plus de couplage ne nous fera pas de mal pour gravir des terrain compliqués.

![Caractéristiques du moteur, cf documents/images/carac_moteur.png](documents/images/carac_moteur.png)

* Pour les roues on veut des chenilles donc j'ai décidé de choisir 6 roues crantées de diamètre 4cm mais j'ai constaté qu'il faut que je sache la taille de l'axe moteur avant pour les choisir. Donc la semaine prochaine je vais commander les pièces nécessaires pour pouvoir choisir les dimensions du reste, l'ordre de choix est donc le suivant: moteur > axe moteur > roue crentées > batteries > toutes les pieces > chassis
