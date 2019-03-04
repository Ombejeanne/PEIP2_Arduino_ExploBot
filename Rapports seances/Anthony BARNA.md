# Rapports de séance - Anthony BARNA

## Informations

* Toutes les images sont rangées dans 'documents/images'.
* Les caractéristiques détaillées des composants du projet sont rangées dans 'documents/specs.md'
* Tous les algorithmes sont rangés dans 'documents/codes'

## Compte rendu de la séance du 10 décembre 2018 :

* Notre groupe de projet est composé de Michele BONA et de Anthony BARNA (moi-même). Nous nous sommes déjà mis d’accord sur l’idée du projet, l’ExploBot.

* Nous créons aujourd’hui le GitHub de notre projet. Nous faisons également des recherches pour pouvoir créer un cahier des charges cohérent avec les circonstances et nos besoins.

* Personnellement, mes recherches sont axées sur la caméra IP et la manette permettant de contrôler l’ExploBot.

* Je soude des câbles sur une manette de Playstation 2 (Bigben) pour pouvoir l’utiliser avec l’arduino. Malheureusement cette dernière est défectueuse: j'utilise la librairie PS2X_lib.h disponible dans documents/codes, avec un exemple d'utilisation PS2X_Example.ino. Une fois les branchements effectués la librairie ne reconnaît pas le type de manette et de plus, il y a trop peu de documentation et de plans sur cette dernière pour pouvoir résoudre le problème. J’en commande donc une nouvelle (Dualshock) qui sera conforme et bien plus documentée/utilisée.

