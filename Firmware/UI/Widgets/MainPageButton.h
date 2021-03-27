
#ifndef MAINPAGEBUTTON_H
#define MAINPAGEBUTTON_H

#include "IButton.h"
#include "../Painter/Painter.h"

#include "../Color565.h"

enum class ButtonType
{
    VALUE_AND_LABEL,
    BUTTON
};

class MainPageButton : public IButton
{
    uint16_t _x;
    uint16_t _y;

    uint16_t _width;

    uint16_t _labelHeight;
    uint16_t _valueHeight;

    char* _label;
    char* _value;

    bool _invertOrder;

    Font _labelFont;
    Font _valueFont;

    ButtonType _type;

    // Color Defintions

    enum Colors : uint8_t
    {
        LabelText = 0,
        LabelBackground = 1,
        ValueText = 2,
        ValueBackground = 2,
    };
    // uint16_t labelTextColor;
    // uint16_t labelBackgroundColor;
    // uint16_t valueTextColor;
    // uint16_t valueBackgroundColor;

    // uint16_t textHighlightColor;
    // uint16_t backgroundHighlightColor;

    // uint16_t currentLabelTextColor;
    // uint16_t currentLabelBackgroundColor;
    // uint16_t currentValueTextColor;
    // uint16_t currentValueBackgroundColor;

    // bool _hideValue;

  public:
    MainPageButton() : IButton()
    {
    }

    // TODO: Check if customizable height is required for this button, if yes, add it later
    MainPageButton(uint16_t x, uint16_t y, uint16_t width, const char* label = "...", bool invertOrder = false,
                   ButtonType type = ButtonType::VALUE_AND_LABEL) :
        _x(x),
        _y(y), _width(width), _labelHeight(20), _valueHeight(40), _label((char*)label), _value((char*)"..."),
        _invertOrder(invertOrder), _labelFont(Font::FreeSans9pt7b), _valueFont(Font::FreeSans12pt7b), _type(type)
    {
        SetColor(ButtonState::Default, Colors::LabelText, static_cast<uint16_t>(Color565::White));
        SetColor(ButtonState::Default, Colors::LabelBackground, static_cast<uint16_t>(Color565::Black));
        SetColor(ButtonState::Default, Colors::ValueText, static_cast<uint16_t>(Color565::Black));
        SetColor(ButtonState::Default, Colors::ValueBackground, static_cast<uint16_t>(Color565::White));

        SetColor(ButtonState::Highlighted, Colors::ValueBackground, static_cast<uint16_t>(Color565::AXIOM_Orange));
        SetColor(ButtonState::Highlighted, Colors::ValueText, static_cast<uint16_t>(Color565::Black));
    }

    void Draw(IPainter* painter) override
    {
        if (_type == ButtonType::BUTTON)
        {
            DrawButton(painter);
        } else if (_type == ButtonType::VALUE_AND_LABEL)
        {
            /*  the buttons at the top have label at the top and value fields below
             *  for the buttons at the bottom of the screen the order is inverted (_invertOrder == true)
             *  meaning the value field is at the top and the label at the bottom. The drawing routine needs to
             *  account for that.
             */

            if (_invertOrder)
            {
                // bottom items
                DrawLabelBox(painter, _valueHeight, 16);
                DrawValueBox(painter, 0, 30);
            } else
            {
                // top items
                DrawLabelBox(painter, 0, 16);
                DrawValueBox(painter, _labelHeight, 30);
            }
        }
    }

    void DrawButton(IPainter* painter)
    {
        // const uint16_t current[] = GetCurrentColor();
        painter->DrawFillRoundRectangle(_x, _y, _width, _labelHeight, 3, GetCurrentColor(Colors::LabelBackground));
        painter->SetFont(_labelFont);
        painter->DrawText(_x, _y + 24, _label, GetCurrentColor(Colors::LabelText), TextAlign::TEXT_ALIGN_CENTER,
                          _width);
    }

    void DrawLabelBox(IPainter* painter, int8_t verticaloffset, int8_t verticaltextoffset)
    {
        painter->DrawFillRoundRectangle(_x, _y + verticaloffset, _width, _labelHeight, 3,
                                        GetCurrentColor(Colors::LabelBackground));
        painter->SetFont(_labelFont);
        painter->DrawText(_x, _y + verticaloffset + verticaltextoffset, _label, GetCurrentColor(Colors::LabelText),
                          TextAlign::TEXT_ALIGN_CENTER, _width);
    }

    void DrawValueBox(IPainter* painter, int8_t verticaloffset, int8_t verticaltextoffset)
    {
        painter->DrawFillRoundRectangle(_x, _y + verticaloffset, _width, _valueHeight, 3,
                                        GetCurrentColor(Colors::ValueBackground));
        painter->SetFont(_valueFont);
        painter->DrawText(_x, _y + verticaloffset + verticaltextoffset, _value, GetCurrentColor(Colors::ValueText),
                          TextAlign::TEXT_ALIGN_CENTER, _width);
    }

    // TODO: Find out what this function does or why we need it.
    uint8_t GetFontYOffset(uint8_t height)
    {
        uint8_t fontOffset = 0;

        switch (_labelFont)
        {
        case Font::FreeSans9pt7b:
            fontOffset = height / 2 - 16 / 2;
            break;
        case Font::FreeSans12pt7b:
            fontOffset = height / 2 - 24 / 2;
            break;
        case Font::FreeSans18pt7b:
            fontOffset = height / 2 - 34 / 2;
            break;
        case Font::FreeSans24pt7b:
            fontOffset = height / 2 - 44 / 2;
            break;
        }

        return fontOffset;
    }

    void SetLabelFont(Font font)
    {
        _labelFont = font;
    }

    void SetType(ButtonType type)
    {
        _type = type;
    }

    void SetValue(char* value)
    {
        _value = value;
    }

    void SetLabelHeight(uint16_t height)
    {
        _labelHeight = height;
    }
};

#endif /* MAINPAGEBUTTON_H */
