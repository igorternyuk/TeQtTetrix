#ifndef LCDWIDGET_H
#define LCDWIDGET_H

#include <QLCDNumber>

class LCDWidget : public QLCDNumber
{
    Q_OBJECT
public:
    static const int DEFAULT_DISPLAY_WIDTH = 120;
    static const int DEFAULT_DISPLAY_HEIGHT = 40;
    static const int DEFAULT_DIGIT_NUMBER = 5;
    LCDWidget(int width = DEFAULT_DISPLAY_WIDTH, int height = DEFAULT_DISPLAY_HEIGHT,
              int numDigits = DEFAULT_DIGIT_NUMBER,
              QColor color = Qt::darkGreen, QWidget* parent = nullptr);
    virtual ~LCDWidget();
public slots:
    void reset();
    void update(int value);
};

#endif // LCDWIDGET_H
