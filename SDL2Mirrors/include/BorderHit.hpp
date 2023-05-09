#pragma once
#include <vector>
#include <optional>
#include <variant>

namespace BorderHit
{
	struct Position2D {
		double x;
		double y;
	};

	struct HitLine2D {
		Position2D pos;
		double angle;
	};




	struct VerticalLine2D {
		double xPosition;
	};

	inline bool operator==(const VerticalLine2D& firstLine, const VerticalLine2D& secondLine) {
		return firstLine.xPosition == secondLine.xPosition;
	}

	/*
	* a line with slope and bias
	* problem is this can not represent a vertical line
	*/
	struct StraightLine2D {
		double slope;
		double bias;
	};

	struct SimpleLine2D {
		Position2D startPos;
		Position2D endPos;
	};



	struct HitRectangle2D {
		Position2D pos;
		double width;
		double height;
	};


	StraightLine2D hitLineToStraightLine(const HitLine2D& hitLine);

	class RectangleHitter {
	private:
		HitLine2D startLine;
		HitRectangle2D shape;
		std::vector<HitLine2D> hitLines;

		bool insideRectangle(const Position2D& point);
		//int hitsWall();
		HitLine2D wallHitReflection(size_t startInd);
	public:
		RectangleHitter(HitRectangle2D rect) : shape(rect), startLine{ 0,0,0.f } {
		};


		std::vector<SimpleLine2D> getLines(size_t amount);

	};





}; // namespace BorderHit