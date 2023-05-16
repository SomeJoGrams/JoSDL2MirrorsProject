
#include "gtest/gtest.h"



#include "BorderHit.hpp"


namespace BorderHit {

	TEST(BorderHitPositionTest, PosEqualOperation) {
		BorderHit::Position2D firstPos{ 1,1 };
		BorderHit::Position2D secondPos{ 1,1 };
		EXPECT_EQ(firstPos, secondPos);
	}


    class HitLineTest : public testing::Test {
    protected:
        // You can remove any or all of the following functions if their bodies would
        // be empty.

        HitLineTest() {
            // You can do set-up work for each test here.
        }

        ~HitLineTest() override {
            // You can do clean-up work that doesn't throw exceptions here.
        }

        // If the constructor and destructor are not enough for setting up
        // and cleaning up each test, you can define the following methods:

        void SetUp() override {
            // Code here will be called immediately after the constructor (right
            // before each test).f

        }

        void TearDown() override {
            // Code here will be called immediately after each test (right
            // before the destructor).
        }

        // Class members declared here can be used by all tests in the test suite
        // for Foo.
    };

    // test for a single origin
    TEST_F(HitLineTest, AngleCalculation) {
        EXPECT_EQ(1, 1);
    }

    // TODO use the fixture

}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}