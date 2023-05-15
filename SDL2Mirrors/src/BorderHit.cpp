




#include "BorderHit.hpp"
#include "Helper.hpp"

namespace BorderHit
{
	

	StraightLine2D hitLineToStraightLine(const HitLine2D& hitLine) { // TODO handle Vertical lines
		double slope(0);
		if (hitLine.angle < 90 && hitLine.angle >= 0) {
			slope = 1 / std::tan(AngleHelper::degToRad(hitLine.angle));
		}
		else if (hitLine.angle > 90 && hitLine.angle < 180) {
			slope = - 1 / std::tan(AngleHelper::degToRad(180 - hitLine.angle));
		}
		else if (hitLine.angle > 180 && hitLine.angle < 270) {
			//slope = 1 / std::tan(AngleHelper::degToRad(270 - hitLine.angle));
			//slope = 1 / std::tan(AngleHelper::degToRad(270 - hitLine.angle));
			slope = std::tan(AngleHelper::degToRad(270 - hitLine.angle));
		}
		else if (hitLine.angle > 270 && hitLine.angle < 360) {
			slope = 1 / std::tan(AngleHelper::degToRad(hitLine.angle));
		}
		
		double bias = (hitLine.pos.y) - slope * hitLine.pos.x; // the position has to be inverted, bc the positions are mirrored
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
			// this gurantees to give us a position
			double xPos;
			double yPos;
			if (const VerticalLine2D* vertLine1 = std::get_if<VerticalLine2D>(&firstLine)) {
				xPos = vertLine1->xPosition;
				StraightLine2D line2D = std::get<StraightLine2D>(secondLine);
				yPos = line2D.slope * xPos + line2D.bias;
			}
			else { // secondLine has to be vertical
				VerticalLine2D vertLine2 = std::get<VerticalLine2D>(secondLine);
				StraightLine2D line2D = std::get<StraightLine2D>(firstLine);
				xPos = vertLine2.xPosition;
				yPos = line2D.slope * xPos + line2D.bias;
			}
			return Position2D{ xPos,yPos };
		}
		
		StraightLine2D line1 = std::get<StraightLine2D>(firstLine);
		StraightLine2D line2 = std::get<StraightLine2D>(secondLine);

