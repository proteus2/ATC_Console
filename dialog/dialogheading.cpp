#include "dialogheading.h"
#include "ui_dialogheading.h"

DialogHeading::DialogHeading(ATCFlight *flight, ATCSettings *settings, QWidget *parent) :
    flight(flight),
    settings(settings),
    QDialog(parent),
    ui(new Ui::DialogHeading)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::FramelessWindowHint);

    dialogHeadingSetup();

    connect(ui->listView, SIGNAL(clicked(QModelIndex)), this, SLOT(slotClicked(QModelIndex)));
}

DialogHeading::~DialogHeading()
{
    if(model != nullptr) delete model;
    delete ui;
}

void DialogHeading::slotClicked(const QModelIndex &index)
{
    QString headingString = index.data(Qt::DisplayRole).toString();

    flight->setHdgRestriction(headingString.toInt());
    flight->setDCT(false);

    QString shortEtiquette = flight->getFlightTag()->getTagBox()->getShortEtiquette();
    QString longEtiquette = flight->getFlightTag()->getTagBox()->getLongEtiquette();

    for(int i = 0; i < headingString.size(); i++)
    {
        longEtiquette[i + 39] = headingString.at(i);
    }

    if(flight->getFlightTag()->getTagType() == ATC::Short)
    {
        for(int i = 0; i < 5; i++)
        {
            shortEtiquette[i + 24] = QChar(' ');
            longEtiquette[i + 24] = QChar(' ');
        }

        flight->getFlightTag()->getTagBox()->setShortEtiquette(shortEtiquette);
        flight->getFlightTag()->getTagBox()->setLongEtiquette(longEtiquette);

        flight->getFlightTag()->getTagBox()->rectShort2Long();
        flight->getFlightTag()->setTagType(ATC::Full);
        flight->getFlightTag()->getTagBox()->setLong();

        flight->setNavMode(ATC::Hdg);
    }
    else
    {
        if(flight->getNavMode() == ATC::Nav)
        {
            for(int i = 0; i < 5; i++)
            {
                shortEtiquette[i + 24] = QChar(' ');
                longEtiquette[i + 24] = QChar(' ');
            }

            flight->setNavMode(ATC::Hdg);
        }

        flight->getFlightTag()->getTagBox()->setShortEtiquette(shortEtiquette);
        flight->getFlightTag()->getTagBox()->setLongEtiquette(longEtiquette);

        flight->getFlightTag()->getTagBox()->setLong();
    }

    if(flight->isFinalApp())
    {
        flight->setCldFinalApp(false);
        flight->setFinalApp(false);
        flight->setGlidePath(false);
    }

    if(flight->getRoutePrediction() != nullptr) emit signalUpdateRoute(flight);
    emit signalClosed();
    close();
}

void DialogHeading::dialogHeadingSetup()
{
    model = new QStandardItemModel(this);

    for(int i = 360; i >= 5; i -= 5)
    {
        if(i < 10)
        {
            appendRow("00" + QString::number(i), model);
        }
        else if(i < 100)
        {
            appendRow("0" + QString::number(i), model);
        }
        else
        {
            appendRow(QString::number(i), model);
        }
    }

    ui->listView->setModel(model);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->listView->setFocusPolicy(Qt::NoFocus);

    int heading = flight->getHdgRestriction();
    QString headingString;

    if(heading < 10)
    {
        headingString = "00" + QString::number(heading);
    }
    else if(heading < 100)
    {
        headingString = "0" + QString::number(heading);
    }
    else
    {
        headingString = QString::number(heading);
    }

    if(heading == -1)
    {
        for(int i = 0; i < model->rowCount(); i++)
        {
            if(model->index(i, 0).data(Qt::DisplayRole).toString() == "180")
            {
                ui->listView->scrollTo(model->index(i, 0), QAbstractItemView::PositionAtCenter);
            }
        }
    }
    else
    {
        for(int i = 0; i < model->rowCount(); i++)
        {
            if(model->index(i, 0).data(Qt::DisplayRole).toString() == headingString)
            {
                ui->listView->scrollTo(model->index(i, 0), QAbstractItemView::PositionAtCenter);
            }
        }
    }

    if(flight->isCldFinalApp())
    {
        ui->buttonILS->setStyleSheet(
                                        "QPushButton"
                                        "{"
                                            "color: #c8c8c8;"
                                            "font: bold 11px;"
                                            "background-color: #574A00;"
                                            "border-style: outset;"
                                            "border-width: 2px;"
                                            "border-color: #3e3e3e;"
                                        "}"
                                        ""
                                        "QPushButton::hover"
                                        "{"
                                            "background-color: #705F00;"
                                        "}"
                                        ""
                                        "QPushButton::pressed"
                                        "{"
                                            "background-color: #8A7500;"
                                        "}"
                                    );
        ui->buttonILS->update();
    }
    else if(flight->isFinalApp())
    {
        ui->buttonILS->setStyleSheet(
                                        "QPushButton"
                                        "{"
                                            "color: #c8c8c8;"
                                            "font: bold 11px;"
                                            "background-color: #006400;"
                                            "border-style: outset;"
                                            "border-width: 2px;"
                                            "border-color: #3e3e3e;"
                                        "}"
                                        ""
                                        "QPushButton::hover"
                                        "{"
                                            "background-color: #007800;"
                                        "}"
                                        ""
                                        "QPushButton::pressed"
                                        "{"
                                            "background-color: #008C00;"
                                        "}"
                                    );
        ui->buttonILS->update();
    }

    if(flight->getRunwayDestination().isEmpty()) ui->buttonILS->setDisabled(true);
}

void DialogHeading::appendRow(QString text, QStandardItemModel *model)
{
    QStandardItem *item = new QStandardItem(text);
    item->setTextAlignment(Qt::AlignCenter);
    model->appendRow(item);
}

void DialogHeading::on_buttonILS_clicked()
{
    if(flight->isFinalApp() || flight->isCldFinalApp())
    {
        flight->setCldFinalApp(false);
        flight->setFinalApp(false);
        flight->setGlidePath(false);

        ui->buttonILS->setStyleSheet(
                                        "QPushButton"
                                        "{"
                                            "color: #c8c8c8;"
                                            "font: 10px;"
                                            "background-color: #000000;"
                                            "border-style: outset;"
                                            "border-width: 2px;"
                                            "border-color: #3e3e3e;"
                                        "}"
                                        ""
                                        "QPushButton::hover"
                                        "{"
                                            "background-color: #2d2d2d;"
                                        "}"
                                        ""
                                        "QPushButton::pressed"
                                        "{"
                                            "background-color: #3c3c3c;"
                                        "}"
                                    );
        ui->buttonILS->update();
    }
    else
    {
        if(!flight->getRunwayDestination().isEmpty())
        {
            flight->setCldFinalApp(true);
            ui->buttonILS->setStyleSheet(
                                            "QPushButton"
                                            "{"
                                                "color: #c8c8c8;"
                                                "font: bold 11px;"
                                                "background-color: #574A00;"
                                                "border-style: outset;"
                                                "border-width: 2px;"
                                                "border-color: #3e3e3e;"
                                            "}"
                                            ""
                                            "QPushButton::hover"
                                            "{"
                                                "background-color: #705F00;"
                                            "}"
                                            ""
                                            "QPushButton::pressed"
                                            "{"
                                                "background-color: #8A7500;"
                                            "}"
                                        );
            ui->buttonILS->update();
        }
    }
}
