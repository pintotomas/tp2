#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

class ClosedQueueException : public std::exception {
};

class NoMoreFutureResourcesException : public std::exception {
};

#endif
