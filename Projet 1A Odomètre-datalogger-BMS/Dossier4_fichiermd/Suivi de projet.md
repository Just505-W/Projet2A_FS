# Suivi de Projet
Le but de cette section est de résumer les avancées du projet jour par jour.\
Voici un exemple de présentation : 
## Date 
 - **NOM Prénom** : 

 modification/recherche apportée

## 05 Février 2026
- **WOELFFEL Justine** :

Notes de début de séance : https://docs.google.com/document/d/1G-7Qv987tz_3XtQDTyCQzI4an9IfghzEJT-DvZPg25M/edit?usp=sharing

## 11 Février 2026
- **WOELFFEL Justine** :

Affectation des composants : 
- Condensateur : d'après la datasheet on doit prendre les condensateur en céramique, c'est à dire non-polarisé (- ChatGPT). Ces condensateurs sont les plus classiques donc on ne prend pas trop de risque 

ChatGPT donne une liste de composant : Capacitor_SMD:C_0603, Capacitor_SMD:C_0805 et Capacitor_SMD:C_1206    

Le plus utilisé est le 0805 **de plus** d'après le TD Projet ce sont celles qu'on a utilisée
    
On prend donc : **Capacitor_SMD:C_0603** 
    
- Mountingholes : on utilise les même qu'en TD
    
- Resistances et LED : tout en 0603 HandSolder comme vu en TD
    
- STM : Originellement on avait 
    
STM32C092FCP6 : SOP65P640X120-20N
    
Pour trouver l'affectation on a va p.120 (Ordering information) de la DataSheet pour regarder : STM32C092**FCP**6

![image1](https://github.com/Just505-W/Projet1A_FS/blob/main/Image/image1.png)

On peut donc mettre comme affectation : Package_SO:TSSOP-20_4.4x6.5mm_P0.65mm

- Bouton poussoir : ChatGPT

## 12 Février 2026

- **NOICI Amélie** :

Finalisation du schéma kikad, rajout d'un deuxième régulateur de tension car problème de tension d'entrée:
![image1](https://github.com/Just505-W/Projet1A_FS/blob/main/Image/Datalogger_kikad_final_sch.png)

## 19 Février
- **Avancement global**

<ins> Datalogger</ins> (Amélie, Joseph, Aïssa): Le PCB est agencé, on doit encore vérifier certaines empreintes, on a trouvé les boutons au labo (on les a réservés), le routage est en cours. Les empreintes en commun avec le groupes d'Alain on été choisies (Le groupe d'Alain s'adaptera au notre)  
Seule note d'Alain : choisir JST qui empêchent la deconnexion (JST AM - il me semble)  
On va surement réussir à commander avant les vancances

<ins> Odomètre</ins> (Bastien, Athénaïs): problème avec le routage et les empreintes, d'après Patricia il faut un bouton auquel on a du importé l'empreinte mais il y a des problèmes d'importations. Le routage n'est pas commencé.  
Peu probable de la commander avant vacances 

<ins> Achat</ins> (Arthur): fichier excels terminé, ils osnt sur GitHub, prêt à être envoyés 

<ins> Autre</ins> : Début de projet pour le gestionnaire de batterie 



## 12 Mars 2026
- **Avancement global**

On a reçu les PCB

L'entièreté de la séance à servi à rechercher les composants necessaires pour les PCB

On a commandé de nouveaux composants via le fichier excel

Pas de productivité optimale.



## 19 Mars 2026

On a reçu des composant mais aucun ne nous appartenaient.\
On a vaguement commencé le code.\
On doit également associer nos actions aux adresses CAN


## 26 Mars 2026

Certains composants reçus

Farnell\
~Processeur STM Odometre et GB : 4676916~ \
~Régulateur 5.0V : 2534281~\
~Connecteur carte SD : 1764374~\
~Processeur STM Datalogger : 2469549~ \
~Capteur à effet Hall : 1617405~\
~SD - DM3AT-SF-PEJM5 : 2427719~\
MicroSD 8Go : 759-925 

RS\
LED CMS : 466-3863 \
Tranceiver CAN : 799-0228 \
~Regulateur 3.3V : 197-7195P~ \
~Bargraph LED : 588-235~ 



## 2 Avril

Campus Day donc pas d'avancées


## 9 avril 2026

Soudage des dernier composants des cartes 

Coté Software : 
- début de programation de la carte SD poru le datalogger (Amélie)
- Début d'initialisation du bus can de l'odomètre (Bastien)


Test des cartes avec les générateurs : 
- odomètre : complation d'un programme simple pour tester les leds ==> vérifier le fonctionnement du PCB\\ l'odomètre fonctionne
- datalogger : chauffe anormalement, court circuit potentiel 


## 16 Avril 2026

But Arthur : finir la schématique du dernier PCB - BMS - (globalment similaire à l'odomètre en changeant 1 ou 2 composants)

Continuation des programmes odomètre/SD carte

Tentative de comprendre ce qui ne marche pas avec le datalogger (déssoudage, tests, etc...)












