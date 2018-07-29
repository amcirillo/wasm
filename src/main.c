#include "main.h"

int getXCoord(context *ctx, SDL_Rect *r);
int getYCoord(context *ctx, SDL_Rect *r);

void mainloop(void *arg) {
    context *ctx = (context *) arg;
    SDL_Renderer *renderer = ctx->renderer;

    // black background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    SDL_Rect *r = (SDL_Rect *) malloc(sizeof(SDL_Rect));
    r->w = 400;
    r->h = 400;
    r->x = getXCoord(ctx, r);
    r->y = getYCoord(ctx, r);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255 );
    SDL_RenderCopy(renderer, ctx->texture, r, r);
    SDL_RenderPresent(renderer);
    free(r);
}

int getXCoord(context *ctx, SDL_Rect *r) {
    int xCoord = 0;
    if(ctx->x == 0) {
        ctx->leftRight = 0;
        printf("Going right\n");
    }
    if(ctx->x == WIDTH - r->w) {
        ctx->leftRight = 1;
        printf("Going left\n");
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

int getYCoord(context *ctx, SDL_Rect *r) {
    int yCoord = 0;
    if(ctx->y == 0) {
        ctx->upDown = 0;
        printf("Going down\n");
    }
    if(ctx->y == HEIGHT - r->h) {
        ctx->upDown = 1;
        printf("Going up\n");
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

int main() {
    printf("Hello World!\n");

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);

    context *ctx = (context *) malloc(sizeof(context));
    ctx->renderer = renderer;
    ctx->x = 0;
    ctx->y = 0;
    ctx->leftRight = 0;
    ctx->upDown = 0;

    SDL_Surface *surface = IMG_Load("resources/resort.jpg");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    ctx->texture = texture;
    printf("Texture created\n");
    const int simulate_infinite_loop = 1; // call the function repeatedly
    const int fps = -1; // call the function as fast as the browser wants to render (typically 60fps)
    emscripten_set_main_loop_arg(mainloop, ctx, fps, simulate_infinite_loop);
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    free(ctx);
    return EXIT_SUCCESS;
}