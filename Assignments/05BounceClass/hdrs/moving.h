#ifndef MOVING_TEMPLATE_CLASS_H
#define MOVING_TEMPLATE_CLASS_H

#include <SFML/Graphics.hpp>


/* why did I make the core type of the Moving class a template
 * instead of simply some sort of constructor paramteter?
 * because sf::Shape is and abstract class, and therefore I would
 * have to carry around either a reference to an outside object
 * or a pointer. If anything happend to those objects; they went
 * out of scope, they are no longer valid, they were temporaries,
 * and especially, they were deleted, now this object is broken...
 * Also, this way, we have one object that contains all we need
 * that allows for restrictive copying between objects, since now
 * each object with a different instance of "T" has its own instance
 * of the class. It just makes more sense to do it this way.
 * Though, we will be paying for it in compilation times....*/

/* The main restrictions to typename "T" is that "T" NEEDS TO inherit
 * from sf::Transformable and sf::Drawable publicly.*/
template<typename T>
class Moving : public sf::Drawable
{
public:
    Moving(const sf::Vector2f& velocity_vector_2D = {0, 0});

    T& getShape(void);
    const T& getShape(void) const;
    void setShape(const T& shape);
    void setVelocityVector2D(const sf::Vector2f& velocity_vector_2D);
    const sf::Vector2f& getVelocityVector2D(void);

    /* Either template "T" must have a getGlobalBounds method defined
     * in order for this method to use 
     * OR
     * You can define a specifc instance of this class for a specific
     * type that doesn't have getGlobalBounds() method by doing so:
     * 
     * template<>
     * sf::FloatRect Moving<"A Specific Type">::getGlobalBounds(void) const
     * {
     *      ... (your implentation)
     *      return sf::FloatRect;
     * }
    */
    sf::FloatRect getGlobalBounds(void) const;

    void updatePosition(void); //use this before drawing
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    T generic_instance;
    sf::Vector2f velocity_vector_2D;

    /* Fail Compilation Quickly, by checking if template input "T" inherits from
     * both sf::Transformable and sf::Drawable. I noticed that would fail compilation
     * if input class was not drawable, but would require to use updatePosition method
     * in order to check if "T" was Transformable. Do this to make compilation
     * results more stable, and hopefully more readable */
    inline void checkIf_TransformableAndDrawable(sf::Transformable& t, sf::Drawable& d);
};

typedef Moving<sf::CircleShape> MovingCircle;
typedef Moving<sf::ConvexShape> MovingConvex;
typedef Moving<sf::RectangleShape> MovingRectangle;

#include "moving.cpp"

#endif //MOVING_TEMPLATE_CLASS_H