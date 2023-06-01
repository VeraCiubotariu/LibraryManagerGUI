#pragma once
#include <string>

class StandardError {
private:
	std::string message;

public:
	StandardError(std::string mess) {
		this->message = mess;
	}

	const std::string& getMessage() noexcept {
		return message;
	}
};

class ValidationError: public StandardError {
public:
	ValidationError(std::string message) : StandardError(message) {
	}
};

class RepositoryError :public StandardError {
public:
	RepositoryError(std::string message) : StandardError(message) {}
};

class ServiceError : public StandardError {
public:
	ServiceError(std::string message) : StandardError(message) {
	}
};