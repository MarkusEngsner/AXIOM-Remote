#ifndef ISCREEN_H
#define ISCREEN_H

#include "../../Utils.h"

#include "../Widgets/ButtonBar.h"
#include "../Widgets/ImageButton.h"

class ButtonBar;
class IUSBDevice;
class IPainter;
class IMenuSystem;

enum class Button;
enum class Color565;

#define MAX_BUTTON_COUNT 3

class IScreen
{
  protected:
    IUSBDevice* _usbDevice;

    ButtonBar _bottomButtonBar;
    ButtonBar _leftButtonBar;

    ImageButton _homeButton;
    ImageButton _backButton;
    //ImageButton _infoButton;

    virtual void DrawCaption();

    virtual void DrawTopButtonBar();
    virtual void DrawBottomButtonBar(IPainter* painter);
    virtual void DrawLeftButtonBar(IPainter* painter);

    virtual void SetBottomButton(ButtonPosition position, IButton* button); // TODO: Rename function name, confusing
    virtual void SetLeftButton(ButtonPosition position, IButton* button); // TODO: Rename function name, confusing

  public:
    IScreen(IUSBDevice* usbDevice = nullptr);
    virtual ~IScreen();

    virtual Color565 GetBackgroundColor();
    virtual void Draw(IPainter* painter);

    virtual void Update(Button button, int8_t knob, IMenuSystem* menuSystem);
};

#endif // ISCREEN_H
