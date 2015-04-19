#pragma once

#include "Enemy.h"

class SimpleRouter : public Router {
public:
	SimpleRouter(float start_x, int stay_time, float y_speed = 8, float y_s = -10, float y_e = 100, float leave_dx = -1.5) {
		x_ = start_x;
		stime_ = stay_time;
		ey_ = y_e;
		cy_ = y_s;
		dy_ = y_speed;
		state_ = 0;
		strong_ = true;
		ldx_ = leave_dx;
	}

	float GetX() const { return x_; }
	float GetY() const { return cy_; }
	bool Strong() const { return strong_; }

	bool Update() {
		switch (state_) {
		case 0:
			cy_ += dy_;
			if (cy_ >= 20)  {
				strong_ = false;
			}
			if (cy_ >= ey_) {
				state_ = 1;
			}
			break;
		case 1:
			if (stime_ < 100) {
				x_ += 0.5;
				cy_ += 0.1;
			}
			if (--stime_ == 0) {
				state_ = 2;
			}
			break;
		default:
			cy_ -= dy_;
			x_ += ldx_;
			if (cy_ < -15) {
				return false;
			}
		}
		return true;
	}
private:
	float x_;
	int stime_;
	float ey_, cy_, dy_;
	float ldx_;
	int state_;
	bool strong_;
};

class DirectRoute : public Router {
public:
	DirectRoute(float x, float y, float dx, float dy, float ddx, float ddy, int strong_fs)
		: x_(x), y_(y), dx_(dx), dy_(dy), ddx_(ddx), ddy_(ddy), fs_(strong_fs) {
		frame_cnt_ = 0;
	}

	float GetX() const { return x_; }
	float GetY() const { return y_; }
	bool Strong() const { return fs_ > 0; }

	bool Update() {
		if (fs_ > 0) --fs_;

		dx_ += ddx_;
		dy_ += ddy_;
		x_ += dx_;
		y_ += dy_;

		if (x_ < -32 || y_ < -32 || x_ > W + 32 || y_ > H + 32) {
			++frame_cnt_;
			if (frame_cnt_ > 300) return false;
		}
		else {
			frame_cnt_ = 0;
		}
		return true;
	}

private:
	float x_, y_, dx_, dy_, ddx_, ddy_;
	int fs_;
	int frame_cnt_;
};

class RouterComb : public Router {
public:
	RouterComb(shared_ptr<Router> r1, shared_ptr<Router> r2, int frames) {
		curr_ = r1;
		next_ = r2;
		f_ = frames;
	}

	float GetX() const { return curr_->GetX(); }
	float GetY() const { return curr_->GetY(); }
	bool Strong() const { return curr_->Strong(); }

	bool Update() {
		if (f_ > 0) {
			--f_;
			if (f_ == 0) {
				curr_ = next_;
			}
		}
		return curr_->Update();
	}
private:
	shared_ptr<Router> curr_;
	shared_ptr<Router> next_;
	int f_;
};

class BigFlyerRouter : public Router {
public:
	BigFlyerRouter(float x, float y, int strong_frames, int stay_frames = 30 * 60) {
		x_ = x;
		y_ = y;
		state_ = 0;
		fs_ = strong_frames;
		stay_frames_ = stay_frames;
	}

	float GetX() const { return x_; }
	float GetY() const { return y_; }
	bool Strong() const { return fs_ > 0; }

	bool Update() {
		if (fs_ > 0) --fs_;

		if (state_ == 0) {
			y_ += 3.5;
			if (y_ >= 200) {
				state_ = 1;
				vx_ = 0.2;
				vy_ = -0.1;
			}
			return true;
		}

		if (stay_frames_ <= 0) {
			y_ -= 1;
			if (y_ < -100) {
				return false;
			}
			return true;
		}

		stay_frames_ -= 1;
		x_ += vx_;
		y_ += vy_;
		if (x_ < 150) {
			vx_ = 0.2;
		}
		else if (x_ > 250) {
			vx_ = -0.2;
		}

		if (y_ < 80) {
			vy_ = 0.1 * (rand() % 1000 / 1000.0);
		} else if (y_ > 240) {
			vy_ = -0.1 * (rand() % 1000 / 1000.0);
		}

		return true;
	}

private:
	float x_;
	float y_;
	float vx_;
	float vy_;
	int fs_;
	int state_;
	int stay_frames_;
};

/// --------------------------------------
/// snake routers
class SnakeRouter : public Router {
public:
	SnakeRouter() {}
	virtual bool Update() {
		bool res = _Update();
		float _nx = GetX();
		float _ny = GetY();
		_angle = atan2(_ny - _ly, _nx - _lx);
		_ly = _ny;
		_lx = _nx;
		return res;
	}; // t for still alive, f for disappear
	
	virtual float Rotate() const { 
		return _angle * 180 / PI + 90;
	}

protected:
	virtual bool _Update() = 0;

	float _lx, _ly;
	float _angle;
};

class SnakeRouter1 : public SnakeRouter {
public:
	SnakeRouter1(float x, float dy, float a_scale, int strong_frames) 
		: x_(x), dy_(dy), a_scale_(a_scale), strong_frames_(strong_frames) {
		state_ = 0;
		y_ = -40;

		vx_ = 0;
		vy_ = 1.5;
	}

	float GetX() const override {
		return x_;
	}

	float GetY() const override {
		return y_;
	}

	bool Strong() const override {
		return strong_frames_ > 0;
	}

	bool _Update() override {
		if (strong_frames_ > 0) {
			--strong_frames_;
		}

		x_ += vx_;
		y_ += vy_;
		if (state_ == 0) {
			if (y_ > dy_) {
				state_ = 1;
				frame_cnt_ = 0;
			}
			return true;
		} else if (state_ == 1) {
			float ax = -vy_ * a_scale_;
			float ay = vx_ * a_scale_;
			vx_ += ax;
			vy_ += ay;

			frame_cnt_ += 1;
			if (frame_cnt_ > 600) {
				state_ = 2;
				frame_cnt_ = 0;
			}
		}
		else {
			if (x_ < -32 || y_ < -32 || x_ > W + 32 || y_ > H + 32) {
				++frame_cnt_;
				if (frame_cnt_ > 600) return false;
			}
			else {
				frame_cnt_ = 0;
			}
		}

		return true;
	}

private:
	float x_, y_, dy_, a_scale_;
	float vx_, vy_;
	int state_;
	int strong_frames_;
	int frame_cnt_;
};