#ifndef ATCSITUATIONALDISPLAY_H
#define ATCSITUATIONALDISPLAY_H

#include "atcairspace.h"
#include "atcconst.h"
#include "atcsettings.h"
#include "atcpaths.h"
#include "atcflight.h"
#include "atcsimulation.h"
#include "atcruler.h"

#include "dialogaltitude.h"
#include "dialogspeed.h"
#include "dialogheading.h"
#include "dialogroute.h"
#include "dialoghandoff.h"
#include "dialogflightplan.h"

#include <QGraphicsView>
#include <QTimer>
#include <QVector>
#include <QDebug>

struct coord
{
    double x;
    double y;
};

struct sector
{
    QVector<coord> coords;
};

class ATCSituationalDisplay : public QGraphicsView
{
    Q_OBJECT

public:
    explicit ATCSituationalDisplay(QWidget *parent = 0);
    ~ATCSituationalDisplay();

    qreal getBaseScale() const;
    void setBaseScale(qreal scale);
    double getCurrentScale();

    void setFlightFactory(ATCFlightFactory *flightFactory);
    void setSimulation(ATCSimulation *sim);

    ATCSettings* getSettings();
    ATCAirspace* getAirspaceData();
    ATCPaths* getPaths();
    QCursor& getAcftCursor();

    void hideAll();

    void loadDisplay(QString path);
    void exportDisplay(QString path);

    void deleteTrailingDots();

signals:
    void signalDisplayClicked(double x, double y);
    void signalShowFlightCreator();
    void signalUpdateFlightList(ATCFlight *flight);

public slots:
    void slotSetColorSectorARTCCLow(QColor color);
    void slotSetColorSectorARTCCHigh(QColor color);
    void slotSetColorSectorARTCC(QColor color);
    void slotSetColorVOR(QColor color);
    void slotSetColorNDB(QColor color);
    void slotSetColorFix(QColor color);
    void slotSetColorAirport(QColor color);
    void slotSetColorCentreline(QColor color);
    void slotSetColorSTAR(QColor color);
    void slotSetColorSID(QColor color);
    void slotSetColorAirwayLow(QColor color);
    void slotSetColorAirwayHigh(QColor color);

    void slotHideSectorARTCCLow(QString name);
    void slotHideSectorARTCCHigh(QString name);
    void slotHideSectorARTCC(QString name);
    void slotHideFix(QString name);
    void slotHideNDB(QString name);
    void slotHideVOR(QString name);
    void slotHideAirport(QString name);
    void slotHideCentreline(QString name);
    void slotHideSID(QString name);
    void slotHideSTAR(QString name);
    void slotHideAirwayLow(QString name);
    void slotHideAirwayHigh(QString name);

    void slotShowSectorARTCCLow(QString name);
    void slotShowSectorARTCCHigh(QString name);
    void slotShowSectorARTCC(QString name);
    void slotShowFix(QString name);
    void slotShowNDB(QString name);
    void slotShowVOR(QString name);
    void slotShowAirport(QString name);
    void slotShowCentreline(QString name);
    void slotShowSID(QString name);
    void slotShowSTAR(QString name);
    void slotShowAirwayLow(QString name);
    void slotShowAirwayHigh(QString name);

    void slotApplySettings();

    void slotShowFlightTag(ATCFlightTag *tag);
    void slotHideFlightTag(ATCFlightTag *tag);

    void slotClearFlightElements(ATCFlight *flight);
    void slotClearAllFlightElements();

private slots:
    void slotGetLocation();
    void slotGetLocation(QStringList &fixList);

    void slotCreateFlightTag(ATCFlight *flight);
    void slotUpdateFlightTag(ATCFlight *flight);

    void slotCreateDialogAltitude(ATCFlight *flight, QPoint point);
    void slotDialogAltitudeClosed();
    void slotDialogAltitudeCloseOnClick();

    void slotCreateDialogSpeed(ATCFlight *flight, QPoint point);
    void slotDialogSpeedClosed();
    void slotDialogSpeedCloseOnClick();

    void slotCreateDialogHeading(ATCFlight *flight, QPoint point);
    void slotDialogHeadingClosed();
    void slotDialogHeadingCloseOnClick();

    void slotCreateDialogRoute(ATCFlight *flight, QPoint point);
    void slotDialogRouteClosed();
    void slotDialogRouteCloseOnClick();

    void slotCreateDialogHandoff(ATCFlight *flight, QPoint point);
    void slotDialogHandoffClosed();
    void slotDialogHandoffCloseOnClick();

    void slotDisplayRoute(ATCFlight *flight);
    void slotDisplayRoute(QStringList &fixList);
    void slotClearRoute(ATCFlight *flight);
    void slotUpdateRoute(ATCFlight *flight);

    void slotUpdateTags();
    void slotUpdateLeaders();
    void slotUpdateTrailingDots();

    void slotUpdateFlightList(ATCFlight *flight);

    void slotItemHovered(bool flag);

private:
    ATCAirspace *airspaceData = nullptr;
    ATCSettings *settings = nullptr;
    ATCPaths *paths = nullptr;
    ATCFlightFactory *flightFactory = nullptr;
    ATCSimulation *simulation = nullptr;
    ATCRuler *ruler = nullptr;

    qreal baseScale = 1;
    qreal scaleResolution = 0.15;
    double scaleFactor;
    double currentScale;

    double sectorCentreX;
    double sectorCentreY;

    QGraphicsScene *currentScene = nullptr;
    QCursor acftCursor;

    bool flagGetLocation = false;
    bool itemHovered = false;
    bool mousePressedRMB = false;

    bool keyPressedCTRL = false;

