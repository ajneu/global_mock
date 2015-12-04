#include "gmock/gmock.h"

int main(int argc, char *argv[])
{
   testing::InitGoogleMock(&argc, argv);
   int ret = RUN_ALL_TESTS();

   std::cout << "Finished" << std::endl;
   return ret;
}
