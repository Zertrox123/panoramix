/*
** EPITECH PROJECT, 2026
** omar
** File description:
** village.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "../include/my.h"

static void drink_potion(context_t *ctx, int my_id)
{
    pthread_mutex_lock(&ctx->pot->mtx);
    printf("Villager %d: I need a drink... I see %d servings left.\n",
        my_id, ctx->pot->servings);
    while (ctx->pot->servings == 0) {
        if (ctx->pot->waiting == 0) {
            printf("Villager %d: Hey Pano wake up! "
                "We need more potion.\n", my_id);
            sem_post(&ctx->pot->s_druid);
        }
        ctx->pot->waiting++;
        pthread_mutex_unlock(&ctx->pot->mtx);
        sem_wait(&ctx->pot->s_vills);
        pthread_mutex_lock(&ctx->pot->mtx);
        ctx->pot->waiting--;
    }
    ctx->pot->servings--;
    pthread_mutex_unlock(&ctx->pot->mtx);
}

void *villager(void *arg)
{
    villager_arg_t *info = (villager_arg_t *)arg;
    context_t *ctx = info->ctx;
    int my_id = info->id;
    int f = 0;

    free(info);
    printf("Villager %d: Going into battle!\n", my_id);
    while (f < ctx->cfg.fights) {
        drink_potion(ctx, my_id);
        printf("Villager %d: Take that roman scum! Only %d left.\n",
            my_id, ctx->cfg.fights - f - 1);
        f++;
    }
    printf("Villager %d: I'm going to sleep now.\n", my_id);
    return NULL;
}
