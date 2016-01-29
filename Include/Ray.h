#pragma once

#include <SFML/System/Vector2.hpp>

#include "Vector2fOperations.h"

#include "Object.h"
#include "BurnableObject.h"

class Ray
{
    private:
        sf::Vector2f m_origin;
        sf::Vector2f m_direction;

        bool m_intersectionFound;
        float m_minT;

        Object * m_obj;

    public:
        /**
         * @brief constuctor for Ray
         *
         * @param origin: origin of the ray
         * @param direction: vector director of the ray
         */
        Ray(sf::Vector2f const& origin, sf::Vector2f const& direction);

        /**
         * @brief has a valid intersection be found?
         *
         * @return true if an intersection has been found, false otherwise
         */
        bool validIntersectionFound() const;

        /**
         * @brief is the thing at the intersection an object ?
         *
         * @return true if the intersection has been with an object
         */
        bool intersectionIsObject() const;

        /**
         * @brief gets the object at the intersection
         *
         * @return a pointer to the intersected object
         */
        Object * intersectionObject() const;


        /**
         * @brief gets the intersection
         *
         * @return the position of the intersection
         * @warning behavior undefined if validIntersectionFound() = false
         */
        sf::Vector2f intersection() const;

		float distanceToIntersection() const;

		void resetDistance();

        /**
         * @return the origin of the ray
         */
        sf::Vector2f getOrigin() const;

        /**
         * @return the vector director of the ray
         */
        sf::Vector2f getDirection() const;
        

        /**
         * @brief computes the intersection between this ray and a circle
         *
         * @param circleCenter: the center of the intersected circle
         * @param radius: the radius of the intersected circle
         * @param saveIntersection: should the ray remember that the intersection happened ?
         *
         * @return true if the ray intersects the circle
         */
        bool intersectCircle(sf::Vector2f circleCenter, float radius, bool saveIntersection = true);

        /**
         * @brief computes the intersection between this ray and an axis-aligned rectangle
         *
         * @param pointMin: the first corner of the rectangle
         * @param pointMax: the corner opposite of pointMin
         * @param saveIntersection: should the ray remember that the intersection happened ?
         *
         * @return true if the ray intersects the rectangle
         */
        bool intersectSquare(sf::Vector2f pointMin, sf::Vector2f pointMax, bool saveIntersection = true, Object * obj = nullptr);

    private:
        /**
         * @brief adds a new intersection to the ray
         *
         * @param t: the value of the t param at the moment of the intersection [ (x,y) = origin() + t*direction() ]
         * @param obj: a pointer to the intersected object (if applicable)
         */
        void setIntersection(float t, Object * obj = nullptr);
};
