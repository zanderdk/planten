#ifndef RGB_H
#define RGB_H

struct rgb {
    public:
        double r, g, b;
        int t;
        rgb(double r, double g, double b): r(r), g(g), b(b), t(0) { }
        rgb(double r, double g, double b, int t): r(r), g(g), b(b), t(t) { }
};

#endif // RGB_H