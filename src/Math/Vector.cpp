#include "Math/Vector.hpp"

Vector Vector::operator+(const Vector &vec) {
    return Vector(m_x + vec.m_x, m_y + vec.m_y);
}

Vector Vector::operator+=(const Vector &vec) {
    return Vector(m_x + vec.m_x, m_y + vec.m_y);
}

Vector Vector::operator-(const Vector &vec) {
    return Vector(m_x - vec.m_x, m_y - vec.m_y);
}

Vector Vector::operator-=(const Vector &vec) {
    return Vector(m_x - vec.m_x, m_y - vec.m_y);
}

Vector Vector::operator*(float scalar) {
    return Vector(m_x * scalar, m_y * scalar);
}

Vector Vector::operator/(float scalar) {
    return Vector(m_x / scalar, m_y / scalar);
}

float Vector::GetLength() { return sqrt(m_x * m_x + m_y * m_y); }

float Vector::GetLength(Vector &vec) {
    return sqrt((vec.m_x * vec.m_x) + (vec.m_y * vec.m_y));
}

Vector Vector::GetNormalized() {
    float l = GetLength();
    if (l > 0) {
        Vector normalized = (*this) * (1 / l);
            return normalized;
  }
        return Vector(0, 0);
}

float Vector::GetAngleDegrees(Vector &vec){
float angle  = atan((vec.m_y - m_y)/(vec.m_x - m_x))*180/3.14;

  //1 quadrante
    if(vec.m_x >=m_x && vec.m_y <= m_y )
        angle = angle;
  //2 quadrante
    if(vec.m_x<m_x && vec.m_y> m_y)
        angle = 180 + angle;
  //3 quadrante
    if(vec.m_x<m_x && vec.m_y< m_y )
       angle = 180  + angle;
  //4 quadrante
    if(vec.m_x >=m_x && vec.m_y <= m_y )
       angle =360 + angle;

return angle;
}

float Vector::GetAngleRadians(Vector &vec){

    return GetAngleDegrees(vec)*3.14/180;

}

float Vector::GetDistance(Vector vec) {
    Vector subtraction = vec - *this;
        return GetLength(subtraction);
}
