#include "gmock/gmock.h"

using namespace testing;

// http://stackoverflow.com/a/8944446
class MyMock {
public:
   MOCK_CONST_METHOD2(func_call_expector, int(int, int));

   static int static_func(int a, int b);

private:
   static int (MyMock::*f)(int, int) const;
};

MyMock mock;

int MyMock::static_func(int a, int b) {
   return (mock.*f)(a, b);
}

int (MyMock::*MyMock::f)(int, int) const = &MyMock::func_call_expector;

/*
MyMock *m;

int static_func2(int a, int b)
{
   return m->func_call_expector(a, b);
}
*/
class Calc {
public:
   Calc(int(*cb)(int, int)) : cb_(cb)
   {  }

   int invoke(int a, int b) {
      return (*cb_)(a, b);
   }
private:
   int(*cb_)(int, int);
};


TEST(Go, Teststatic) {
   ::testing::Mock::AllowLeak(&mock);
   const int a = 1, b = 2;

   EXPECT_CALL(mock, func_call_expector(a, b))
      .Times(1);

   Calc calc(MyMock::static_func);
   calc.invoke(a, b);
   Mock::VerifyAndClearExpectations(&mock);
}
