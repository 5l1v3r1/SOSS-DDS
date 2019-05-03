/*
 * Copyright (C) 2018 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#ifndef SOSS__DDS__INTERNAL__PARTICIPANT_HPP
#define SOSS__DDS__INTERNAL__PARTICIPANT_HPP

#include <memory>

namespace soss {
namespace dds {


class Publisher;
class Subscriber;

class Participant {

public:
    Participant(
            const std::string& xml_file);

    virtual ~Participant();

    std::shared_ptr<Publisher> create_publisher();
    std::shared_ptr<Subscriber> create_subscriber();

    //something with the listener (as spin_once)
private:
    //fast::Participant
};


} // namespace dds
} // namespace soss

#endif // SOSS__DDS__INTERNAL__PARTICIPANT_HPP