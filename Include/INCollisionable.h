#pragma once

class Ray;

class INCollisionable
{
    public:
        virtual void collision(Ray * ray) = 0;
};
