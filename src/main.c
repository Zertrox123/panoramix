/*
** EPITECH PROJECT, 2026
** omar
** File description:
** main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "../include/my.h"

static void init_pot(pot_t *pot, int servings)
{
    pot->servings = servings;
    pot->done = 0;
    pot->waiting = 0;
    pthread_mutex_init(&pot->mtx, NULL);
    sem_init(&pot->s_druid, 0, 0);
    sem_init(&pot->s_vills, 0, 0);
}

static void join_threads(context_t *ctx, pthread_t *v_ids, pthread_t d_id)
{
    int i = 0;

    while (i < ctx->cfg.n_v) {
        pthread_join(v_ids[i], NULL);
        i++;
    }
    ctx->pot->done = 1;
    sem_post(&ctx->pot->s_druid);
    pthread_join(d_id, NULL);
    free(v_ids);
}

static void run_simulation(context_t *ctx)
{
    pthread_t d_id;
    pthread_t *v_ids = malloc(sizeof(pthread_t) * ctx->cfg.n_v);
    villager_arg_t *v;
    int x = 0;

    pthread_create(&d_id, NULL, druid, ctx);
    while (x < ctx->cfg.n_v) {
        v = malloc(sizeof(villager_arg_t));
        v->ctx = ctx;
        v->id = x;
        pthread_create(&v_ids[x], NULL, villager, v);
        x++;
    }
    join_threads(ctx, v_ids, d_id);
}

static int check_args(int ac, char **av, config_t *cfg)
{
    if (ac != 5) {
        printf("USAGE: ./panoramix <nb_villagers> <pot_size> "
            "<nb_fights> <nb_refills>\n");
        return 84;
    }
    cfg->n_v = atoi(av[1]);
    cfg->pot = atoi(av[2]);
    cfg->fights = atoi(av[3]);
    cfg->refills = atoi(av[4]);
    if (cfg->n_v <= 0 || cfg->pot <= 0 || cfg->fights <= 0 ||
        cfg->refills <= 0) {
        printf("USAGE: ./panoramix <nb_villagers> <pot_size> "
            "<nb_fights> <nb_refills>\nValues must be >0.\n");
        return 84;
    }
    return 0;
}

int main(int ac, char **av)
{
    pot_t pot;
    config_t cfg;
    context_t ctx;

    if (check_args(ac, av, &cfg) == 84)
        return 84;
    init_pot(&pot, cfg.pot);
    ctx.cfg = cfg;
    ctx.pot = &pot;
    run_simulation(&ctx);
    return 0;
}
