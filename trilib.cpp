#include "trilib.h"

#include "communication.h"

// ============ CONFIG ============
typedef bool DATA_TYPE;
typedef int ANSWER_TYPE;

constexpr size_t PIPE_BUFFER_SIZE = 1048576;
constexpr int MESSAGE_LIMIT = 1 << 11;

constexpr std::string_view CHILD_A_NAME = "A";
constexpr std::string_view CHILD_B_NAME = "H";
// ============ END CONFIG ============

using Comm = Communication<DATA_TYPE, ANSWER_TYPE>;

namespace {

Comm com;

std::bitset<M> _A, _B;
int _n, _correct, _subtask;

void readInput() {
    int prefix, seed;
    std::cin >> prefix >> seed;
    std::mt19937 _rng(seed);
    _A.reset();
    _B.reset();
    int S = 0;
    for (int i = 0; i < prefix; ++i) {
        int a = _rng() % 2, b = _rng() % 2;
        _A[i] = a;
        _B[i] = b;
        S += a + b;
    }
    if (prefix > 16) _subtask++;
    if (prefix > 2048) _subtask++;
    _n = (int)(_rng() % (unsigned long)S + 1);
    int _p = _n;
    _correct = -1;
    do {
        ++_correct;
        if (_A[_correct]) --_p;
        if (_B[_correct]) --_p;
    } while (_p > 0);
}

}  // namespace

template <>
std::string Comm::printData(const DATA_TYPE &data) {
    std::stringstream s;
    s << data;
    return s.str();
}

template <>
void Comm::runA() {
    mainA(_A, _n, _subtask);
}

template <>
void Comm::runB() {
    mainH(_B, _n, _subtask);
}

void answer(ANSWER_TYPE x) { com.answer(x); }
void send(DATA_TYPE b) { com.userSend(b); }
DATA_TYPE receive() { return com.userReceive(); }

int main() {
    readInput();

    com.forkAndRunChildren();

    try {
        auto [answer, messages, _] = com.masterMain();
        com.printExitMessage(ExitType::ANSWER, answer, _correct, messages);
        std::cout << "odpowiednio <ODPOWIEDŹ_PROGRAMU> <POPRAWNA_ODPOWIEDŹ> <LICZBA_UŻYTYCH_BITÓW>" << std::endl;
    } catch (const CommunicationError &e) {
        com.panic(ErrorType::COMMUNICATION_ERROR);
    }
    return 0;
}
