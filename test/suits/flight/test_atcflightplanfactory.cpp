
#include "test_atcflightplanfactory.h"

void Test_ATCFlightPlanFactory::test_newFlightPlan()
{
    ATCPaths paths;
    ATCFlightPlanFactory foo(paths);

    ATCFlightPlan *plan = foo.newFlightPlan();
    QVERIFY(plan->getRoute().getDeparture().isNull());

    delete plan;

    plan = foo.newFlightPlan(ATC::IFR, "EPWA", "EPKK", 35000, QTime(12, 15, 0, 0));
    QVERIFY(plan->getFlightRules() == ATC::IFR);
    QVERIFY(plan->getRoute().getDeparture() == "EPWA");
    QVERIFY(plan->getRoute().getDestination() == "EPKK");
    QVERIFY(plan->getAltitude() == 35000);
    QVERIFY(plan->getDepartureTime() == QTime(12, 15, 0, 0));

    delete plan;

    plan = foo.newFlightPlan(ATC::IFR, "EPWA", "EDDT", 32000, QTime(12, 15, 0, 0));
    QVERIFY(plan == nullptr);
}

