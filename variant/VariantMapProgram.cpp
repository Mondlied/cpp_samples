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

#include <programs/Program.hpp>
#include <programs/Programs.hpp>

#include <iomanip>
#include <iostream>
#include <variant>
#include <string>
#include <map>

namespace
{
    template<typename VType>
    class Wrapper
    {
    public:
        using ValueType = VType;

        template<typename...Args>
        Wrapper(Args&&...args)
            : m_value(std::forward<Args>(args)...)
        {}

        ValueType& Value()
        {
            return m_value;
        }
    private:
        ValueType m_value;
    };

    template<typename...WrappedTypes>
    using WrapperVariant = std::variant<Wrapper<WrappedTypes>...>;

    void PrintEntry(std::string const& key, std::string const& value)
    {
        std::cout << "mapping to string: " << std::quoted(key) << " -> " << std::quoted(value) << '\n';
    }
    
    void PrintEntry(std::string const& key, float value)
    {
        std::cout << "mapping to float: " << std::quoted(key) << " -> " << value << '\n';
    }

    void PrintEntry(std::string const& key, int value)
    {
        std::cout << "mapping to int: " << std::quoted(key) << " -> " << value << '\n';
    }

    class VariantMapProgram : public CppSamples::Program
    {
    public:
        VariantMapProgram()
            : Program("VariantMap", "Map of variants")
        {
        }

        int Run(std::vector<std::string> & args) override
        {
            std::map<std::string, WrapperVariant<std::string, float, int>> map;
            while(true)
            {
                std::cout << ("Enter the command: ("
                    "e: exit; "
                    "f: insert float; "
                    "i: insert int; "
                    "s: insert string; "
                    "p: print)\n");

                char c;
                std::cin >> c;
                switch(c)
                {
                case 'e':
                    return 0;
                case 'f':
                case 'i':
                case 's':
                {
                    std::string key;
                    std::cout << "enter key\n";
                    std::cin >> key;

                    std::cout << "enter value\n";
                    switch(c)
                    {
                        case 'f':
                        {
                            float value;
                            std::cin >> value;
                            map[key] = Wrapper<float>(value);
                            break;
                        }
                        case 'i':
                        {
                            int value;
                            std::cin >> value;
                            map[key] = Wrapper<int>(value);
                            break;
                        }
                        case 's':
                        {
                            std::string value;
                            std::cin >> value;
                            map[key] = Wrapper<std::string>(value);
                            break;
                        }
                    }
                    break;
                }
                case 'p':
                {
                    std::cout << "Content of the map:\n\n";
                    for (auto&[key, value] : map)
                    {
                        std::visit([&key](auto& value){ PrintEntry(key, value.Value()); }, value);
                    }
                    std::cout << '\n';
                    break;
                }
                default:
                    std::cout << "invalid input\n";
                }

            }
        }
    };

    CPP_SAMPLES_REGISTER_PROGRAM(VariantMapProgram)
}
