#pragma once

#include "Driver.hpp"

#include <cmath>
#include <cstdlib>
#include <map>
#include <memory>
#include <random>
#include <vector>

namespace lf::game::driver {

class Bot : public Driver {
public:
    using States = engine::DistanceMeter::Distances;
    using Actions = std::map<Choice::Direction, float>;

    Bot()
    {
        std::cout << "Initializing Q Table... ";
        auto init_actions = Actions{{Choice::Direction::Left, 0.0F},
                                    {Choice::Direction::Right, 0.0F},
                                    {Choice::Direction::Straight, 0.0F}};
        for (unsigned i_front = 0; i_front < 200U; i_front += 20) {
            for (unsigned i_left = 0; i_left < 200U; i_left += 20) {
                for (unsigned i_front_left = 0; i_front_left < 200U; i_front_left += 20) {
                    for (unsigned i_right = 0; i_right < 200U; i_right += 20) {
                        for (unsigned i_front_right = 0; i_front_right < 200U;
                             i_front_right += 20) {
                            std::cout << i_front << " " << i_left << " " << i_front_left
                                      << " " << i_right << " " << i_front_right << "\n";
                            q_table.emplace(States{static_cast<float>(i_front),
                                                   static_cast<float>(i_left),
                                                   static_cast<float>(i_front_left),
                                                   static_cast<float>(i_right),
                                                   static_cast<float>(i_front_right)},
                                            init_actions);
                        }
                    }
                }
            }
        }
        std::cout << "done\n";

        std::srand(std::time(nullptr));
    }

    Steering get_steering(const engine::DistanceMeter::Measures& measures) override
    {
        set_driver_choice(measures);
        set_car_steering();
        return std::move(car_steering);
    }

    static std::unique_ptr<Driver> create() { return std::make_unique<Bot>(); }

