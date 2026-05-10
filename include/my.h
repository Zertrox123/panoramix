/*
** EPITECH PROJECT, 2024
** omar
** File description:
** my.h
*/

#ifndef MY_H
    #define MY_H

typedef struct {
    int n_v;
    int pot;
    int fights;
    int refills;
} config_t;

typedef struct {
    int servings;
    int done;
    int waiting;
    pthread_mutex_t mtx;
    sem_t s_druid;
    sem_t s_vills;
} pot_t;

typedef struct {
    config_t cfg;
    pot_t *pot;
} context_t;

typedef struct {
    context_t *ctx;
    int id;
} villager_arg_t;

void *druid(void *arg);
void *villager(void *arg);

#endif /* MY_H */
