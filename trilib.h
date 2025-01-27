#include <bitset>

constexpr int M(1 << 21);

/* Oczekujemy od uczestnika zaimplementowania poniższych funkcji: */
void mainA(std::bitset<M> A, int n, int subtask);
void mainH(std::bitset<M> B, int n, int subtask);

/* Biblioteczka wystawia uczestnikowi następujące funkcje: */
void send(bool x);
bool receive();
void answer(int x);
