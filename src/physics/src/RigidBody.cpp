#include "RigidBody.hpp"

using namespace lf::physics;

void RigidBody::calc_inertia()
{
    inertia_kg_cm2 =
        (1.0f / 12.0f) * mass_kg
        * (dimensions_cm.x * dimensions_cm.x + dimensions_cm.y * dimensions_cm.y);
}

void RigidBody::update(float time_step_ms)
{
    auto acceleration_m_s2 = forces_N / mass_kg;
    velocity_m_s += acceleration_m_s2 * time_step_ms / 1000.0f;
    position_cm += velocity_m_s * 100.0f * time_step_ms / 1000.0f;
    forces_N = sf::Vector2f{0, 0};

    auto angular_accel_rad_s2 = torque_N_cm * 100.0f / inertia_kg_cm2;
    angular_velocity_rad_s += angular_accel_rad_s2 * time_step_ms / 1000.0f;
    angle_rad += angular_velocity_rad_s * time_step_ms / 1000.0f;
    torque_N_cm = 0.0f;
}

void RigidBody::apply_force(const sf::Vector2f& force_N, const sf::Vector2f& offset_cm)
{
    forces_N += force_N;
    // torque_N_cm += force_N * offset_cm; // todo - calculate a cross product
}
