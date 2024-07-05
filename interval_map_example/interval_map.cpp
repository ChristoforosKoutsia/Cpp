#include <iostream>
#include <map>
#include <limits>

// interval_map class definition
template<typename K, typename V>


class interval_map {
public:
    std::map<K, V> m_map;


    // constructor associates whole range of K with val by inserting (K_min, val)
    // into the map
    interval_map(V const& val) {
        m_map.insert(m_map.end(), std::make_pair(std::numeric_limits<K>::lowest(), val));
    }

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    void assign(K const& keyBegin, K const& keyEnd, V const& val) {
        if (!(keyBegin < keyEnd))
            return;

        typename std::map<K, V>::iterator iterBegin; /*The new begin with val, can be begin()*/
        typename std::map<K, V>::iterator iterEnd;   /*the new end of val, can be end()*/

        auto lowerKeyBegin = m_map.lower_bound(keyBegin); //either end() or some iter whose key is not less than keyBegin. [1st O(logN)]
        auto upperKeyEnd = m_map.upper_bound(keyEnd); //some iter where keyEnd < key, or end()  [2nd O(logN)]
        auto prevKeyEnd = std::prev(upperKeyEnd);

        /*
        The next interval of the new interval starts at keyEnd if the previous value at keyEnd differed from val
        */
        if (!(prevKeyEnd->second == val))
        {
            // prevKeyEnd is either less than the new end we are inserting, or the same (no update to avoid copying from erased node)
            if (!(prevKeyEnd->first < keyEnd) && !(keyEnd < prevKeyEnd->first))
                iterEnd = prevKeyEnd;
            else
                iterEnd = m_map.insert_or_assign(upperKeyEnd, keyEnd, prevKeyEnd->second);
        }
        else
        {
            iterEnd = upperKeyEnd;
        }

        /*
        The new interval starts at keyBegin if the would-be previous interval has a different value.
        Previous interval is either a key in the map less than keyBegin, or non-existent when lower_bound is m_map.begin()
        The new interval's start is merged with previous interval, if the previous interval has the same value.
        */
        if (lowerKeyBegin != m_map.begin())
        {
            auto prevIter = std::prev(lowerKeyBegin); //safe when end(), because we always have at least one value
            if (!(prevIter->second == val))
            {
                iterBegin = m_map.insert_or_assign(lowerKeyBegin, keyBegin, val);
            }
            else iterBegin = prevIter;
        }
        else
        {
            iterBegin = m_map.insert_or_assign(lowerKeyBegin, keyBegin, val);
        }

        /*
        Erase all keys between the new begin and end (excluding) so that there is only one value after iterBegin
        This is fine when iterEnd is end()
        */
        {
            if (std::next(iterBegin) != m_map.end())
            {
                //I would be very interested in a smarter way to get rid of this part without additional storage ...
                m_map.erase(nextIterOfBegin, iterEnd); 
            }
        }

        // //debug - check canonical
        // for (auto iter = m_map.begin(); iter != m_map.end(); ++iter)
        // {
        //  auto next = std::next(iter);
        //  if (next != m_map.end() && iter->second == next->second)
        //  {
        //      throw;
        //  }
        // }
    }

    // look-up of the value associated with key
    V const& operator[](K const& key) const {
        return (--m_map.upper_bound(key))->second;
    }

};

// Main function to test interval_map
int main() {
    // Create an interval map with initial value 'A'
    interval_map<int, char> imap('A');

    // Assign intervals
    imap.assign(1, 5, 'B');
    imap.assign(6, 10, 'C');
    imap.assign(2, 7, 'D');
    //imap.assign(6, 7, 'B');
    //imap.assign(10, 12, 'D');

    // Print the current state of the interval map
    //imap.print();
    for (int i = -13; i<13;++i)
    {
         std::cout<<imap[i]<<std::endl;
    }
   

    return 0;
}
