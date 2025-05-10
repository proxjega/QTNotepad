#include <QtTest>

// add necessary includes here

class test1 : public QObject
{
    Q_OBJECT

public:
    test1();
    ~test1();

private slots:
    void test_case1();
    void test_case2();
};

test1::test1() {}

test1::~test1() {}

void test1::test_case1() {
    int x = 1;
    QVERIFY(x == 1);
}
void test1::test_case2() {}

QTEST_APPLESS_MAIN(test1)

#include "tst_test1.moc"
