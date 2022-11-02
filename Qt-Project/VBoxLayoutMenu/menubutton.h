#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QPushButton>

class MenuButton : public QPushButton
{
    Q_OBJECT
    Q_ENUMS(TextAlign)
    Q_ENUMS(LinePosition)

public:
    enum TextAlign {
        TextAlign_Left = 0x0001,    //左侧对齐
        TextAlign_Right = 0x0002,   //右侧对齐
        TextAlign_Top = 0x0020,     //顶部对齐
        TextAlign_Bottom = 0x0040,  //底部对齐
        TextAlign_Center = 0x0004   //居中对齐
    };

    enum LinePosition {
        LinePosition_Left = 0,      //左侧
        LinePosition_Right = 1,     //右侧
        LinePosition_Top = 2,       //顶部
        LinePosition_Bottom = 3     //底部
    };

public:
    explicit MenuButton(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);     // 绘图事件，修改按钮
    void drawBg(QPainter *painter);     // 绘制背景
    void drawText(QPainter *painter);   // 绘制文字
    void setPaddingLeft(int paddingLeft);
    void setPaddingRight(int paddingRight);
    void setPaddingTop(int paddingTop);
    void setPaddingBottom(int paddingBottom);
    void setPadding(int padding);
    void setPadding(int paddingLeft, int paddingRight, int paddingTop, int paddingBottom);
    void setTextAlign(const MenuButton::TextAlign &textAlign);
    void setLinePosition(const MenuButton::LinePosition &linePosition);
    void setNormalTextColor(const QColor &normalTextColor);
    void setCheckTextColor(const QColor &checkTextColor);
    void setNormalBgColor(const QColor &normalBgColor);
    void setCheckBgColor(const QColor &checkBgColor);

private:
    int paddingLeft;                //文字左侧间隔
    int paddingRight;               //文字右侧间隔
    int paddingTop;                 //文字顶部间隔
    int paddingBottom;              //文字底部间隔
    TextAlign textAlign;            //文字对齐

    bool showLine;                  //显示线条
    int lineSpace;                  //线条间隔
    int lineWidth;                  //线条宽度
    LinePosition linePosition;      //线条位置
    QColor lineColor;               //线条颜色

    QColor normalBgColor;           //正常背景颜色
    QColor checkBgColor;            //选中背景颜色
    QColor normalTextColor;         //正常文字颜色
    QColor checkTextColor;          //选中文字颜色
};

#endif // MENUBUTTON_H
