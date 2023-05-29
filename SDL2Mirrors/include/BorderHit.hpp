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

	inline double position2Ddistance(const Position2D pos1, const Position2D pos2) {
		// dist = sqrt((y2 - y1)^2 + (x2-x1)^2)
		return std::sqrt((pos2.y - pos1.y) * (pos2.y - pos1.y) + (pos2.x - pos1.x) * (pos2.x - pos1.x));
	}

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
		return line.angle > 0 && line.angle < 180;
	}
	inline bool facesTop(const HitLine2D& line) {
		return (line.angle > 270 && line.angle <= 360) || (line.angle >= 0 && line.angle < 90);
	}
	inline bool facesLeft(const HitLine2D& line) {
		return line.angle > 180 && line.angle < 360;
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

	struct TraveledLine {
		size_t lineIndex;
		double traveledDistance; // the time that is traveled on the line
	};


	std::variant<VerticalLine2D, StraightLine2D> hitLineToStraightLine(const HitLine2D& hitLine);
	std::variant<VerticalLine2D, StraightLine2D> positionsToLine(const Position2D pos1, const Position2D pos2);

	class RectangleHitter {
	private:
		HitRectangle2D shape;
		std::vector<HitLine2D> hitLines;
		HitLine2D firstLine;
		size_t removedLines;

		bool insideRectangle(const Position2D& point);
		void wallHitReflection(const size_t reflections,const bool goBackwards);
		void clearCache();


		inline HitLine2D getHitLineAtIndex(size_t index) {
			if (index < this->removedLines) { //index - removedLines < 0 use this comparison, elements from the start have already been removed
				this->clearCache();
				this->wallHitReflection(index,true); // genereate up to the index from the start
				return this->hitLines[index - this->removedLines];
			}// the index was removed due to caching only recent lines: calculate from the start
			// fixed size is the amount of current lines  
			if (index > this->fixedSize() - 1) {
				this->wallHitReflection(index - this->fixedSize() + 1,false);
			}
			return this->hitLines[index - this->removedLines];
		}

		inline size_t fixedSize() {
			return this->hitLines.size() + this->removedLines;
		}

	public:
		inline HitLine2D startLine() {
			return firstLine;
		}
		RectangleHitter(const double rectXPos, const double rectYPos, double width, double height,HitLine2D startLine) :
			shape(HitRectangle2D{ Position2D{rectXPos,rectYPos}, width,height}), hitLines{startLine},firstLine(startLine),removedLines(0) {
		};
		RectangleHitter(const double rectXPos, const double rectYPos, double width, double height, HitLine2D startLine,size_t precalculatedLines) :
			shape(HitRectangle2D{ Position2D{rectXPos,rectYPos}, width,height }), hitLines{ startLine }, firstLine(startLine), removedLines(0) {
			this->wallHitReflection(precalculatedLines + 1,false);
		};
		//RectangleHitter(const HitRectangle2D& rect) : shape(rect), hitLines{ HitLine2D{0,0,0} }, {
		//};
		RectangleHitter(const HitRectangle2D& rect,const HitLine2D& startLine) : shape(rect), hitLines{ startLine }, firstLine(startLine), removedLines(0) {
		};


		std::vector<SimpleLine2D> getLines(const size_t amount);
		SimpleLine2D getLine(const size_t index,const int startPercent,const int endPercent);
		std::pair<std::vector<SimpleLine2D>, TraveledLine> getLinesWithSpeed(size_t startIndex, int speed, int time);
		std::pair<std::vector<SimpleLine2D>, TraveledLine> getLinesWithSpeedWithTrailTime(size_t startIndex, int speed, int time, int trailTime);
		std::pair<std::vector<SimpleLine2D>, TraveledLine> getLinesWithSpeedWithTrailLength(size_t startIndex, int speed, int time, int length);
		std::pair<std::vector<SimpleLine2D>, TraveledLine> getLinesWithLength(size_t startIndex, int time, int length);
	};

	class SimpleRectangleHitter : RectangleHitter {
	private:
		size_t currentLineIndex;// = traveledLine.lineIndex;
		int time;// = traveledLine.traveledDistance / speed; // v = s / t <=> s = v * t <=> t = s / v 
	public:
		SimpleRectangleHitter(const RectangleHitter& rectHitter) : RectangleHitter(rectHitter),currentLineIndex(1), time(0) {

		}

		std::vector<SimpleLine2D> linesTrailTime(int speed, int trailTime,int timeOffset);

		std::vector<SimpleLine2D> linesTrailLength(int speed, int length, int timeOffset);



	};



}; // namespace BorderHit