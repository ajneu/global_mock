#include "gmock/gmock.h"
#include "printer.h"
#include "mockrenderer.h"

using namespace testing;


// global mock!!
MockRenderer mock_renderer;


class APrinter : public testing::Test {
public:

   // MockRenderer mock_renderer;     // member mock

   Printer printer;
   APrinter() : printer(mock_renderer)
   {
      ::testing::GMOCK_FLAG(catch_leaked_mocks) = false;
      //::testing::Mock::AllowLeak(&mock_renderer);
   }
};



TEST_F(APrinter, PrintsAChar) {
   const char c = 'c';
   EXPECT_CALL(mock_renderer, print(c))
      .Times(1);

   printer.print(c);
   Mock::VerifyAndClearExpectations(&mock_renderer);
}
