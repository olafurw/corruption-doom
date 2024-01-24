#define STB_IMAGE_IMPLEMENTATION
#include "../image-resizer-bmp/src/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../image-resizer-bmp/src/stb_image_write.h"

// doom color index
static unsigned char color_index[256][3] = {
    { 0, 0, 0 },
    { 31, 23, 11 },
    { 23, 15, 7 },
    { 75, 75, 75 },
    { 255, 255, 255 },
    { 27, 27, 27 },
    { 19, 19, 19 },
    { 11, 11, 11 },
    { 7, 7, 7 },
    { 47, 55, 31 },
    { 35, 43, 15 },
    { 23, 31, 7 },
    { 15, 23, 0 },
    { 79, 59, 43 },
    { 71, 51, 35 },
    { 63, 43, 27 },
    { 255, 183, 183 },
    { 247, 171, 171 },
    { 243, 163, 163 },
    { 235, 151, 151 },
    { 231, 143, 143 },
    { 223, 135, 135 },
    { 219, 123, 123 },
    { 211, 115, 115 },
    { 203, 107, 107 },
    { 199, 99, 99 },
    { 191, 91, 91 },
    { 187, 87, 87 },
    { 179, 79, 79 },
    { 175, 71, 71 },
    { 167, 63, 63 },
    { 163, 59, 59 },
    { 155, 51, 51 },
    { 151, 47, 47 },
    { 143, 43, 43 },
    { 139, 35, 35 },
    { 131, 31, 31 },
    { 127, 27, 27 },
    { 119, 23, 23 },
    { 115, 19, 19 },
    { 107, 15, 15 },
    { 103, 11, 11 },
    { 95, 7, 7 },
    { 91, 7, 7 },
    { 83, 7, 7 },
    { 79, 0, 0 },
    { 71, 0, 0 },
    { 67, 0, 0 },
    { 255, 235, 223 },
    { 255, 227, 211 },
    { 255, 219, 199 },
    { 255, 211, 187 },
    { 255, 207, 179 },
    { 255, 199, 167 },
    { 255, 191, 155 },
    { 255, 187, 147 },
    { 255, 179, 131 },
    { 247, 171, 123 },
    { 239, 163, 115 },
    { 231, 155, 107 },
    { 223, 147, 99 },
    { 215, 139, 91 },
    { 207, 131, 83 },
    { 203, 127, 79 },
    { 191, 123, 75 },
    { 179, 115, 71 },
    { 171, 111, 67 },
    { 163, 107, 63 },
    { 155, 99, 59 },
    { 143, 95, 55 },
    { 135, 87, 51 },
    { 127, 83, 47 },
    { 119, 79, 43 },
    { 107, 71, 39 },
    { 95, 67, 35 },
    { 83, 63, 31 },
    { 75, 55, 27 },
    { 63, 47, 23 },
    { 51, 43, 19 },
    { 43, 35, 15 },
    { 239, 239, 239 },
    { 231, 231, 231 },
    { 223, 223, 223 },
    { 219, 219, 219 },
    { 211, 211, 211 },
    { 203, 203, 203 },
    { 199, 199, 199 },
    { 191, 191, 191 },
    { 183, 183, 183 },
    { 179, 179, 179 },
    { 171, 171, 171 },
    { 167, 167, 167 },
    { 159, 159, 159 },
    { 151, 151, 151 },
    { 147, 147, 147 },
    { 139, 139, 139 },
    { 131, 131, 131 },
    { 127, 127, 127 },
    { 119, 119, 119 },
    { 111, 111, 111 },
    { 107, 107, 107 },
    { 99, 99, 99 },
    { 91, 91, 91 },
    { 87, 87, 87 },
    { 79, 79, 79 },
    { 71, 71, 71 },
    { 67, 67, 67 },
    { 59, 59, 59 },
    { 55, 55, 55 },
    { 47, 47, 47 },
    { 39, 39, 39 },
    { 35, 35, 35 },
    { 119, 255, 111 },
    { 111, 239, 103 },
    { 103, 223, 95 },
    { 95, 207, 87 },
    { 91, 191, 79 },
    { 83, 175, 71 },
    { 75, 159, 63 },
    { 67, 147, 55 },
    { 63, 131, 47 },
    { 55, 115, 43 },
    { 47, 99, 35 },
    { 39, 83, 27 },
    { 31, 67, 23 },
    { 23, 51, 15 },
    { 19, 35, 11 },
    { 11, 23, 7 },
    { 191, 167, 143 },
    { 183, 159, 135 },
    { 175, 151, 127 },
    { 167, 143, 119 },
    { 159, 135, 111 },
    { 155, 127, 107 },
    { 147, 123, 99 },
    { 139, 115, 91 },
    { 131, 107, 87 },
    { 123, 99, 79 },
    { 119, 95, 75 },
    { 111, 87, 67 },
    { 103, 83, 63 },
    { 95, 75, 55 },
    { 87, 67, 51 },
    { 83, 63, 47 },
    { 159, 131, 99 },
    { 143, 119, 83 },
    { 131, 107, 75 },
    { 119, 95, 63 },
    { 103, 83, 51 },
    { 91, 71, 43 },
    { 79, 59, 35 },
    { 67, 51, 27 },
    { 123, 127, 99 },
    { 111, 115, 87 },
    { 103, 107, 79 },
    { 91, 99, 71 },
    { 83, 87, 59 },
    { 71, 79, 51 },
    { 63, 71, 43 },
    { 55, 63, 39 },
    { 255, 255, 115 },
    { 235, 219, 87 },
    { 215, 187, 67 },
    { 195, 155, 47 },
    { 175, 123, 31 },
    { 155, 91, 19 },
    { 135, 67, 7 },
    { 115, 43, 0 },
    { 255, 255, 255 },
    { 255, 219, 219 },
    { 255, 187, 187 },
    { 255, 155, 155 },
    { 255, 123, 123 },
    { 255, 95, 95 },
    { 255, 63, 63 },
    { 255, 31, 31 },
    { 255, 0, 0 },
    { 239, 0, 0 },
    { 227, 0, 0 },
    { 215, 0, 0 },
    { 203, 0, 0 },
    { 191, 0, 0 },
    { 179, 0, 0 },
    { 167, 0, 0 },
    { 155, 0, 0 },
    { 139, 0, 0 },
    { 127, 0, 0 },
    { 115, 0, 0 },
    { 103, 0, 0 },
    { 91, 0, 0 },
    { 79, 0, 0 },
    { 67, 0, 0 },
    { 231, 231, 255 },
    { 199, 199, 255 },
    { 171, 171, 255 },
    { 143, 143, 255 },
    { 115, 115, 255 },
    { 83, 83, 255 },
    { 55, 55, 255 },
    { 27, 27, 255 },
    { 0, 0, 255 },
    { 0, 0, 227 },
    { 0, 0, 203 },
    { 0, 0, 179 },
    { 0, 0, 155 },
    { 0, 0, 131 },
    { 0, 0, 107 },
    { 0, 0, 83 },
    { 255, 255, 255 },
    { 255, 235, 219 },
    { 255, 215, 187 },
    { 255, 199, 155 },
    { 255, 179, 123 },
    { 255, 163, 91 },
    { 255, 143, 59 },
    { 255, 127, 27 },
    { 243, 115, 23 },
    { 235, 111, 15 },
    { 223, 103, 15 },
    { 215, 95, 11 },
    { 203, 87, 7 },
    { 195, 79, 0 },
    { 183, 71, 0 },
    { 175, 67, 0 },
    { 255, 255, 255 },
    { 255, 255, 215 },
    { 255, 255, 179 },
    { 255, 255, 143 },
    { 255, 255, 107 },
    { 255, 255, 71 },
    { 255, 255, 35 },
    { 255, 255, 0 },
    { 167, 63, 0 },
    { 159, 55, 0 },
    { 147, 47, 0 },
    { 135, 35, 0 },
    { 79, 59, 39 },
    { 67, 47, 27 },
    { 55, 35, 19 },
    { 47, 27, 11 },
    { 0, 0, 83 },
    { 0, 0, 71 },
    { 0, 0, 59 },
    { 0, 0, 47 },
    { 0, 0, 35 },
    { 0, 0, 23 },
    { 0, 0, 11 },
    { 0, 0, 0 },
    { 255, 159, 67 },
    { 255, 231, 75 },
    { 255, 123, 255 },
    { 255, 0, 255 },
    { 207, 0, 207 },
    { 159, 0, 155 },
    { 111, 0, 107 },
    { 167, 107, 107 }
};

int closest_color(unsigned char r, unsigned char g, unsigned char b)
{
    int min = 0;
    int min_index = 0;

    for (int i = 0; i < 256; i++)
    {
        int dr = color_index[i][0] - r;
        int dg = color_index[i][1] - g;
        int db = color_index[i][2] - b;

        int dist = dr*dr + dg*dg + db*db;
        if (i == 0 || dist < min)
        {
            min = dist;
            min_index = i;
        }
    }

    return min_index;
}

int main(int argc, char *argv [])
{
    if (argc < 3)
    {
        printf("Usage: %s <input_image> <output_image>\n", argv[0]);
        return 1;
    }

    int x,y,n;
    unsigned char *data = stbi_load(argv[1], &x, &y, &n, 0);

    for (int i = 0; i < x*y*n; i += n)
    {
        int index = closest_color(data[i], data[i + 1], data[i + 2]);
        data[i] = color_index[index][0];
        data[i + 1] = color_index[index][1];
        data[i + 2] = color_index[index][2];
    }

    stbi_write_bmp(argv[2], x, y, n, data);

    stbi_image_free(data);
    return 0;
}