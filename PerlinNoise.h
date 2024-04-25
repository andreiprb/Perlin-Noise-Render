#pragma once

#include <math.h>

#include "color_vectors.h"
#include "Renderer.h"

class Renderer;

class PerlinNoise
{
    static vector2 randomGradient(int ix, int iy);
    static float dotGridGradient(int ix, int iy, float x, float y);
    static float interpolate(float a0, float a1, float w);
    static float perlin(float x, float y);
    
    static float smoothStep(const float& edge0, const float& edge1, float x);
    static color interpolateColor(const color& c0, const color& c1, const float& t);
    static color colorMap(float value);
public:
    static void Algorithm(Renderer& r, const int& aspect_index1, const int& aspect_index2, char aspect);

    static long s_random_seed;
};