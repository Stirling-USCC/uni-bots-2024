#include <stdint.h>

#include <Servo.h>

class Wheel {
public:
  Wheel() : m_servo(), m_pin(0), m_centre(90), m_reversed(false) {}

  Wheel(int pin, int centre, bool reversed = false)
      : m_pin(pin), m_centre(centre), m_reversed(reversed) {
    m_servo.attach(pin);
    m_servo.write(m_centre);
  }

  ~Wheel() { m_servo.detach(); }

  void stop() { m_servo.detach(); }

  void backward(uint8_t speed = 255) {
    if (!m_servo.attached()) {
      m_servo.attach(m_pin);
    }
    int fudge_factor = (speed * m_centre) / 255;
    int val;
    if (m_reversed) {
      val = m_centre + fudge_factor;
    } else {
      val = m_centre - fudge_factor;
    }
    m_servo.write(val);
  }

  void forward(uint8_t speed = 255) {
    if (!m_servo.attached()) {
      m_servo.attach(m_pin);
    }
    int fudge_factor = (speed * m_centre) / 255;
    int val;
    if (m_reversed) {
      val = m_centre - fudge_factor;
    } else {
      val = m_centre + fudge_factor;
    }
    m_servo.write(val);
  }

private:
  Servo m_servo;
  int m_pin;
  int m_centre;
  bool m_reversed;
};

class Movement {
public:
  Movement() : m_left(), m_right() {}

  Movement(int left_pin, int left_centre, int right_pin, int right_centre)
      : m_left(left_pin, left_centre, false),
        m_right(right_pin, right_centre, true) {}

  void backward(uint8_t speed = 255) {
    m_left.backward(speed);
    m_right.backward(speed);
  }

  void forward(uint8_t speed = 255) {
    m_left.forward(speed);
    m_right.forward(speed);
  }

  void left(uint8_t speed = 255) {
    m_left.backward(speed);
    m_right.forward(speed);
  }

  void right(uint8_t speed = 255) {
    m_left.forward(speed);
    m_right.backward(speed);
  }

private:
  Wheel m_left, m_right;
};

Movement movement;

void setup() { movement = Movement(5, 79, 6, 78); }

void loop() {
  movement.forward(10);
  delay(2000);
  movement.left(10);
  delay(2000);
  movement.right(10);
  delay(2000);
  movement.backward(10);
  delay(2000);
}