![alt text](https://raw.githubusercontent.com/MicheleBona/PEIP2_Arduino_ExploBot/master/documents/images/soudure2.jpg)

## Compte rendu de la séance du 17 décembre 2018 :

* Je fais des recherches sur les moteurs et le phare que nous allons commander.

* En attente de la livraison de la manette, je m'occupe de la gestion du servomoteur qui, servira à orienter notamment la caméra et le phare de l'ExploBot, le modèle choisi est le MG 996R de Tower Pro (cf 'documents/specs.md').
Il sera temporairement commandé à l'aide d'un potentiomètre 5K.

![alt text](https://raw.githubusercontent.com/MicheleBona/PEIP2_Arduino_ExploBot/master/documents/images/servo1.jpg)

* Nous récupérons un dispositif permettant la gestion de deux moteurs et du phare de l'ExploBot : le L298N, un double pont en H tableau de commande d'entraînement de moteur à courant continu (cf 'documents/specs.md').

* Commande d'une lampe LED pour faire le phare de l'ExploBot.

## Compte rendu de la séance du 7 janvier 2019 :

* Je fais des recherches avec Michele sur les moteurs, chassis et chenilles. Nous finissons par opter pour un kit préfait, les détails sont sur le rapport de Michele.

* Je mets au point le code et les branchements du capteur de distance à ultrasons positionné sur le servomoteur, i lservira à scanner les environs pour rendre un graphique en 2D.

* Je reçois la manette conforme, je fais les branchements et soudures nécessaires : 

![alt text](https://raw.githubusercontent.com/MicheleBona/PEIP2_Arduino_ExploBot/master/documents/images/branchement%20manette.jpg)

* Ainsi il faut brancher sur l'Arduino deux cables de commande qui communiquent entre la manette et les pins numériques, un cable qui correspondra à l'horloge, un qui va donner des informations sur les paquets de bytes envoyés et pour finir l'alimentation en 3.3V et la masse.

* Pour finir je mets au point le code pour gérer les commandes, qui sera à terminer et à optimiser sur les séances à venir. Je me sers de la librairie PS2X disponible sur le GitHub.


## Compte rendu séance du 14 janvier 2019

* La manette est enfin fonctionelle: j'ai étudié la librairie PS2X pour comprendre le fonctionnement du code. J'ai aussi passé les cables de la manette à l'oscilloscope :
![alt text](https://raw.githubusercontent.com/MicheleBona/PEIP2_Arduino_ExploBot/master/documents/images/oscilloscope%201.jpg)
Cela donne des informations, notamment sur la manière dont sont transmis les paquets d'informations (à quelle fréquence, en fonction de quoi..).

* En conclusion, la manette utilise une liaison Serial Peripheral Interface (SPI) où elle se comporte comme un slave et la carte arduino comme le master comme l'explique ce schéma : 
![alt text](https://raw.githubusercontent.com/MicheleBona/PEIP2_Arduino_ExploBot/master/documents/images/SPI.png)

* Il y a quatre fils connectés entre la manette et l'arduino: deux servent à l'échange de données entre l'arduino et la manette (MOSI et MISO), un sert pour l'horloge (SCK) et le dernier est le slave selecter (SS). 

* Au démarrage, la manette envoie une 'signature' qui permettra de l'identifier, ensuite l'arduino impose une cadence de transfert de données puis des paquets de bytes se transmettent en suivant la cadence de l'horloge (le slave selecter va se mettre en valeur logique basse avant chaque réception de paquet). Ensuite, en analysant les bytes reçus (mis sous forme hexadécimale), on peut déterminer quelle commande a été actionnée. En ce qui concerne les joysticks analogiques, chaque axe d'un joystick renvoie des valeurs comprises entre 0 et 255 en fonction de sa position. Donc au repos les 4 axes (pour les deux joysticks) renvoie chacun la valeur 128. Cela permettra de contrôler les moteurs de manière précise.

* Pour finir j'ai créé le code qui fait fonctionner le servomoteur avec la manette ainsi que la LED haute puissance, la vidéo est disponible [ici](https://youtu.be/iUmSV24hpvE). Je travaille maintenant sur la caméra IP pour pouvoir l'intégrer sur un support avec la LED, sur le servomoteur.

* Le code sera régulièrement mis à jour dans le GitHub.

## Compte rendu séance du 4 février 2019

* Nous recevons le colis tant attendu : le chassis du char, les moteurs, les chenilles.. Nous pouvons enfin mettre notre travail en commun. 

* Je commence les branchements des moteurs pour les faire marcher avec les josticks analogiques de la manette de PS2. 

![alt text](https://scontent-mrs1-1.xx.fbcdn.net/v/t1.15752-9/51150461_392252168194172_1247527384890998784_n.jpg?_nc_cat=101&_nc_ht=scontent-mrs1-1.xx&oh=b534cfb33e1a8cf85e95a14a7493b954&oe=5CED568A)

* Pendant ce temps, Michele monte le 'char', les moteurs seront disposés comme ceci: 

![alt text](https://scontent-mrs1-1.xx.fbcdn.net/v/t1.15752-9/51178873_243762909885456_5320521704357756928_n.jpg?_nc_cat=101&_nc_ht=scontent-mrs1-1.xx&oh=ae04c628d8f99c4bcb07c0931f5c2388&oe=5CF20671)

* Il y a encore un petit problème au niveau du moteur qui ne délivre pas sa pleine puissance, mais pour le reste, tout semble avancer de manière rassurante.

* Cette séance a été en grande partie une séance de montage électronique et mécanique, il reste maintenant le code à développer entièrement pour pouvoir manier l'Explobot au mieux.

## Compte rendu séance du 11 février 2019

* Cette séance est entièrement dédiée au code de l'Explobot. Michele me donne sa partie de code concernant les moteurs que j'intègre au code principal (disponible dans le GitHub, régulièrement mis à jour) pour qu'il fonctionne avec la manette. Pour mieux comprendre mon travail, voici un schéma de ce que renvoie un jostick :

![alt text](https://raw.githubusercontent.com/MicheleBona/PEIP2_Arduino_ExploBot/master/documents/images/sch%C3%A9maJoystick.png)

* Ici l'axe X est bleu et l'axe Y est rouge, si on ne touche pas le jostick, les deux axes renvoient 128.

* Le jostick droit sert à donner l'intensité au moteur, celui de gauche sert à donner la direction.

* Le code fonctionne correctement. En attendant une dernière retouche sur le chassis (fixation d'axe moteur) je commence à prévoir l'agencement du montage (cable management, vis, écrous, éventuelle plaque de bois..).

* Nous pourrons commencer à monter l'ExploBot concrètement dès la prochaine séance.

## Compte rendu séance du 25 février 2019

* Aujourd'hui nous montons en partie l'ExploBot. Nous faisons des soudures, les finitions du code, le cable managment.. 

* Voici une courte [vidéo](https://l.facebook.com/l.php?u=https%3A%2F%2Fyoutu.be%2FKJUN-Gob8qw%3Ffbclid%3DIwAR1eGpQI2xFTQnhV1hlKM3nVFsLNu5_y9kutA6KZit-YHbofoGitM4g1mTw&h=AT2WfpAzhRxiHpDFNaCvjarttAML4TCD_0FxaemhZ1p-elKtKIgg1dm8Zp7bAd5aKo6JU0BSAc7wL_DCew_vSds-qBg9rdrCWuCCYfXlStw5wVy5HbCvTjzUn4ci0A) qui montre l'avancement (le montage reste expérimental). 

* Il reste maintenant à finir de monter proprement les câbles et à créer les supports pour les différentes pièces (les cartes électroniques ne doivent pas avoir de contact direct avec le chassis pour éviter les courts circuits, un support pour le servomoteur, la caméra et la LED haute puissance qui sera de préférence en PVC).

## Compte rendu séance du 4 mars 2019

* Nous découpons et fixons le support final de l'ExploBot où sont fixés tous les autres composants.

* Nous mettons l'ExploBot sur batterie pour plus d'autonomie.

* Nous aménageons les câbles au mieux.

* Nous avons fait fonctionner la caméra IP, les images sont réceptionnées sur mon smartphone.

* Voici une courte [vidéo](https://youtu.be/Llfrzw-GikU) qui montre l'avancement du projet : 
