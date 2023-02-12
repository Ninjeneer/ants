#include "gui/frame.hpp"
#include "utils/constants.hpp"

int main()
{
    Frame gameFrame = Frame(WINDOW_WIDTH, WINDOW_HEIGHT, "Anthill Game");
    gameFrame.start();
}