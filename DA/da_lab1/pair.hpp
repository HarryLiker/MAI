#pragma once

namespace NPair {
    template<class T1, class T2>
    class TPair {
    public:
        T1 Key; // Ключ
        T2 Value; // Значение
        TPair() {}
        TPair(T1 k, T2 v): Key(k), Value(v) {}
        ~TPair() {}
    };
} // namespace NPair