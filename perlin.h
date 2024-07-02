#include <SFML/Graphics.hpp>

class Perlin{
  public:
    Perlin(); 
    double perlin(double x, double y, double z);
    int inc(int num);
    static double fade(double t);
    static double lerp(double a, double b, double x);
    static double grad(int hash, double x, double y, double z);
  private:
   static const int permutation[256]; 
   int p[512];
   int repeat;
};
