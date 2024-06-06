#include "rad.h"

namespace POLYGINE {
	
	void getPolFromCart(cartesian c, polar &p) {
		p.r = sqrt(pow(c.x, 2.0) + pow(c.y, 2.0) + pow(c.z, 2.0));
		p.theta = acos(c.z/p.r);
		p.phi = copysign(acos(c.x/sqrt(pow(c.x, 2.0) + pow(c.y, 2.0))), c.y);
	}

	void getCartFromPol(polar p, cartesian &c) {
		c.x = p.r * sin(p.theta) * cos(p.phi);
		c.y = p.r * sin(p.theta) * sin(p.phi);
		c.z = p.r * cos(p.theta);
	}
	
	void fan2D(glfltvec &arr, int tris) {
		int len = (tris + 2) * M_DIM;
		float angle = (float)(M_TAU / tris);
		
		arr.clear();
		arr.reserve(len);
		
		polar p_point {1.0, 0.0, 0.0};
		cartesian c_point {0.0, 0.0, 0.0};
	
		for (int i = 0; i < len; i += M_DIM) {
			arr.push_back(c_point.x);
			arr.push_back(c_point.z);
			arr.push_back(c_point.y);
			getCartFromPol(p_point, c_point);
			p_point.theta += angle;
		}
	}
	
	/*void rotate(glfltvec &arr, float rx, float ry, float rz){
		rx *= M_DEG2RAD;
		ry *= M_DEG2RAD;
		rz *= M_DEG2RAD;
		
		for (int i = M_DIM; i < arr.size(); i += M_DIM) {
			float tx = arr[i] - arr[0];
			float ty = arr[i+1] - arr[1];
			//float tz = arr[i+2] - arr[2];
			
			arr[i] = tx * cos(ry) - ty * sin(ry) + arr[0];
			arr[i+1] = tx * sin(ry) + ty * cos(ry) + arr[1];
			//arr[i+2] = + arr[2];
		}
	}

	void scale(glfltvec &arr, float s) {
		for (int i = M_DIM; i < arr.size(); i += M_DIM) {
			arr[i] = s * (arr[i] - arr[0]) + arr[0];
			arr[i+1] = s * (arr[i+1] - arr[1]) + arr[1];
			arr[i+2] = s * (arr[i+2] - arr[2]) + arr[2];
		}
	}

	void translate(glfltvec &arr, float tx, float ty, float tz) {
		for (int i = 0; i < arr.size(); i += M_DIM) {
			arr[i] += tx;
			arr[i+1] += ty;
			arr[i+2] += tz;
		}
	}*/
}