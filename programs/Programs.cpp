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

#include "Program.hpp"
#include "Programs.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace CppSamples
{
    Programs::Programs(){}
    Programs::~Programs(){}

    Programs& Programs::Instance()
    {
        static Programs instance;
        return instance;
    }

    int Programs::RunProgram(int argc, char const* const* argv)
    {
        if (argc < 2)
        {
            std::cerr << ("Incorrect number of command line parameters\n\n" 
                "Usage: CppSamples <program name> [program parameter]...\n");
        }
        else
        {
            std::cerr << "incorrect program name\n";
            std::cout << "Valid programs:\n\n";
            auto iter = m_programs.find(argv[1]);
            if (iter == m_programs.end())
            {
                std::vector<decltype(m_programs)::value_type*> programs;
                programs.reserve(m_programs.size());
                for (auto& entry : m_programs)
                {
                    programs.push_back(&entry);
                }
                std::sort(programs.begin(), programs.end(), [](auto entryPtr1, auto entryPtr2)
                    {
                        return entryPtr1->first < entryPtr1->first;
                    });
                for (auto progEntryPtr : programs)
                {
                    progEntryPtr->second->PrintDescription();
                }
            }
            else
            {
                std::vector<std::string> arguments(argv + 2, argv + argc);
                return iter->second->Run(arguments);
            }
        }
        return 1;
    }
    
    void Programs::AddProgram(std::unique_ptr<Program>&& program)
    {
        auto prog = program.get();
        auto emplaceResult = m_programs.try_emplace(prog->Name(), std::move(program));
        if (!emplaceResult.second)
        {
            throw std::runtime_error("duplicate program: " + prog->Name());
        }
    }
}