    float total_reward{0.0F};

private:
    void set_driver_choice(const engine::DistanceMeter::Measures& measures)
    {
        static auto epsilon{1.0f};
        static const auto epsilon_decay{0.999F};
        static const auto learning_rate{0.1F};
        static const auto gamma{0.6F};

        // calculate_reward(measures);
        // determine_state(measures);

        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> distrib(0, 1);

        auto reward{0.0F};

        std::cout << "------------------------\n";

        if (previous_measures.segment != measures.segment) {
            if (previous_measures.segment == engine::DistanceMeter::Segment::First
                    and measures.segment == engine::DistanceMeter::Segment::Second
                or previous_measures.segment == engine::DistanceMeter::Segment::Second
                       and measures.segment == engine::DistanceMeter::Segment::Third
                or previous_measures.segment == engine::DistanceMeter::Segment::Third
                       and measures.segment == engine::DistanceMeter::Segment::First) {
                reward += 1.0F;
            }
        }
        total_reward += reward;
        std::cout << "Total reward: " << total_reward << "\n";

        auto new_state = measures.distances;
        const auto division_factor{10.0F};
        const auto attraction_value{20.0F};
        new_state.front_left =
            std::round((new_state.front_left / division_factor) / attraction_value)
            * attraction_value;
        new_state.front =
            std::round((new_state.front / division_factor) / attraction_value)
            * attraction_value;
        new_state.front_right =
            std::round((new_state.front_right / division_factor) / attraction_value)
            * attraction_value;
        new_state.right =
            std::round((new_state.right / division_factor) / attraction_value)
            * attraction_value;
        new_state.left = std::round((new_state.left / division_factor) / attraction_value)
                         * attraction_value;

        if (new_state.front_left > 180.0F) {
            new_state.front_left = 180.0F;
        }
        if (new_state.left > 180.0F) {
            new_state.left = 180.0F;
        }
        if (new_state.front > 180.0F) {
            new_state.front = 180.0F;
        }
        if (new_state.front_right > 180.0F) {
            new_state.front_right = 180.0F;
        }
        if (new_state.right > 180.0F) {
            new_state.right = 180.0F;
        }

        std::cout << "Distances: " << measures.distances.front_left << " "
                  << measures.distances.front << " " << measures.distances.front_right
                  << " " << measures.distances.right << " " << measures.distances.left
                  << "\n";

        std::cout << "New state: " << new_state.front_left << " " << new_state.front
                  << " " << new_state.front_right << " " << new_state.right << " "
                  << new_state.left << "\n";

        std::cout << "Previous state: " << previous_state.front_left << " "
                  << previous_state.front << " " << previous_state.front_right << " "
                  << previous_state.right << " " << previous_state.left << "\n";

        const auto q_value = q_table.at(previous_state).at(last_action);
        auto best_q{0.0F};

        const auto& actions_weights = q_table.at(new_state);
        if (actions_weights.at(Choice::Direction::Straight)
                > actions_weights.at(Choice::Direction::Left)
            and actions_weights.at(Choice::Direction::Straight)
                    > actions_weights.at(Choice::Direction::Right)) {
            best_q = actions_weights.at(Choice::Direction::Straight);

        } else if (actions_weights.at(Choice::Direction::Left)
                   > actions_weights.at(Choice::Direction::Right)) {
            best_q = actions_weights.at(Choice::Direction::Left);
        } else {
            best_q = actions_weights.at(Choice::Direction::Right);
        }

        std::cout << "Best Q = " << best_q << "\n";

        q_table[previous_state][last_action] =
            (1 - learning_rate) * q_value + learning_rate * (reward + gamma * best_q);

        std::string choice_str;

        if (distrib(gen) < epsilon) {
            // perform random action
            // const auto random_choice = std::rand() % 2;
            switch (std::rand() % 2) {
            case 0:
                driver_choice.direction = Choice::Direction::Right;
                choice_str = "Right";
                break;
            case 1:
                driver_choice.direction = Choice::Direction::Left;
                choice_str = "Left";
                break;
            case 2:
                driver_choice.direction = Choice::Direction::Straight;
                choice_str = "Straight";
            }
        } else {
            // get an action from the q_table

            const auto& actions_weights = q_table.at(new_state);
            if (actions_weights.at(Choice::Direction::Straight)
                    > actions_weights.at(Choice::Direction::Left)
                and actions_weights.at(Choice::Direction::Straight)
                        > actions_weights.at(Choice::Direction::Right)) {
                driver_choice.direction = Choice::Direction::Straight;
                choice_str = "Straight";

            } else if (actions_weights.at(Choice::Direction::Left)
                       > actions_weights.at(Choice::Direction::Right)) {
                driver_choice.direction = Choice::Direction::Left;
                choice_str = "Left";
            } else {
                driver_choice.direction = Choice::Direction::Right;
                choice_str = "Right";
            }


        }
            std::cout << "Choice: " << choice_str << "\n";

        //
        //        if (measures.out_of_track == true) {
        //            std::cout << "Penalty!\n"; // reset game!
        //        }
        //
        //        if (measures.distances.front > measures.distances.front_left
        //            and measures.distances.front > measures.distances.left
        //            and measures.distances.front > measures.distances.front_right
        //            and measures.distances.front > measures.distances.right) {
        //            driver_choice.direction = Choice::Direction::Straight;
        //        } else if (measures.distances.right > measures.distances.left
        //                   and measures.distances.right >
        //                   measures.distances.front_left)
        //                   {
        //            driver_choice.direction = Choice::Direction::Right;
        //        } else if (measures.distances.left > measures.distances.front_right)
        //        {
        //            driver_choice.direction = Choice::Direction::Left;
        //        } else if (measures.distances.front_right >
        //        measures.distances.front_left) {
        //            driver_choice.direction = Choice::Direction::Right;
        //        } else {
        //            driver_choice.direction = Choice::Direction::Left;
        //        }

        previous_measures = measures;
        previous_state = new_state;
        last_action = driver_choice.direction;
    }

    void set_car_steering()
    {
        car_steering.accelerating = true;
        switch (driver_choice.direction) {
        case Choice::Direction::Right: {
            car_steering.wheels_angle = 1.0F;
            break;
        }
        case Choice::Direction::Left:
            car_steering.wheels_angle = -1.0F;
            break;

        case Choice::Direction::Straight:
            car_steering.wheels_angle = 0.0F;
            break;
        }
    }

    Choice driver_choice{};
    Steering car_steering{};

    engine::DistanceMeter::Measures previous_measures;
    States previous_state;
    Choice::Direction last_action{Choice::Direction::Straight};
    std::map<States, Actions> q_table;
};

} // namespace lf::game::driver
