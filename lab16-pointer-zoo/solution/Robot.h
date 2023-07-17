#pragma once

struct Robot {
    virtual ~Robot() = default;
    virtual int charge_remaining() const = 0;
};

