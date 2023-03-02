#include <QApplication>
#include "MainWindow.h"
#include "CustomSplashScreen.h"
#include <thread>
#include <random>

int main(int argc, char *argv[]) {
    srand(time(nullptr));

    QApplication app(argc, argv);

    MainWindow window;

    QPixmap splashImage;

    CustomSplashScreen* splashScreen = new CustomSplashScreen(splashImage, my_flag);

    splashScreen->show();

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2000ms);

    splashScreen->close();

    app.processEvents();

    window.show();

    return QApplication::exec();
}