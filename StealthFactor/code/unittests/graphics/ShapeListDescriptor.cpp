#include <gtest/gtest.h>

#include <cmath>
#include <engine/graphics/ShapeListDescriptor.hpp>

namespace engine
{
	namespace graphics
	{
		class AreaComputer : public ShapeDescriptorVisitor
		{
		public:
			void circle(CircleDescriptor &circleDescriptor) override
			{
				_area += (float)M_PI * circleDescriptor.radius * circleDescriptor.radius;
			}

			void rectangle(RectangleDescriptor &rectangleDescriptor)
			{
				_area += rectangleDescriptor.width * rectangleDescriptor.height;
			}

			float getArea() const
			{
				return _area;
			}

		private:
			float _area{ 0.f };
		};

		class ShapeListDescriptorTest : public ::testing::Test
		{
		protected:
			ShapeListDescriptor descriptor;

			void SetUp() override
			{
				ASSERT_TRUE(descriptor.load("circle_2_rectangle_3_5"));
			}
		};

		TEST_F(ShapeListDescriptorTest, Load)
		{
			auto &shapeDescriptors = descriptor.getShapeDescriptors();
			EXPECT_EQ((std::size_t)2, shapeDescriptors.size());
		}

		TEST_F(ShapeListDescriptorTest, Visitor)
		{
			AreaComputer computer;
			for (auto &shapeDescriptor : descriptor.getShapeDescriptors())
			{
				shapeDescriptor->accept(computer);
			}
			EXPECT_FLOAT_EQ(15.f + (float)M_PI * 4.f, computer.getArea());
		}
	}
}