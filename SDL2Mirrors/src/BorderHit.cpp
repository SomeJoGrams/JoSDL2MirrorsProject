




#include "BorderHit.hpp"
#include "Helper.hpp"

namespace BorderHit
{
	

	StraightLine2D hitLineToStraightLine(const HitLine2D& hitLine) {
		double slope = AngleHelper::degToRad(hitLine.angle);
		double bias = hitLine.pos.y - slope * hitLine.pos.x;	
		return StraightLine2D{ slope,bias };
	}

	// maybe use a border to determine start position
	/*HitLine2D StraightLineToHitLine(const StraightLine2D& straightLine) {
		int slope = AngleHelper::degToRad(hitLine.angle);
		int bias = hitLine.pos.y - slope * hitLine.pos.x;
		return StraightLine2D{ slope,bias };
	}*/

	std::optional<std::variant<Position2D, VerticalLine2D, StraightLine2D>> solveIntersectionPoint(const std::variant<VerticalLine2D, StraightLine2D>& firstLine
													, const std::variant<VerticalLine2D, StraightLine2D>& secondLine) {
		if (std::holds_alternative<VerticalLine2D>(firstLine) && std::holds_alternative<VerticalLine2D>(secondLine)) {
			if (std::get<VerticalLine2D>(firstLine) == std::get<VerticalLine2D>(secondLine)) {
				return std::get<VerticalLine2D>(firstLine);
			}
			return {};
		}
		else if (std::holds_alternative<VerticalLine2D>(firstLine) != std::holds_alternative<VerticalLine2D>(secondLine)) {
			// for only one vertical line do this
			// we get a x coordinate and just set it in

		}
		
		StraightLine2D line1 = std::get<StraightLine2D>(firstLine);
		StraightLine2D line2 = std::get<StraightLine2D>(secondLine);

		auto m1 = line1.slope;
		auto b1 = line1.bias;
		auto m2 = line2.slope;
		auto b2 = line2.bias;
		// check for invalid solutions
		if (m1 == m2 && b1 == b2) {
			return line1; // same lines
		}
		// otherwise create a new pair of where the lines intersect
		auto x = (b2 - b1) / (m2 - m1);
		auto y = m2 * x + b1;
		Position2D pos{ x,y };
		return pos;
	}
	
	bool RectangleHitter::insideRectangle(const Position2D& pos) {
		return pos.y <= (*this).shape.height + (*this).shape.pos.y && pos.y >= (*this).shape.pos.y
			&& pos.x <= (*this).shape.width + (*this).shape.pos.x && pos.x >= (*this).shape.pos.x;
	}

	HitLine2D RectangleHitter::wallHitReflection(size_t startInd) {
		// TODO implement with startInd
		//startLine
		

		//std::variant<VerticalLine2D, StraightLine2D>;
		// hit right side
		auto leftLine = VerticalLine2D{this->shape.pos.x};
		auto rightLine = VerticalLine2D{this->shape.pos.x + this->shape.width};
		auto botLine = StraightLine2D{1,this->shape.pos.y + this->shape.height};
		auto topLine = StraightLine2D{1,this->shape.pos.y};
		auto straightPointLine = hitLineToStraightLine(this->startLine); // TODO fix this to also return vertical lines
		if (auto notEmptyObject = solveIntersectionPoint(rightLine,straightPointLine)){ // resolve optional
			if (const Position2D* pos = std::get_if<Position2D>(&notEmptyObject.value())) {
				if ((*this).insideRectangle(*pos)) {
					double reflectedAngle = -1 * this->hitLines[0].angle;
					return HitLine2D{ *pos,reflectedAngle };
				}
			}

		}
		//else if (auto positionBot = solveIntersectionPoint()/*) {

		//}
		return HitLine2D{ 0,0,0 };
	}

}