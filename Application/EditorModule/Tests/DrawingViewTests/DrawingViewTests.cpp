
#include "DrawingViewTests.h"



DrawingViewTests::DrawingViewTests()
{

}

DrawingViewTests::~DrawingViewTests()
{

}

void DrawingViewTests::test_case1()
{
    Events *events = new Events;
    DrawingView view(events);

    view.setPenWidth(15);
    QCOMPARE(view.getPenWidth(), 15);

    delete events;
}

QTEST_MAIN(DrawingViewTests)
