#ifndef __MISERVER_POOL_HPP
#define __MISERVER_POOL_HPP
#include <vector>
#include <algorithm>
#include <cstdint>
namespace mimp
{
    namespace internal
    {
        template <class T>
        class CPool
        {
        public:
            CPool(uint16_t size) : m_vecPool(size, nullptr), m_wSize(size)
            {
            }

            uint16_t GetMax(void)
            {
                return this->m_wSize;
            }

            void DeleteAt(const uint16_t idx)
            {
                if (idx < this->m_wSize)
                {
                    delete this->m_vecPool[idx];
                    this->m_vecPool[idx] = nullptr;
                }
            }

            bool InsertAt(const uint16_t idx, T *elem)
            {
                if (idx < this->m_wSize)
                {
                    this->m_vecPool[idx] = elem;
                    return true;
                }
                else
                {
                    return false;
                }
            }

            int Insert(T *elem)
            {
                auto it = std::find(this->m_vecPool.begin() + 1, this->m_vecPool.end(), nullptr);
                if (it == this->m_vecPool.end())
                {
                    return -1;
                }
                size_t idx = std::distance(this->m_vecPool.begin(), it);
                this->m_vecPool[idx] = elem;
                return idx;
            }

            T *GetAt(uint16_t idx)
            {
                if (idx < this->m_wSize)
                {
                    return this->m_vecPool.at(idx);
                }
                else
                {
                    return nullptr;
                }
            }

            uint16_t GetCount(void)
            {
                return std::count_if(this->m_vecPool.begin(), this->m_vecPool.end(), [](T *elem)
                                     { return elem != nullptr; });
            }
            auto begin()
            {
                return m_vecPool.begin();
            }

            auto end()
            {
                return m_vecPool.end();
            }

            auto begin() const
            {
                return m_vecPool.begin();
            }

            auto end() const
            {
                return m_vecPool.end();
            }

            void Clear() {
                for (T*& element : m_vecPool) {
                    delete element;
                    element = nullptr;
                }
            }

        private:
            std::vector<T *> m_vecPool;
            uint16_t m_wSize;
        };
    }
}
#endif