#ifndef SETEXCEPTION_H
#define SETEXCEPTION_H

#include <stdexcept>
#include <string>

class set_exception : public std::runtime_error {
public:
	/**
		Costruttore che prende un messaggio d'errore
	*/
	set_exception(const std::string &message);
};

#endif