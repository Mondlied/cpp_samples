//
// Copyright 2021 Mondlied@github.com
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
#pragma once

#include <string>
#include <vector>

namespace CppSamples
{
    /**
     * \brief an actual program to run
     */
    class Program
    {
    public:
        Program(std::string&& name, std::string&& description)
            : m_name(std::move(name)), m_description(std::move(description))
        {
        }

        virtual int Run(std::vector<std::string>& args) = 0;

        std::string const& Name() const
        {
            return m_name;
        }

        void PrintDescription() const;
    private:
        std::string m_name;
        std::string m_description;
    };

}