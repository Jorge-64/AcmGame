#include "application.h"

#define WIDTH 1024
#define HEIGHT 768

int main(int argc, char* argv[])
{
    application app;
    app.init(argc, argv, WIDTH, HEIGHT);
    app.run();
}
