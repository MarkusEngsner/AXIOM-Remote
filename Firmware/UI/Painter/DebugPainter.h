#ifndef DEBUGPAINTER_H
#define DEBUGPAINTER_H

#include <stdint.h>

#include "PainterDecorator.h"

//template <class T>
class DebugPainter : public Painter
{
    Painter* _painter;

  public:
    DebugPainter(Painter* painter) : Painter(*painter), _painter(painter)
    {
    }

    void DrawIcon(const uint8_t* data, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color) override
    {
        _painter->DrawIcon(data, x, y, width, height, color);
        _painter->DrawRectangle(x, y, width, height, (uint16_t)Color565::Red);
    }

    void DrawText(uint16_t x, uint16_t y, const char* text, uint16_t color, TextAlign align, uint16_t textblockwidth) override
    {
        uint16_t textWidth = _painter->GetStringFramebufferWidth(text);
        _painter->DrawRectangle(x, y, textWidth, 30, (uint16_t)Color565::Red);
        //std::cout << "Text: " <<  text << " | x: " << x << " y: " << y << " width: " << textWidth << " height: " << "N/A" << std::endl;

        _painter->DrawText(x, y, text, color, align, textblockwidth);
    }
};

#endif // DEBUGPAINTER_H