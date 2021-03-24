#include<iostream>
#include<vector>
#include<algorithm>
#include<tgmath.h>
#define PI 3.14159265
using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

struct Vec2 {
	float x, y;
	Vec2(float x, float y) : x(x), y(y) {}
};
struct Vec3 {
	float x, y, z;
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
};

struct Arrow {
	Vec2 pos;
	float r;
	Arrow(const Vec2& pos, float r)
	: pos(pos), r(r) {}
};

struct Box {
	float x0, x1, y0, y1;
	Box(float x0, float x1, float y0, float y1) :
		x0(x0), x1(x1), y0(y0), y1(y1) {}
};

struct Circle {
	Vec2 pos;
	float r;
	Circle(const Vec2& pos, float r) : pos(pos), r(r) {}
};

class Simulation {
	const int maxTryCnt = 8;
	Box box; Circle circle;
	Arrow gun;
public:
	Simulation(const Box& box, const Circle& circle, const Arrow& gun)
	: box(box), circle(circle), gun(gun) {}

	// funcs
	bool canHit() {
		if (tryCntForHit(gun, maxTryCnt) != -1) {
			return true;
		}
		return false;
	}
	int tryCntForHit() {
		return tryCntForHit(gun, maxTryCnt);
	}

private:

	int tryCntForHit(const Arrow& arrow, int tryLeft) {
		if (tryLeft < 1) return -1;
		if (canHit(arrow)) {
			return maxTryCnt - tryLeft;
		}
		auto nxt = nextArrow(arrow);
		cout << ": (" << nxt.pos.x << ", " << nxt.pos.y << "), " << nxt.r/PI << "\n";
		return tryCntForHit(nxt, tryLeft-1);
	}

	bool canHit(const Arrow& arrow) {
		float dx = circle.pos.x - arrow.pos.x;
		float dy = circle.pos.y - arrow.pos.y;
		float dist = sqrt(dx*dx + dy*dy);
		float teta = asin(circle.r / dist);
		float gama = atan2(dy, dx);
		//cout << "ph: " << teta/PI << ", " << gama/PI << ", " << arrow.r/PI << '\n';
		float dif = abs(gama - arrow.r);
		return dif <= teta;
	}

	Arrow nextArrow(Arrow gun) {
		auto calc = [&](float b_x, float b_y, int zx, int zy) {
			float tg = abs(tan(gun.r)),
				  Itg = 1/tg;
			float dx = abs(b_x - gun.pos.x),
				  dy = abs(b_y - gun.pos.y);
			float cx = Itg * dy,
				  cy = tg * dx;
			float subX = cx - dx,
				  subY = cy - dy;
			//cout << "-> " << dx << ", " << dy << '\n';
			//cout << "-> " << cx << ", " << cy << '\n';
			//cout << "=> " << subX << ", " << subY << '\n';
			if (subX > subY) {
				cout << "1)\n";
				return Arrow(Vec2(b_x, gun.pos.y+cy*zy), (PI-abs(gun.r)) * sgn(gun.r));
			} else {
				cout << "2)\n";
				return Arrow(Vec2(gun.pos.x+cx*zx, b_y), -gun.r);
			}
		};
		if (gun.r >= 0 && gun.r < PI/2) {
			// area 1
			return calc(box.x1, box.y1, 1, 1);
		} else if (gun.r >= PI/2 && gun.r < PI) {
			// area 2
			return calc(box.x0, box.y1, -1, 1);
		} else if (gun.r < 0 && gun.r >= -PI/2) {
			// area 4
			return calc(box.x1, box.y0, 1, -1);
		} else if (gun.r < -PI/2 && gun.r >= -PI) {
			// area 3
			return calc(box.x0, box.y0, -1, -1);
		}

		return gun;
	}
};

int main() {
	Simulation sim = Simulation(
		Box(0, 10, 0, 10),
		Circle(Vec2(7, 1), 1),
		Arrow(Vec2(1, 1), PI/6)
	);
	auto res = sim.tryCntForHit();
	cout << "\n\nsimulation res:\n";
	cout << "\tHit: " << (res == -1 ? "false" : "true") << '\n';
	cout << "\tnumber of bounces: " << res << '\n';
}
