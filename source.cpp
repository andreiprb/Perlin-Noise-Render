#include "Renderer.h"

int main()
{
    srand(time(NULL));
    
    Renderer perlin_renderer(1280, 720);
    PerlinNoise::Algorithm(perlin_renderer, 400, 12, 'g');
    perlin_renderer.Run();

    return 0;
}