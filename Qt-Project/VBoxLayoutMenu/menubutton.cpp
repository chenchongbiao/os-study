#include <QPainter>
#include <QDebug>

#include "menubutton.h"

MenuButton::MenuButton(QWidget *parent) : QPushButton(parent)
{
    paddingLeft = 20;
    paddingRight = 5;
    paddingTop = 5;
    paddingBottom = 5;
    textAlign = TextAlign_Left;

    normalBgColor = QColor(255, 255, 255);
    checkBgColor = QColor(0, 129, 255);
    normalTextColor = QColor(37, 37, 37);
    checkTextColor = QColor(255, 255, 255);

    setCheckable(true);

//    this->setStyleSheet("border-radius: 3;");
}

void MenuButton::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制文字
    drawText(&painter);
}

void MenuButton::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    int width = this->width();
    int height = this->height();

    QRect bgRect;
    if (linePosition == LinePosition_Left) {
        bgRect = QRect(lineSpace, 0, width - lineSpace, height);
    } else if (linePosition == LinePosition_Right) {
        bgRect = QRect(0, 0, width - lineSpace, height);
    } else if (linePosition == LinePosition_Top) {
        bgRect = QRect(0, lineSpace, width, height - lineSpace);
    } else if (linePosition == LinePosition_Bottom) {
        bgRect = QRect(0, 0, width, height - lineSpace);
    }

    //根据当前状态选择对应颜色
    QColor bgColor;
    if (isChecked()) {
        bgColor = checkBgColor;
    } else {
        bgColor = normalBgColor;
    }

    painter->setBrush(bgColor);

    painter->drawRect(bgRect);

    painter->restore();
}

void MenuButton::drawText(QPainter *painter)
{
    painter->save();
    painter->setBrush(Qt::NoBrush);

    //根据当前状态选择对应颜色
    QColor textColor;
    if (isChecked()) {
        textColor = checkTextColor;
    } else {
        textColor = normalTextColor;
    }

    QRect textRect = QRect(paddingLeft, paddingTop, width() - paddingLeft - paddingRight, height() - paddingTop - paddingBottom);
    painter->setPen(textColor);
    painter->drawText(textRect, textAlign | Qt::AlignVCenter, text());

    painter->restore();
}

void MenuButton::setPaddingLeft(int paddingLeft)
{
    if (this->paddingLeft != paddingLeft) {
        this->paddingLeft = paddingLeft;
        this->update();
    }
}

void MenuButton::setPaddingRight(int paddingRight)
{
    if (this->paddingRight != paddingRight) {
        this->paddingRight = paddingRight;
        this->update();
    }
}

void MenuButton::setPaddingTop(int paddingTop)
{
    if (this->paddingTop != paddingTop) {
        this->paddingTop = paddingTop;
        this->update();
    }
}

void MenuButton::setPaddingBottom(int paddingBottom)
{
    if (this->paddingBottom != paddingBottom) {
        this->paddingBottom = paddingBottom;
        this->update();
    }
}

void MenuButton::setPadding(int padding)
{
    setPadding(padding, padding, padding, padding);
}

void MenuButton::setPadding(int paddingLeft, int paddingRight, int paddingTop, int paddingBottom)
{
    this->paddingLeft = paddingLeft;
    this->paddingRight = paddingRight;
    this->paddingTop = paddingTop;
    this->paddingBottom = paddingBottom;
    this->update();
}

void MenuButton::setTextAlign(const MenuButton::TextAlign &textAlign)
{
    if (this->textAlign != textAlign) {
        this->textAlign = textAlign;
        this->update();
    }
}

void MenuButton::setLinePosition(const MenuButton::LinePosition &linePosition)
{
    if (this->linePosition != linePosition) {
        this->linePosition = linePosition;
        this->update();
    }
}

void MenuButton::setNormalTextColor(const QColor &normalTextColor)
{
    if (this->normalTextColor != normalTextColor) {
        this->normalTextColor = normalTextColor;
        this->update();
    }
}

void MenuButton::setCheckTextColor(const QColor &checkTextColor)
{
    if (this->checkTextColor != checkTextColor) {
        this->checkTextColor = checkTextColor;
        this->update();
    }
}

void MenuButton::setNormalBgColor(const QColor &normalBgColor)
{
    if (this->normalBgColor != normalBgColor) {
        this->normalBgColor = normalBgColor;
        this->update();
    }
}

void MenuButton::setCheckBgColor(const QColor &checkBgColor)
{
    if (this->checkBgColor != checkBgColor) {
        this->checkBgColor = checkBgColor;
        this->update();
    }
}
