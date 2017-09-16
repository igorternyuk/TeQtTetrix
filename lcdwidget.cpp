#include "lcdwidget.h"

LCDWidget::LCDWidget(int width, int height, int numDigits, QColor color, QWidget *parent) :
    QLCDNumber(numDigits, parent)
{
   setFixedSize(width, height);
   setAutoFillBackground(true);
   setSegmentStyle(QLCDNumber::Flat);
   QPalette pal = this->palette();
   pal.setColor(QPalette::Normal, QPalette::WindowText, color);
   pal.setColor(QPalette::Normal, QPalette::Window, Qt::black);
   setPalette(pal);
}

LCDWidget::~LCDWidget()
{}

void LCDWidget::reset()
{
    display(0);
}

void LCDWidget::update(int value)
{
    display(value);
}
