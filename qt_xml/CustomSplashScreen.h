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
    QVector<QPixmap> my_images = {QPixmap(":/control_xml.png"),
                                  QPixmap(":/george_sotter_xml.png"),
                                  QPixmap(":/mandalorian_xml.png"),
                                  QPixmap(":/romashka_xml.png"),
                                  QPixmap(":/valdemar_fink_xml.png"),
                                  QPixmap(":/william_glakens_xml.png"),
                                  QPixmap(":/firenze_lai_xml.png")};

public:
    explicit CustomSplashScreen(const QPixmap& pixmap);
    CustomSplashScreen(const QPixmap& images, my_images_flag_t);
    ~CustomSplashScreen();

    virtual void drawContents(QPainter *painter);
    void showStatusMessage(const QString &message, const QColor &color = Qt::black);
    void setMessageRect(QRect rect, int alignment = Qt::AlignLeft);

};

