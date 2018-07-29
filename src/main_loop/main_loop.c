#include "main_loop.h"
#include "../events/events.h"

void EMSCRIPTEN_KEEPALIVE mainloop(void *arg) {
    context *ctx = (context *) arg;
    SDL_Renderer *renderer = ctx->renderer;

    // check for events
    checkEvents();

    // black background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    SDL_Rect *r = (SDL_Rect *) malloc(sizeof(SDL_Rect));
    r->w = getSquareWidth();
    r->h = getSquareWidth();
    r->x = getXCoord(ctx, r);
    r->y = getYCoord(ctx, r);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255 );
    SDL_RenderCopy(renderer, ctx->texture, r, r);
    SDL_RenderPresent(renderer);
    free(r);
}

int getSquareWidth() {
    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);
    if(dm.w < 400) {
        return 25;
    }
    if(dm.w > 400 && dm.w < 1000) {
        return 75;
    }
    return 400;
}

int EMSCRIPTEN_KEEPALIVE getXCoord(context *ctx, SDL_Rect *r) {
    int xCoord = 0;
    if(ctx->x == 0) {
        ctx->leftRight = 0;
        emscripten_log(0, "Going right");
    }
    if(ctx->x == WIDTH - r->w) {
        ctx->leftRight = 1;
        emscripten_log(0, "Going left");
    }
    if(!ctx->leftRight) {
        xCoord = ctx->x + 2;
        ctx->x++;
    } else {
        xCoord = ctx->x - 2;
        ctx->x--;
    }
    return xCoord;
}

int EMSCRIPTEN_KEEPALIVE getYCoord(context *ctx, SDL_Rect *r) {
    int yCoord = 0;
    if(ctx->y == 0) {
        ctx->upDown = 0;
        emscripten_log(0, "Going down");
    }
    if(ctx->y == HEIGHT - r->h) {
        ctx->upDown = 1;
        emscripten_log(0, "Going up");
    }
    if(!ctx->upDown) {
        yCoord = ctx->y + 2;
        ctx->y++;
    } else {
        yCoord = ctx->y - 2;
        ctx->y--;
    }
    return yCoord;
}