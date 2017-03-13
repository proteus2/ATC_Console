
#include "atcflight.h"

ATCFlight::ATCFlight()
{
}

ATCFlight::ATCFlight(State s) : state(s)
{
}

ATCFlight::ATCFlight(State s, ATCFlightPlan *p) : state(s), plan(p)
{
}

ATCFlight::ATCFlight(State s, ATCFlightPlan *p, QString sq) : state(s), plan(p), assignedSquawk(sq)
{
}

ATCFlight::~ATCFlight()
{
    emit signalClearFlightElements(this);

    if(plan != nullptr) delete plan;
    if(tag != nullptr) delete tag;
    if(prediction != nullptr) delete prediction;
    if(profileClimb != nullptr) delete profileClimb;
    if(profileDescent != nullptr) delete profileDescent;

    if(!trailingDots.isEmpty())
    {
        for(int i = 0; i < trailingDots.size(); i++)
        {
            if(trailingDots.at(i) != nullptr) delete trailingDots.at(i);
        }
        trailingDots.clear();
    }

    if(dataLogged) closeDataLog();
}

ATCFlightPlan *ATCFlight::getFlightPlan()
{
    return plan;
}

QString ATCFlight::getSquawk()
{
    return squawk;
}

QString ATCFlight::getAssignedSquawk()
{
    return assignedSquawk;
}

State& ATCFlight::getState()
{
    return state;
}

Temp &ATCFlight::getTemp()
{
    return temp;
}

ATC::NavMode ATCFlight::getNavMode()
{
    return mode;
}

QString ATCFlight::getTargetAltitude()
{
    return targetAltitude;
}

QString ATCFlight::getTargetSpeed()
{
    return targetSpeed;
}

int ATCFlight::getHdgRestriction()
{
    return hdgRestriction;
}

QString ATCFlight::getNextFix()
{
    return nextFix;
}

QTime ATCFlight::getSimStartTime()
{
    return simStart;
}

QStringList &ATCFlight::getFixList()
{
    return fixList;
}

QStringList &ATCFlight::getMainFixList()
{
    return mainFixList;
}

QString ATCFlight::getRunwayDeparture()
{
    return depRwy;
}

QString ATCFlight::getRunwayDestination()
{
    return desRwy;
}

QString ATCFlight::getSID()
{
    return sid;
}

QString ATCFlight::getSTAR()
{
    return star;
}

ATCFlightTag *ATCFlight::getFlightTag()
{
    return tag;
}

ATCRoutePrediction *ATCFlight::getRoutePrediction()
{
    return prediction;
}

QVector<QPair<double, double>> &ATCFlight::getWaypoints()
{
    return waypoints;
}

QVector<QPair<double, double> > &ATCFlight::getProjectedWaypoints()
{
    return projectedWaypoints;
}

QPair<double, double> ATCFlight::getWaypoint(int i)
{
    return waypoints.at(i);
}

QPair<double, double> ATCFlight::getProjectedWaypoint(int i)
{
    return projectedWaypoints.at(i);
}

int ATCFlight::getWaypointsVectorSize()
{
    return waypoints.size();
}

int ATCFlight::getProjectedWaypointsVectorSize()
{
    return projectedWaypoints.size();
}

int ATCFlight::getWaypointIndex()
{
    return waypointIndex;
}

bool ATCFlight::isDCT()
{
    return dct;
}

bool ATCFlight::isCldFinalApp()
{
    return cldFinalApp;
}

bool ATCFlight::isFinalApp()
{
    return finalApp;
}

bool ATCFlight::isGlidePath()
{
    return glidePath;
}

double ATCFlight::getAppTargetAltitude()
{
    return appTargetAltitude;
}

bool ATCFlight::isSimulated()
{
    return simulated;
}

void ATCFlight::setFlightPlan(ATCFlightPlan *fpl)
{
    delete plan;
    plan = fpl;
}

void ATCFlight::setSquawk(QString sq)
{
    squawk = sq;
}

void ATCFlight::setAssignedSquawk(QString sq)
{
    assignedSquawk = sq;
}

void ATCFlight::setState(State st)
{
    state = st;
}

void ATCFlight::setTemp(Temp tp)
{
    temp = tp;
}

void ATCFlight::setNavMode(ATC::NavMode m)
{
    mode = m;
}

void ATCFlight::setTargetAltitude(QString altitude)
{
    targetAltitude = altitude;
}

void ATCFlight::setTargetSpeed(QString speed)
{
    targetSpeed = speed;
}

void ATCFlight::setHdgRestriction(int hdg)
{
    hdgRestriction = hdg;
}

void ATCFlight::setNextFix(QString fix)
{
    nextFix = fix;
}

void ATCFlight::setSimStartTime(QTime time)
{
    simStart = time;
}

void ATCFlight::setFixList(QStringList list)
{
    fixList = list;
}

void ATCFlight::setMainFixList(QStringList list)
{
    mainFixList = list;
}

void ATCFlight::setRunwayDeparture(QString rwy)
{
    depRwy = rwy;
}

