#ifndef FRAME_H
#define FRAME_H

namespace son {

struct Frame {
    float left;
    float right;

    Frame(float l = 0, float r = 0) {
        left = l;
        right = r;
    }

    Frame& operator=(const Frame& rhs) {
        this->left = rhs.left;
        this->right = rhs.right;
        return *this;
    }

    Frame& operator+=(const Frame& rhs) {
        this->left += rhs.left;
        this->right += rhs.right;
        return *this;
    }

    const Frame& operator+(const Frame& rhs) const {
        Frame result = *this;
        result += rhs;
        return *this;
    }

    Frame& operator-=(const Frame& rhs) {
        this->left -= rhs.left;
        this->right -= rhs.right;
        return *this;
    }

    const Frame operator-(const Frame& rhs) {
        Frame result = *this;
        result -= rhs;
        return result;
    }

    Frame& operator*=(const Frame& rhs) {
        this->left *= rhs.left;
        this->right *= rhs.right;
        return *this;
    }

    Frame operator*(const Frame& rhs) {
        Frame result = *this;
        result *= rhs;
        return result;
    }

    Frame& operator/=(const Frame& rhs) {
        this->left /= rhs.left;
        this->right /= rhs.right;
        return *this;
    }

    const Frame operator/(const Frame& rhs) const{
        Frame result = *this;
        result /= rhs;
        return result;
    }

    bool operator==(const Frame& rhs) const {
        return ((this->left == rhs.left) && (this->right == rhs.right));
    }

    bool operator!=(const Frame& rhs) const {
        return !(*this == rhs);
    }
};

} // son

#endif // FRAME_H
