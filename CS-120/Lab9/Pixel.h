# ifndef PIXEL_H
# define PIXEL_H

# include <ostream>

class Pixel {
    private:
        int r = 0;
        int g = 0;
        int b = 0;

        int getValidColor(int v);

    public:
        Pixel(int r, int g, int b);
        Pixel();
        int getRed() const;
        int getGreen() const;
        int getBlue() const;
        void setRed(int r);
        void setGreen(int g);
        void setBlue(int b);
        Pixel operator+(const Pixel& p);    
};

std::ostream& operator<<(std::ostream& os, const Pixel& p);

# endif
