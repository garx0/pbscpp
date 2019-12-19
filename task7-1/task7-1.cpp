template <char ...c>
struct TString {
};

template <char ...c, char ...d>
constexpr TString<c..., d...> operator+(const TString<c...>&, const TString<d...>&) {
    return TString<c..., d...>();
}

template <char h1, char ...c, char h2, char ...d>
constexpr bool operator==(const TString<h1, c...>& lhs, const TString<h2, d...>& rhs) {
    return h1 == h2 && sizeof...(c) == sizeof...(d) && TString<c...>() == TString<d...>();
}

constexpr bool operator==(const TString<>& lhs, const TString<>& rhs) {
    return true;
}

// c++14+
template <typename T, T ...c>
constexpr TString<c...> operator"" _s() {
    return TString<c...>();
}

int main() {
    constexpr auto hello = "hello"_s + " world"_s;
    static_assert(hello == "hello world"_s);
};