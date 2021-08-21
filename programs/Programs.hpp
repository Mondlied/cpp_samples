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

#include <memory>
#include <string>
#include <unordered_map>

namespace CppSamples
{
    class Program;

    /**
     * \brief a singleton for collecting and running programs
     */
    class Programs
    {
    public:
        ~Programs();

        static Programs& Instance();

        int RunProgram(int argc, char const* const* argv);

        void AddProgram(std::unique_ptr<Program>&& program);
    private:
        Programs();

        std::unordered_map<std::string, std::unique_ptr<Program>> m_programs;
    };

    template<typename T>
    struct ProgramRegistrar
    {
        ProgramRegistrar()
        {
            Programs::Instance().AddProgram(std::make_unique<T>());
        }
    };

    /**
     * \brief macro registering a certain subtype of CppSamples::Program for as possible sample to run 
     */
    #define CPP_SAMPLES_REGISTER_PROGRAM(ProgramType) namespace { ::CppSamples::ProgramRegistrar<ProgramType> registrar; }

}