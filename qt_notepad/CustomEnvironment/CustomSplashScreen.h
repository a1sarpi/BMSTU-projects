#pragma once
#include <QSplashScreen>
#include <QPainter>

struct my_images_flag_t{};
inline constexpr my_images_flag_t my_flag{};

class CustomSplashScreen : public QSplashScreen {
private:
    QString message;
    int alignment;
    QColor color;
    QRect rect;
    QVector<QString> my_images = {QString("../SplashScreens/control_np.png"),
                                  QString("../SplashScreens/george_sotter_np.png"),
                                  QString("../SplashScreens/mandalorian_np.png"),
                                  QString("../SplashScreens/romashka_np.png"),
                                  QString("../SplashScreens/valdemar_fink_np.png"),
                                  QString("../SplashScreens/william_glakens_np.png"),
                                  QString("../SplashScreens/firenze_lai_np.png")};

public:
    explicit CustomSplashScreen(const QPixmap& pixmap);
    CustomSplashScreen(const QPixmap& images, my_images_flag_t);
    ~CustomSplashScreen();

    virtual void drawContents(QPainter *painter);
    void showStatusMessage(const QString &message, const QColor &color = Qt::black);
    void setMessageRect(QRect rect, int alignment = Qt::AlignLeft);

};

