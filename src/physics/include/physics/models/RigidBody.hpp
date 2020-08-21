#pragma once
#include <SFML/System.hpp>

namespace lf::physics {

class RigidBody {
public:
    RigidBody(float length_cm, float width_cm, float mass_kg)
        : dimensions_cm{length_cm, width_cm}, mass_kg{mass_kg}
    {
        // todo: mass_kg and inertia cant be zero
        calc_inertia();
    }

    void update(float time_step_ms);
    void apply_force(const sf::Vector2f& force_N, const sf::Vector2f& offset_cm);

private:
    void calc_inertia();

    sf::Vector2f dimensions_cm;

    sf::Vector2f position_cm;
    sf::Vector2f velocity_m_s;
    sf::Vector2f forces_N;
    float mass_kg;

    float angle_rad{0.0};
    float angular_velocity_rad_s{0.0};
    float torque_N_cm{0.0};
    float inertia_kg_cm2;
};

} // namespace lf::physics
