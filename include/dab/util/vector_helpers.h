#ifndef DABIP_UTIL_VECTOR_HELPERS
#define DABIP_UTIL_VECTOR_HELPERS

#include <vector>
#include <utility>
#include <algorithm>

namespace dab
  {

  namespace internal
    {
    /**
     * @author Tobias Stauber
     *
     * @param[out] left Vector left concatenated with vector right.
     * @brief Concatenates right vector to left vector. This alters left vector.
     */
    template<typename T>
      void concat_vectors_inplace(std::vector<T> & left, std::vector<T> const & right)
        {
        left.reserve(left.size() + right.size());
        for(T t : right)
          {
          left.push_back(t);
          }
        }

    /**
     * @author Tobias Stauber
     *
     * @param[out] first Vector first concatenated with second and third.
     * @brief Concatenates second vector and third vector to first vector. This alters the first vector.
     */
    template<typename T>
      void concat_vectors_inplace(std::vector<T> & first, std::vector<T> const & second, std::vector<T> const & third)
        {
        first.reserve(first.size() + second.size() + third.size());
        for(T t : second)
          {
          first.push_back(t);
          }
        for(T t : third)
          {
          first.push_back(t);
          }
        }

    /**
     * @author Tobias Stauber
     *
     * @return A new vector containing the contents of left and right.
     */
    template<typename T>
      std::vector<T> concat_vectors(std::vector<T> const & left, std::vector<T> const & right)
        {
        auto concatenated = std::vector<T>();
        for(T t: left)
          {
          concatenated.push_back(t);
          }
        for(T t: right)
          {
          concatenated.push_back(t);
          }
        return concatenated;
        }

    /**
     * @author Tobias Stauber
     *
     * @return [begin, position] of input as first and ]position, last] of input as second
     */
    template<typename T>
      std::pair<std::vector<T>, std::vector<T>> split_vector(std::vector<T> const & input, typename std::vector<T>::size_type const position)
        {
        return std::make_pair<std::vector<T>, std::vector<T>>(std::vector<T>{input.begin(), input.begin()+position}, std::vector<T>{input.begin()+position, input.end()});
        }
    }

  }

#endif
