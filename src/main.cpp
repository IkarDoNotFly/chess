#include <Game.h>
#include <Saver.h>
#include <ViewSide.h>

#include <memory>

using std::make_shared;

int main()
{
    auto view = make_shared<ViewSide>();

    auto saver = make_shared<Saver>("./saveFile.txt");
    Game game(view, saver);

    bool whiteWon = game.run();
    if (whiteWon) {
        view->renderText("Whites won, congratulations!");
    } else {
        view->renderText("Blacks won, congratulations!");
    }

    return 0;
}
