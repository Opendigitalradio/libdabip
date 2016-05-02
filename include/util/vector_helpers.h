#ifndef __DABIP_UTIL__VECTOR_HELPERS
#define __DABIP_UTIL__VECTOR_HELPERS

#include <vector>
#include <utility>
#include <algorithm>

namespace dabip {

  template<typename T>
    void concat_vectors_inplace(std::vector<T> & left, std::vector<T> const & right)
      {
      if(left.capacity() < left.size() + right.size())
        {
        left.reserve(left.size() + right.size());
        }
      std::copy(right.begin(), right.end(), back_inserter(left));
      }

  template<typename T>
    void concat_vectors_inplace(std::vector<T> & first, std::vector<T> const & second, std::vector<T> const & third)
      {
      if(first.capacity() < first.size() + second.size() + third.size())
        {
        first.reserve(first.size() + second.size() + third.size());
        }
      std::copy(second.begin(), second.end(), back_inserter(first));
      std::copy(third.begin(), third.end(), back_inserter(first));
      }

  template<typename T>
    std::vector<T> concat_vectors(std::vector<T> const & left, std::vector<T> const & right)
      {
      auto concatenated = std::vector<T>(left.capacity());
      std::copy(left.begin(), left.end(), back_inserter(concatenated));
      std::copy(right.begin(), right.end(), back_inserter(concatenated));
      return concatenated;
      }

  template<typename T>
    /**
     * @author Tobias Stauber
     *
     * @return [0, position] as first and ]position, input.size()-1]
     */
    std::pair<std::vector<T>, std::vector<T>> split_vector(std::vector<T> const & input, typename std::vector<T>::size_type const position)
      {
      return std::make_pair<std::vector<T>, std::vector<T>>(std::vector<T>{input.begin(), input.begin()+position}, std::vector<T>{input.begin()+position, input.end()});
      }
}

#endif // __DABIP_UTIL__VECTOR_HELPERS