void ATCFlight::setRunwayDestination(QString rwy)
{
    desRwy = rwy;
}

void ATCFlight::setSID(QString procedure)
{
    sid = procedure;
}

void ATCFlight::setSTAR(QString procedure)
{
    star = procedure;
}

void ATCFlight::setFlightTag(ATCFlightTag *t)
{
    tag = t;
}

void ATCFlight::setRoutePrediction(ATCRoutePrediction *pred)
{
    prediction = pred;
}

void ATCFlight::appendWaypoint(QPair<double, double> wp)
{
    waypoints.append(wp);
}

void ATCFlight::appendProjectedWaypoint(QPair<double, double> wp)
{
    projectedWaypoints.append(wp);
}

void ATCFlight::setWaypointIndex(int i)
{
    waypointIndex = i;
}

void ATCFlight::setDCT(bool flag)
{
    dct = flag;
}

void ATCFlight::setCldFinalApp(bool flag)
{
    cldFinalApp = flag;
}

void ATCFlight::setFinalApp(bool flag)
{
    finalApp = flag;
}

void ATCFlight::setGlidePath(bool flag)
{
    glidePath = flag;
}

void ATCFlight::setAppTargetAltitude(double altitudeM)
{
    appTargetAltitude = altitudeM;
}

void ATCFlight::setSimulated(bool flag)
{
    simulated = flag;
}

QVector<ATCTrailingDot*> &ATCFlight::getTrailingDots()
{
    return trailingDots;
}

ATCTrailingDot *ATCFlight::getTrailingDot(int i)
{
    return trailingDots.at(i);
}

int ATCFlight::getTrailingDotsVectorSize()
{
    return trailingDots.size();
}

void ATCFlight::appendTrailingDot(ATCTrailingDot *dot)
{
    trailingDots.append(dot);
}

void ATCFlight::setTrailingDots(QVector<ATCTrailingDot *> &vector)
{
    trailingDots = vector;
}

void ATCFlight::removeOldestDot()
{
    delete trailingDots.at(0);
    trailingDots.removeFirst();
}

void ATCFlight::rescaleDots()
{
    for(int i = 0; i < trailingDots.size(); i++)
    {
        trailingDots.at(i)->rescaleDot();
    }
}

void ATCFlight::clearWaypoints()
{
    waypoints.clear();
    projectedWaypoints.clear();
}

void ATCFlight::setDataLog(QString path)
{
    logFile.setFileName(path);

    if(!logFile.open(QFile::Append | QFile::Text))
    {
        QMessageBox msgBox;
        msgBox.setText("ATCFlight: Failed to open path: " + path);
        msgBox.exec();

        return;
    }

    logStream.setDevice(&logFile);
    dataLogged = true;
}

void ATCFlight::closeDataLog()
{
    logFile.close();
    dataLogged = false;
}

void ATCFlight::logData(QString buffer)
{
    logStream << buffer << endl;
}

ATCProfileClimb *ATCFlight::getProfileClimb()
{
    return profileClimb;
}

void ATCFlight::setProfileClimb(ATCProfileClimb *profile)
{
    profileClimb = profile;
}

ATCProfileDescent *ATCFlight::getProfileDescent()
{
    return profileDescent;
}

void ATCFlight::setProfileDescent(ATCProfileDescent *profile)
{
    profileDescent = profile;
}

double ATCFlight::getLegDistance(int i)
{
    return legDistances.at(i);
}

int ATCFlight::getLegDistanceVectorSize()
{
    return legDistances.size();
}

void ATCFlight::appendLegDistance(double dst)
{
    legDistances.append(dst);
}

void ATCFlight::clearLegDistances()
{
    legDistances.clear();
}

double ATCFlight::getLegAngleChange(int i)
{
    return legAngleChanges.at(i);
}

int ATCFlight::getLegAngleChangeVectorSize()
{
    return legAngleChanges.size();
}

void ATCFlight::appendLegAngleChange(double chng)
{
    legAngleChanges.append(chng);
}

void ATCFlight::clearLegAngleChanges()
{
    legAngleChanges.clear();
}

void ATCFlight::slotCreateDialogAltitude(QPoint point)
{
    emit signalCreateDialogAltitude(this, point);
}

void ATCFlight::slotCreateDialogSpeed(QPoint point)
{
    emit signalCreateDialogSpeed(this, point);
}

void ATCFlight::slotCreateDialogHeading(QPoint point)
{
    emit signalCreateDialogHeading(this, point);
}

void ATCFlight::slotCreateDialogRoute(QPoint point)
{
    emit signalCreateDialogRoute(this, point);
}

void ATCFlight::slotCreateDialogHandoff(QPoint point)
{
    emit signalCreateDialogHandoff(this, point);
}

void ATCFlight::slotCreateDialogFlightPlan()
{
    emit signalCreateDialogFlightPlan(this);
}

void ATCFlight::slotDisplayRoute()
{
    emit signalDisplayRoute(this);
}
