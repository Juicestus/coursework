# ifndef IMAGE_H
# define IMAGE_H

# include <string>
# include "Pixel.h"

class Image {
    private:
        Pixel** image;
        unsigned int width;
        unsigned int height;

        void load(std::string filename);
        void allocateImage(unsigned int width, unsigned int height);
        void clear();

    public:
        // TODO: rule of three functions

        Image();
        Image(std::string filename);
        Image(unsigned int width, unsigned int height);
        Image(const Image& other);
        ~Image();

        Pixel*& operator[](unsigned int column);
        const Pixel* operator[](unsigned int column) const;
        unsigned int getWidth();
        unsigned int getHeight();

        void makeGreyscale();
        void makeSepia();
        void addColor(Pixel p);

        void output(std::string filename);

        Image& operator=(const Image& other);
};

# endif
