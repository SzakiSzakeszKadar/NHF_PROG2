#ifndef PAIR_HPP
#define PAIR_HPP
/**
 * Pár struktúra sablon definíciója.
 */
template <typename T1, typename T2>
struct Pair {
    T1 first;
    T2 second;
    /**
     * Pár struktúra konstruktora.
     */
    Pair() = default;
    /**
    * Pár struktúra konstruktora az első és második elemekkel.
    */
    Pair(const T1& first, const T2& second) : first(first), second(second) {}
};

/**
 * Pár struktúra sablonhoz tartozó make_pair függvény.
 */
template <typename T1, typename T2>
Pair<T1, T2> make_pair(const T1& first, const T2& second) {
    return Pair<T1, T2>(first, second);
}

#endif // PAIR_HPP
