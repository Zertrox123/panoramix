# Panoramix

Projet de concurrence en C (problème des philosophes / druide) pour gérer des threads consommateurs et producteurs autour d'une marmite commune.

Utilise des mutex et des sémaphores POSIX pour éviter les race conditions et les deadlocks.

## Build et lancement

```bash
make
./panoramix <nb_villageois> <taille_marmite> <nb_combats> <nb_recharges>
# Exemple :
./panoramix 3 5 2 3
```