    QVector<ATCSectorARTCCLow*> visibleSectorsARTCCLow;
    QVector<ATCSectorARTCCHigh*> visibleSectorsARTCCHigh;
    QVector<ATCSectorARTCC*> visibleSectorsARTCC;
    QVector<ATCRunwayExtendedCentreline*> visibleCentrelines;
    QVector<ATCNavFix*> visibleFixes;
    QVector<ATCAirport*> visibleAirports;
    QVector<ATCBeaconVOR*> visibleVORs;
    QVector<ATCBeaconNDB*> visibleNDBs;
    QVector<ATCProcedureSTARSymbol*> visibleSTARs;
    QVector<ATCProcedureSIDSymbol*> visibleSIDs;
    QVector<ATCAirwayLow*> visibleLowAirways;
    QVector<ATCAirwayHigh*> visibleHighAirways;

    QVector<ATCFlightTag*> visibleTags;
    QVector<ATCRoutePrediction*> visibleRoutes;

    ATCRoutePrediction *tempPrediction = nullptr;

    DialogAltitude *dialogAltitude = nullptr;
    bool dialogAltitudeExists = false;
    bool dialogAltitudeCloseOnClick = false;

    DialogSpeed *dialogSpeed = nullptr;
    bool dialogSpeedExists = false;
    bool dialogSpeedCloseOnClick = false;

    DialogHeading *dialogHeading = nullptr;
    bool dialogHeadingExists = false;
    bool dialogHeadingCloseOnClick = false;

    DialogRoute *dialogRoute = nullptr;
    bool dialogRouteExists = false;
    bool dialogRouteCloseOnClick = false;

    DialogHandoff *dialogHandoff = nullptr;
    bool dialogHandoffExists = false;
    bool dialogHandoffCloseOnClick = false;

    void situationalDisplaySetup();

    void rescaleAll();

    void rescaleScene();
    void rescaleSectorsARTCCLow();
    void rescaleSectorsARTCCHigh();
    void rescaleSectorsARTCC();
    void rescaleFixes();
    void rescaleFixLabels();
    void rescaleVORs();
    void rescaleVORLabels();
    void rescaleNDBs();
    void rescaleNDBLabels();
    void rescaleAirports();
    void rescaleAirportLabels();
    void rescaleExtendedCentrelines();
    void rescaleSTARs();
    void rescaleSIDs();
    void rescaleAirwaysLow();
    void rescaleAirwaysHigh();
    void rescaleTags();
    void rescaleRoutes();
    void rescaleTrailingDots();

    void rescaleSectorARTCCLow(ATCSectorARTCCLow *object);
    void rescaleSectorARTCCHigh(ATCSectorARTCCHigh *object);
    void rescaleSectorARTCC(ATCSectorARTCC *object);
    void rescaleFix(ATCNavFix *object);
    void rescaleVOR(ATCBeaconVOR *object);
    void rescaleNDB(ATCBeaconNDB *object);
    void rescaleAirport(ATCAirport *object);
    void rescaleExtendedCentreline(ATCRunwayExtendedCentreline *object);
    void rescaleSTAR(ATCProcedureSTARSymbol *object);
    void rescaleSID(ATCProcedureSIDSymbol *object);
    void rescaleAirwayLow(ATCAirwayLow *object);
    void rescaleAirwayHigh(ATCAirwayHigh *object);
    void rescaleTag(ATCFlightTag *tag);
    void rescaleRoute(ATCRoutePrediction *route);

    void projectSectorsARTCCLow();
    void projectSectorsARTCCHigh();
    void projectSectorsARTCC();

    void calculateSectorsARTCCLow();
    void calculateSectorsARTCCHigh();
    void calculateSectorsARTCC();
    void calculateFixes();
    void calculateAirports();
    void calculateExtendedCentrelines();
    void calculateCentrelineTicks();
    void calculateVORs();
    void calculateNDBs();
    void calculateSTARs();
    void calculateSIDs();
    void calculateAirwayLow();
    void calculateAirwayHigh();

    void deleteRuler();

    ATCRoutePrediction* constructPrediction(QStringList &fixList);      //To be used only when ATCFlight is unavailable
    void displayRouteFixNames(ATCRoutePrediction *prediction);          //To be used only when ATCFlight is unavailable

    void constructPrediction(ATCFlight *flight);
    void displayRouteFixNames(ATCFlight *flight);
    void displayRouteLevels(ATCFlight *flight);
    void displayRouteETA(ATCFlight *flight);


    void createFlightTag(ATCFlight *flight);

    void createTagType(ATCFlight *flight);
    ATCTagDiamond *createDiamond(ATCFlightTag *tag, double lon, double lat);
    QGraphicsLineItem* createLeader(ATCFlightTag* tag, double lon, double lat, double trueHdg, double tasMPS);
    QGraphicsLineItem* createConnector(ATCFlightTag *tag);
    ATCTagRect* createTagBox(ATCFlightTag *tag);
    QGraphicsSimpleTextItem* createTagText(ATCFlightTag *tag);
    void createEtiquettes(ATCFlight *flight);
    void updateEtiquettesQuick(ATCFlight *flight);
    void updateRoutePrediction(ATCFlight *flight);
    void updateTrailingDots(ATCFlight *flight);

    void assignTagPosition(ATCFlightTag *tag);
    void assignTagPositions();

    void loadInitialDisplay(QString path);
    void interpretDisplayFile(QString path);

    void calculateSectorParameters();

    void connectSlots();

    template<class T> void removeFromVisible(T *object, QVector<T*> &vector);

protected:
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // ATCSITUATIONALDISPLAY_H
