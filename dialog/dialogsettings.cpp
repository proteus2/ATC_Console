#include "dialogsettings.h"
#include "ui_dialogsettings.h"
#include <QDebug>

DialogSettings::DialogSettings(ATCSituationalDisplay *display, QWidget *parent) :
    situationalDisplay(display),
    ATCDialog(parent, "Settings", 500, 700),
    uiInner(new Ui::DialogSettings)
{
    uiInner->setupUi(this);
    windowSetup();
//    initializeColorBoxes();

    QColor color(0, 0, 0);

    QPalette palette;
    palette.setColor(QPalette::Window, color);

    uiInner->widgetColor->setPalette(palette);

    connect(uiInner->buttonColorPicker, SIGNAL(clicked(bool)), situationalDisplay, SLOT(slotFlagARTCCLow(bool)));
}

DialogSettings::~DialogSettings()
{
    delete uiInner;
}

void DialogSettings::on_buttonColorPicker_clicked()
{
    if(!flagDialogColorPickerExists)
    {
        QColor currentColor(uiInner->widgetColor->palette().color(QPalette::Window));

        dialogColorPicker = new DialogColorPicker(currentColor, this);
        dialogColorPicker->show();

        connect(dialogColorPicker, SIGNAL(signalColorPickerClosed()), this, SLOT(slotColorPickerClosed()));
        connect(dialogColorPicker, SIGNAL(colorSelected(QColor)), this, SLOT(slotSetColor(QColor)));
        connect(dialogColorPicker, SIGNAL(colorSelected(QColor)), situationalDisplay, SLOT(slotSetColorSectorARTCCLow(QColor)));

        flagDialogColorPickerExists = true;
    }
}

void DialogSettings::slotColorPickerClosed()
{
    flagDialogColorPickerExists = false;
//    disconnect(dialogColorPicker, SIGNAL(signalColorPickerClosed()), this, SLOT(slotColorPickerClosed()));
//    disconnect(dialogColorPicker, SIGNAL(colorSelected(QColor)), this, SLOT(slotSetColor(QColor)));
}

void DialogSettings::slotSetColor(QColor color)
{
    QPalette palette = uiInner->widgetColor->palette();
    palette.setColor(QPalette::Window, color);

    uiInner->widgetColor->setPalette(palette);
}

void DialogSettings::initializeColorBoxes()
{
//    QColor color(situationalDisplay->getSettings()->ARTCC_LOW_COLOR);

//    QPalette palette;
//    palette.setColor(QPalette::Window, color);

//    uiInner->widgetColor->setPalette(palette);
}