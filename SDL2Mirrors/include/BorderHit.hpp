#pragma once
#include <vector>
#include <optional>
#include <variant>
#include <iostream>


namespace BorderHit
{
	struct Position2D {
		double x;
		double y;
	};

	inline bool operator==(const Position2D& pos1, const Position2D& pos2) {
		return pos1.x == pos2.x && pos1.y == pos2.y;
	}

	inline bool operator!=(const Position2D& pos1, const Position2D& pos2) {
		return !(pos1 == pos2);
	}

	inline std::ostream& operator<<(std::ostream& os, const Position2D& pos) {
		os << "xCoord: " << pos.x << "yCoord: " << pos.y;
		return os;
	}

	struct HitLine2D { // TODO make this a class for initialization with modulo
		Position2D pos;
		double angle;
	};

	inline bool facesRight(const HitLine2D& line) { // the angle in degrees is "going up"
		//return line.angle > 0 && line.angle < 180;
		return line.angle > 0 && line.angle <= 180;
	}
	inline bool facesTop(const HitLine2D& line) {
		return (line.angle > 270 && line.angle <= 360) || (line.angle >= 0 && line.angle < 90);
	}
	inline bool facesLeft(const HitLine2D& line) {
		return line.angle > 180 && line.angle <= 360;
	}
	inline bool facesBot(const HitLine2D& line) {
		return line.angle > 90 && line.angle <= 270;
	}



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
		HitRectangle2D shape;
		std::vector<HitLine2D> hitLines;

		bool insideRectangle(const Position2D& point);
		void wallHitReflection(const size_t reflections);
		
	public:
		inline HitLine2D startLine() {
			return hitLines[0];
		}
		RectangleHitter(const double rectXPos, const double rectYPos, double width, double height,HitLine2D startLine) :
			shape(HitRectangle2D{ Position2D{rectXPos,rectYPos}, width,height}), hitLines{startLine} {
		};
		RectangleHitter(const HitRectangle2D& rect) : shape(rect), hitLines{ HitLine2D{0,0,0} } {
		};
		RectangleHitter(const HitRectangle2D& rect,const HitLine2D& startLine) : shape(rect), hitLines{ startLine } {
		};


		std::vector<SimpleLine2D> getLines(const size_t amount);

	};





}; // namespace BorderHit