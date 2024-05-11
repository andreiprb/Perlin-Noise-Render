#include "PerlinNoise.h"

long PerlinNoise::s_random_seed = 2048419325;

vector2 PerlinNoise::randomGradient(int ix, int iy)
{
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2;
    unsigned a = ix, b = iy;
    a *= 3284157443;

    b ^= a << s | a >> w - s;
    b *= 1911520717;

    a ^= b << s | b >> w - s;
    a *= PerlinNoise::s_random_seed;
    float random = a * (3.14159265 / ~(~0u >> 1)); // [0, 2*Pi]

    vector2 v;
    v.x = sin(random);
    v.y = cos(random);

    return v;
}

float PerlinNoise::dotGridGradient(int ix, int iy, float x, float y)
{
    vector2 gradient = randomGradient(ix, iy);

    float dx = x - (float)ix;
    float dy = y - (float)iy;

    return (dx * gradient.x + dy * gradient.y);
}

float PerlinNoise::interpolate(float a0, float a1, float w)
{
    return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
}

float PerlinNoise::perlin(float x, float y)
{
    int x0 = (int)x;
    int y0 = (int)y;
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    float sx = x - (float)x0;
    float sy = y - (float)y0;

    float n0 = dotGridGradient(x0, y0, x, y);
    float n1 = dotGridGradient(x1, y0, x, y);
    float ix0 = interpolate(n0, n1, sx);

    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    float ix1 = interpolate(n0, n1, sx);

    float value = interpolate(ix0, ix1, sy);

    return value;
}

float PerlinNoise::smoothStep(const float& edge0, const float& edge1, float x)
{
    x = std::max(0.0f, std::min(1.0f, (x - edge0) / (edge1 - edge0)));
    return std::pow(x * x * (3 - 2 * x), 2);
}

color PerlinNoise::interpolateColor(const color& c0, const color& c1, const float& t)
{
    color result{};
    result.r = static_cast<unsigned char>(c0.r + t * (c1.r - c0.r));
    result.g = static_cast<unsigned char>(c0.g + t * (c1.g - c0.g));
    result.b = static_cast<unsigned char>(c0.b + t * (c1.b - c0.b));
    result.a = 255;
    return result;
}

color PerlinNoise::colorMap(float value)
{
    value = std::max(-1.0f, std::min(1.0f, value));

    if (value <= -0.8f) {
        return ColorVectors::s_height_map_colors[0];
    }
    else if (value <= -0.4f) {
        return interpolateColor(ColorVectors::s_height_map_colors[0], ColorVectors::s_height_map_colors[1], smoothStep(-0.8f, -0.4f, value));
    }
    else if (value <= 0.0f) {
        return interpolateColor(ColorVectors::s_height_map_colors[1], ColorVectors::s_height_map_colors[2], smoothStep(-0.4f, 0.0f, value));
    }
    else if (value <= 0.5f) {
        return interpolateColor(ColorVectors::s_height_map_colors[2], ColorVectors::s_height_map_colors[3], smoothStep(0.0f, 0.5f, value));
    }
    else if (value <= 0.7f) {
        return interpolateColor(ColorVectors::s_height_map_colors[3], ColorVectors::s_height_map_colors[4], smoothStep(0.5f, 0.7f, value));
    }
    else {
        return interpolateColor(ColorVectors::s_height_map_colors[4], ColorVectors::s_height_map_colors[5], smoothStep(0.7f, 1.0f, value));
    }

}

void PerlinNoise::Algorithm(Renderer& r, const int& aspect_index1, const int& aspect_index2, char aspect = 'g')
{
    PerlinNoise::s_random_seed = rand() % LONG_MAX;

    if (aspect != 'g' && aspect != 'h')
        aspect = 'g';

    for (int x = 0; x < r.m_window_width; x++)
    {
        for (int y = 0; y < r.m_window_height; y++)
        {
            float val = 0;

            float freq = 1;
            float amp = 1;

            for (int i = 0; i < aspect_index2; i++)
            {
                val += perlin(x * freq / aspect_index1, y * freq / aspect_index1) * amp;

                freq *= 2;
                amp /= 2;

            }

            val *= 1.2;
            val = std::max(-1.0f, std::max(val, 1.0f));

            color Col = PerlinNoise::colorMap(val);
            int index = (y * r.m_window_width + x) * 4;

            if (aspect == 'g')
            {
                unsigned char cl = (unsigned char)(((val + 1.0f) * 0.5f) * 255);
                Col = { cl, cl, cl, 255 };
            }

            r.m_pixels[index] = Col.r;
            r.m_pixels[index + 1] = Col.g;
            r.m_pixels[index + 2] = Col.b;
            r.m_pixels[index + 3] = Col.a;
        }
    }
}
