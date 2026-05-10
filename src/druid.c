/*
** EPITECH PROJECT, 2026
** omar
** File description:
** druid.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "../include/my.h"

static void refill_pot(context_t *ctx, int remaining)
{
    int idx = 0;

    printf("Druid: Ah! Yes, yes, I'm awake! Working on it! Beware I can "
        "only make %d more refills after this one.\n", remaining);
    ctx->pot->servings = ctx->cfg.pot;
    while (idx < ctx->pot->waiting) {
        sem_post(&ctx->pot->s_vills);
        idx++;
    }
}

void *druid(void *arg)
{
    context_t *ctx = (context_t *)arg;
    int count = 0;

    printf("Druid: I'm ready... but sleepy...\n");
    while (count < ctx->cfg.refills) {
        sem_wait(&ctx->pot->s_druid);
        if (ctx->pot->done)
            break;
        pthread_mutex_lock(&ctx->pot->mtx);
        refill_pot(ctx, ctx->cfg.refills - count - 1);
        pthread_mutex_unlock(&ctx->pot->mtx);
        count++;
    }
    printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
    return NULL;
}
