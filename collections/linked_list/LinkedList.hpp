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

#include <iterator>

namespace CppSamples::Collections
{

    template <typename T>
    class LinkedList
    {
    public:
        class Iterator;

        Iterator begin()
        {
            return m_head;
        }

        Iterator end()
        {
            return {};
        }

        /**
         * \brief insert a new object after a given iterator position using \p args as constructor parameters
         */
        template <typename... Args>
        inline T& EmplaceAfter(Iterator const &iter, Args &&...args)
        {
            Node *node = new Node(std::forward<Args>(args)...);
            node->m_next = iter.m_node->m_next;
            iter.m_node->m_next = node;
            return node->m_value;
        }

        /**
         * \brief insert a new object at the start of the list \p args as constructor parameters
         */
        template <typename... Args>
        inline T &EmplaceFront(Args &&...args)
        {
            Node *node = new Node(std::forward<Args>(args)...);
            node->m_next = m_head;
            m_head = node;
            return node->m_value;
        }

    private:
        struct Node
        {
            template <typename... Args>
            Node(Args &&...args)
                : m_value(std::forward<Args>(args)...)
            {
            }

            T m_value;
            Node *m_next{nullptr};
        };

        Node *m_head{nullptr};
    };

    template<typename T>
    class LinkedList<T>::Iterator
    {
    public:
        using difference_type = std::nullptr_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;
        using iterator_category = std::forward_iterator_tag;

        reference operator*()
        {
            return m_node->m_value;
        }

        pointer operator->()
        {
            return &m_node->m_value;
        }

        Iterator &operator++()
        {
            m_node = m_node->m_next;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator result = *this;
            m_node = m_node->m_next;
            return result;
        }

        bool operator==(Iterator const &other) const noexcept
        {
            return m_node == other.m_node;
        }

        bool operator!=(Iterator const &other) const noexcept
        {
            return !operator==(other);
        }

        // iterator should be copyable
        Iterator &operator=(Iterator const &) = default;
        Iterator(Iterator const &) = default;

    private:
        Iterator(Node *node = nullptr)
            : m_node(node)
        {
        }

        Node *m_node;
        friend class LinkedList<T>;
    };
}