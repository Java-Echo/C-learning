int lowbit(int x) {
    return x & -x;
}
// int x = 5
// 0b 0000 0101 &
// 0b 1111 1011 =
// 0b 0000 0001