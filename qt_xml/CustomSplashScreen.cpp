#include "CustomSplashScreen.h"

CustomSplashScreen::CustomSplashScreen(const QPixmap &pixmap) {
    QSplashScreen::setPixmap(pixmap);
}

CustomSplashScreen::CustomSplashScreen(const QPixmap &pixmap, my_images_flag_t) {
    QSplashScreen::setPixmap(my_images[rand() % 7]);
}

CustomSplashScreen::~CustomSplashScreen() {}

void CustomSplashScreen::drawContents(QPainter *painter) {
    QPixmap textPix = QSplashScreen::pixmap();
    painter->setPen(this->color);
    painter->drawText(this->rect, this->alignment, this->message);
}

void CustomSplashScreen::showStatusMessage(const QString &message, const QColor &color) {
    this->message = message;
    this->color = color;
    this->showMessage(this->message, this->alignment, this->color);
}

void CustomSplashScreen::setMessageRect(QRect rect, int alignment) {
    this->rect = rect;
    this->alignment = alignment;
}
