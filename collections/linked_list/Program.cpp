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

#include <collections/linked_list/LinkedList.hpp>
#include <programs/Program.hpp>
#include <programs/Programs.hpp>

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>

namespace
{
    using CppSamples::Program;
    using CppSamples::Collections::LinkedList;

    class LinkedListProgram : public Program
    {
    public:
        LinkedListProgram()
            : Program("LinkedList", "Modifying and printing a linked list")
        {
        }

        int Run(std::vector<std::string> & args) override
        {
            size_t listSize = 1;

            std::cout << "the list contains a single empty string initially\n";

            LinkedList<std::string> list;
            list.EmplaceFront("");
            
            auto iterator = list.begin();

            while(true)
            {
                std::cout << ("Enter the command: ("
                    "e: exit; "
                    "i: insert element after current one; "
                    "f: move iterator forward; "
                    "p: print the list; "
                    "r: reset the iterator to start; "
                    "c: print current element)\n");

                char c;
                std::cin >> c;
                switch(c)
                {
                case 'e':
                    return 0;
                case 'i':
                {
                    if (iterator != list.end())
                    {
                        std::string value;
                        std::cout << "enter the string to insert\n";
                        std::cin >> value;
                        list.EmplaceAfter(iterator, std::move(value));
                    }
                    else
                    {
                        std::cerr << "current position is the end of the list; cannot insert an element there\n";
                    }
                    break;
                }
                case 'f':
                    if (iterator != list.end())
                    {
                        ++iterator;
                    }
                    else
                    {
                        std::cerr << "iterator already at the end of the list\n";
                    }
                    break;
                case 'p':
                {
                    for (auto& value : list)
                    {
                        std::cout << std::quoted(value) << ", ";
                    }
                    std::cout << '\n';
                    break;
                }
                case 'r':
                    iterator = list.begin();
                    break;
                case 'c':
                    if (iterator == list.end())
                    {
                        std::cerr << "at end of the list cannot be printed\n"; 
                    }
                    else
                    {
                        std::cout << std::quoted(*iterator) << '\n';
                    }
                    break;
                }

            }
        }
    };

    CPP_SAMPLES_REGISTER_PROGRAM(LinkedListProgram)
}
