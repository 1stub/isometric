#ifndef PERLIN_H
#define PERLIN_H

#include <SFML/Graphics.hpp>

// all code credited to https://adrianb.io/2014/08/09/perlinnoise.html wonderful article.

class Perlin{
  public:
    Perlin(); 
    double perlin(double x, double y, double z);

    //this is the actual function used tp apply noise to a specific grid tile
    double noise(double x, double y, double z, int octaves, double persistence);
    int inc(int num);
    static double fade(double t);
    static double lerp(double a, double b, double x);
    static double grad(int hash, double x, double y, double z);
  private:
   static const int permutation[256]; 
   int p[512];
   int repeat = -1;
};

#endif
