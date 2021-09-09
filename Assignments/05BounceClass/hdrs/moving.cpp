#ifndef MOVING_TEMPLATE_CLASS_IMPLENTATION
#define MOVING_TEMPLATE_CLASS_IMPLENTATION

#include "moving.h"

template<typename T>
Moving<T>::Moving(const sf::Vector2f& velocity_vector_2D)
    : velocity_vector_2D(velocity_vector_2D)
{
    checkIf_TransformableAndDrawable(generic_instance, generic_instance);
}
//EOF

template<typename T>
T& Moving<T>::getShape(void)
    {return generic_instance;}
//EOF

template<typename T>
const T& Moving<T>::getShape(void) const
    {return generic_instance;}
//EOF

template<typename T>
void Moving<T>::setShape(const T& shape)
    {generic_instance = shape;}
//EOF

template<typename T>
void Moving<T>::setVelocityVector2D(const sf::Vector2f& velocity_vector_2D)
    {this->velocity_vector_2D = velocity_vector_2D;}
//EOF

template<typename T>
const sf::Vector2f& Moving<T>::getVelocityVector2D(void)
    {return velocity_vector_2D;}

template<typename T>
sf::FloatRect Moving<T>::getGlobalBounds(void) const
    {return generic_instance.getGlobalBounds();}

template<typename T>
void Moving<T>::updatePosition(void)
    {generic_instance.move(velocity_vector_2D);}
//EOF

template<typename T>
void Moving<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {target.draw(generic_instance, states);}
//EOF

template<typename T>
inline void Moving<T>::checkIf_TransformableAndDrawable(sf::Transformable& t, sf::Drawable& d)
{}
//EOF
#endif //MOVING_TEMPLATE_CLASS_IMPLENTATION