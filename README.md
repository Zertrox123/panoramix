# Panoramix

Modélisation et résolution du problème de synchronisation concurrentielle en C.

## Présentation

Projet de programmation système concurrente (G-CCP-400) simulant les interactions entre des villageois (threads consommateurs) et un druide (thread producteur) autour d'une marmite partagée.

Notions clés :
- Synchronisation stricte par sémaphores POSIX et mutexes.
- Prévention totale des interblocages (*deadlocks*) et des famines de ressources (*starvation*).
- Gestion propre de l'arrêt des threads en fin de scénario.

## Prérequis

- GCC
- Make

## Compilation et Lancement

```bash
# Compiler le programme
make

# Lancer la simulation : ./panoramix <nb_villageois> <taille_marmite> <nb_combats> <nb_recharges>
./panoramix 3 5 2 3
```