		auto m1 = line1.slope;
		auto b1 = line1.bias;
		auto m2 = line2.slope;
		auto b2 = line2.bias;
		// TODO check for invalid solutions
		if (m1 == m2 && b1 == b2) {
			return line1; // same lines
		}
		// otherwise create a new pair of where the lines intersect
		auto x = (b1 - b2) / (m2 - m1);
		auto y = m1 * x + b1;
		return Position2D{ x,y };
	}
	
	bool RectangleHitter::insideRectangle(const Position2D& pos) {
		return pos.y >= - (*this).shape.height + (*this).shape.pos.y && pos.y <= (*this).shape.pos.y
			&& pos.x <= (*this).shape.width + (*this).shape.pos.x && pos.x >= (*this).shape.pos.x;
	}

	void RectangleHitter::wallHitReflection(size_t reflections) {
		// startLine
		// hit right side
		
		HitLine2D startHitLine;
		if (this->hitLines.size() > reflections) {
			return;
		}
		else {
			startHitLine = this->hitLines[this->hitLines.size() - 1];
		}
		HitLine2D currentHitLine(startHitLine);

		auto leftLine = VerticalLine2D{this->shape.pos.x};
		auto rightLine = VerticalLine2D{this->shape.pos.x + this->shape.width};
		auto botLine = StraightLine2D{0,this->shape.pos.y - this->shape.height};
		auto topLine = StraightLine2D{0,this->shape.pos.y};


		int foundReflections(0); // if the line the the edge directly 2 lines will be hit
		int lastHitSide = 0; // topside = 1, rightSide = 2, botSide = 3, leftSide = 4
		for (size_t startInd = this->hitLines.size(); startInd < reflections; startInd++) {
			foundReflections = 0;
			auto straightPointLine = hitLineToStraightLine(startHitLine);
			// TODO fix the case where the edge is thit directly, fix equal signs!
			int quadrant(0);
			double reflectedAngle;
			//if (currentHitLine.angle > 0 && currentHitLine.angle < 90) {
			//	quadrant = 1;// the lower left quadrant
			//}
			//else if (currentHitLine.angle > 90 && currentHitLine.angle < 180) {
			//	quadrant = -1;
			//}
			//else if (currentHitLine.angle > 180 && currentHitLine.angle < 270) {
			//	quadrant = 1;
			//}
			//else { // between 270 and 360 stuck for exact 90,180, 270,360...
			//	quadrant = -1;
			//}
			//
			//double reflectedAngle = AngleHelper::addDegreesOnAngle(currentHitLine.angle,90 * quadrant);
			// this syntax didnt work?
			//if (auto notEmptyObject = solveIntersectionPoint(rightLine, straightPointLine)) { // resolve optional
			//	if (const Position2D* pos = std::get_if<Position2D>(&notEmptyObject.value())) { // only reflect in case of a 2d Position
			//		
			//		// reflections on the right Line will only happend if the line faces to the right, only take reflections which arent the same as the start position
			//		if ((*this).insideRectangle(*pos) && facesRight(startHitLine) && !((*pos) == startHitLine.pos)) {
			//			currentHitLine = HitLine2D{ *pos,reflectedAngle };
			//			foundReflections += 1;
			//		}
			//	}
			//}
			//else if (auto notEmptyObject = solveIntersectionPoint(botLine, straightPointLine)) { // resolve optional
			//	std::cout << "checking bot line";
			//	if (const Position2D* pos = std::get_if<Position2D>(&notEmptyObject2.value())) { // only reflect in case of a 2d Position
			//		if ((*this).insideRectangle(*pos) && facesBot(startHitLine) && !((*pos) == startHitLine.pos)) {
			//			currentHitLine = HitLine2D{ *pos,reflectedAngle };
			//			foundReflections += 1;
			//		}
			//	}
			//}
			//else if (auto notEmptyObject = solveIntersectionPoint(leftLine, straightPointLine)) { // resolve optional
			//	if (const Position2D* pos = std::get_if<Position2D>(&notEmptyObject3.value())) { // only reflect in case of a 2d Position
			//		if ((*this).insideRectangle(*pos) && facesLeft(startHitLine) && !((*pos) == startHitLine.pos)) {
			//			currentHitLine = HitLine2D{ *pos,reflectedAngle };
			//			foundReflections += 1;
			//		}
			//	}
			//}
			//else if (auto notEmptyObject = solveIntersectionPoint(topLine, straightPointLine)) { // resolve optional
			//	if (const Position2D* pos = std::get_if<Position2D>(&notEmptyObject4.value())) { // only reflect in case of a 2d Position
			//		if ((*this).insideRectangle(*pos) && facesTop(startHitLine) && !((*pos) == startHitLine.pos)) {
			//			currentHitLine = HitLine2D{ *pos,reflectedAngle };
			//			foundReflections += 1;
			//		}
			//	}
			//}
			auto rightHit = solveIntersectionPoint(rightLine, straightPointLine);
			auto botHit = solveIntersectionPoint(botLine, straightPointLine);
			auto leftHit = solveIntersectionPoint(leftLine, straightPointLine);
			auto topHit = solveIntersectionPoint(topLine, straightPointLine);

			std::optional<Position2D> cornerPosition; // only a hit if two lines are hit at the same time
			if (rightHit) { // resolve optional
				if (const Position2D* pos = std::get_if<Position2D>(&rightHit.value())) { // only reflect in case of a 2d Position
					// reflections on the right Line will only happend if the line faces to the right, only take reflections which arent the same as the start position
					if ((*this).insideRectangle(*pos) && facesRight(startHitLine) && lastHitSide != 2) {
						if (startHitLine.angle > 0 && startHitLine.angle < 90) {
							reflectedAngle = 360 - startHitLine.angle;
						}
						else { // between 270 and 360
							reflectedAngle = 360 - startHitLine.angle;
						}
						//if (currentHitLine.angle > 0 && currentHitLine.angle <90) {
						//	quadrant = -1;
						//}
						//else {
						//	quadrant = 1;
						//}
						//reflectedAngle = AngleHelper::addDegreesOnAngle(currentHitLine.angle, 90 * quadrant);
						//std::cout << "the angle right" << reflectedAngle << "\n";
						currentHitLine = HitLine2D{ *pos,reflectedAngle };
						foundReflections += 1;
						lastHitSide = 2;
					}
				}
			}
			if (botHit) { // resolve optional
				if (const Position2D* pos = std::get_if<Position2D>(&botHit.value())) { // only reflect in case of a 2d Position
					if ((*this).insideRectangle(*pos) && facesBot(startHitLine) && lastHitSide != 3) {
						/*if (currentHitLine.angle > 90 && currentHitLine.angle < 180) {
							quadrant = -1;
						}
						else{
							quadrant = 1;
						}*/
						if (startHitLine.angle > 90 && startHitLine.angle < 180) {
							reflectedAngle = 180 - startHitLine.angle;
						}
						else { // between 180 and 270
							//reflectedAngle = -180 + startHitLine.angle;
							reflectedAngle = 270 + (270 - startHitLine.angle);
						}
						//reflectedAngle = AngleHelper::addDegreesOnAngle(currentHitLine.angle, 90 * quadrant);
						currentHitLine = HitLine2D{ *pos,reflectedAngle };
						foundReflections += 1;
						lastHitSide = 3;
					}
					if (foundReflections == 2) {
						cornerPosition = *pos;
					}
				}
			}
			if (leftHit) { // resolve optional
				if (const Position2D* pos = std::get_if<Position2D>(&leftHit.value())) { // only reflect in case of a 2d Position
					if ((*this).insideRectangle(*pos) && facesLeft(startHitLine) && lastHitSide != 4) {
						/*if (currentHitLine.angle > 180 && currentHitLine.angle < 270) {
							quadrant = -1;
						}
						else {
							quadrant = 1;
						}*/
						if (startHitLine.angle > 180 && startHitLine.angle < 270) {
							// 360 - angle
							reflectedAngle = AngleHelper::addDegreesOnAngle(-startHitLine.angle, 360);
						}
						else { // between 270 and 360
							reflectedAngle = 360 - startHitLine.angle;
						}
						currentHitLine = HitLine2D{ *pos,reflectedAngle };
						foundReflections += 1;
						lastHitSide = 4;
					}
					if (foundReflections == 2) {
						cornerPosition = *pos;
					}
				}
			}
			if (topHit) { // resolve optional
				if (const Position2D* pos = std::get_if<Position2D>(&topHit.value())) { // only reflect in case of a 2d Position
					if ((*this).insideRectangle(*pos) && facesTop(startHitLine) && lastHitSide != 1) {
						//if (currentHitLine.angle > 270 && currentHitLine.angle < 360) {
						//	quadrant = -1;
						//}
						//else {
						//	quadrant = 1;
						//}
						if (startHitLine.angle > 0 && startHitLine.angle < 90) {
							reflectedAngle = 180 - startHitLine.angle;
						}
						else { // between 270 and 360
							//180 - angle
							reflectedAngle = AngleHelper::addDegreesOnAngle(-startHitLine.angle,180);
						}
						
						currentHitLine = HitLine2D{ *pos,reflectedAngle };
						foundReflections += 1;
						lastHitSide = 1;
					}
					if (foundReflections == 2) {
						cornerPosition = *pos;
					}
				}
			}
			if (foundReflections == 2) { // an edge was hit directly, reflect in with the 180 degree rotated angle
				reflectedAngle = AngleHelper::addDegreesOnAngle(currentHitLine.angle, 180);
				currentHitLine = HitLine2D{ *(cornerPosition),reflectedAngle };
			}

			startHitLine = currentHitLine;
			this->hitLines.push_back(currentHitLine);
			// end for loop
		}
	}
	
	std::vector<SimpleLine2D> RectangleHitter::getLines(size_t amount) {	
		this->wallHitReflection(amount + 1); // 1 reflection creates a single point , however we want the amount of lines
											 // f.e. 1 line => 2 points / reflections, 2 lines => 3 points , ...
		std::vector<SimpleLine2D> result;
		Position2D startPoint;
		if (this->startLine().pos.y <= 0) {
			startPoint = Position2D{ this->startLine().pos.x,this->startLine().pos.y * -1 };
		}
		else {
			startPoint = this->startLine().pos; // should probably cancel the excution instead, the coordinated should be negative
		}
		if (this->hitLines.size() < 2) {
			return result;
		}
		Position2D posPoint;
		for (auto hitLineIt = std::next(this->hitLines.cbegin(),1); hitLineIt != this->hitLines.cend(); hitLineIt=std::next(hitLineIt,1)) {
			
			if ((*hitLineIt).pos.y < 0) { // the screen has positive coodinated
				posPoint = Position2D{ (*hitLineIt).pos.x , -1 * (*hitLineIt).pos.y }; 
			}
			else {
				posPoint = (*hitLineIt).pos;
			}
			SimpleLine2D reflectionSimpleLine{ startPoint, posPoint};
			startPoint = posPoint;
			result.push_back(reflectionSimpleLine);
		}
		return result;
	}


}