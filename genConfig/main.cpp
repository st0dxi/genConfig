#include <iostream>
#include <fstream>
#include <string>
#include <regex>



int main()
{

	std::cout << "config start" << std::endl;

	std::string fileConf("configuration.yml");

	std::string indentation = "  "; // ne comprend pas les \t T-T

	std::ofstream configuration;
	configuration.open(fileConf, std::ios_base::out);


	std::regex contrIP("[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}");
	std::regex contrPort("[0-9]{1,5}");

	int roleNB;
	std::string inputString;

	//role

	do {
		std::cout << "what is your role : " << std::endl << "\t(1) brainer" << std::endl << "\t(2) asker" << std::endl << "\t(3) memory" << std::endl;
		std::cin >> roleNB;
	} while (roleNB == NULL || roleNB < 1 || roleNB > 3);

	switch (roleNB)
	{
	case 1:
		inputString = "brainer";
		break;
	case 2:
		inputString = "asker";
		break;
	case 3:
		inputString = "memory";
		break;
	default:
		return -1;
	}

	configuration << "role : " << inputString << std::endl;

	// rabitmq

	do {
		std::cout << "what is rabitmq ip (V4)" << std::endl;
		std::cin >> inputString;
	} while (!std::regex_match(inputString, contrIP) && inputString != "localhost");

	configuration << "rabbitmq:" << std::endl << indentation << "host: " << inputString << std::endl;

	do {
		std::cout << "what is rabbitmq port (default : 5672)" << std::endl;
		std::cin >> inputString;
	} while (!std::regex_match(inputString, contrPort) || inputString.empty());

	if (inputString.empty()) {
		inputString = "5672";
	}

	configuration << indentation  << "port: " << inputString << std::endl;

	std::cout << "what is user rabitmq name" << std::endl;
	std::cin >> inputString;

	configuration << indentation << "credentials:" << std::endl << indentation << indentation << "username: " << inputString << std::endl;

	std::cout << "what is user rabbitmq password" << std::endl;
	std::cin >> inputString;

	configuration << indentation << indentation << "password: " << inputString << std::endl;

	if (roleNB == 3) {
		// mongodb

		do {
			std::cout << "what is mongodb ip (V4)" << std::endl;
			std::cin >> inputString;
		} while (!std::regex_match(inputString, contrIP) && inputString != "localhost");

		configuration << "mongodb:" << std::endl << indentation << "host: " << inputString << std::endl;

		do {
			std::cout << "what is mongodb port (default : 2707)" << std::endl;
			std::cin >> inputString;
		} while (!std::regex_match(inputString, contrPort) || inputString.empty());

		if (inputString.empty()) {
			inputString = "27017";
		}

		configuration << indentation << "port: " << inputString << std::endl;

		std::cout << "what is user mongodb name" << std::endl;
		std::cin >> inputString;

		configuration << indentation << "credentials:" << std::endl << indentation << indentation << "username: " << inputString << std::endl;

		std::cout << "what is user mongodb password" << std::endl;
		std::cin >> inputString;

		configuration << indentation << indentation << "password: " << inputString << std::endl;

		std::cout << "what is database mongodb for connect user" << std::endl;
		std::cin >> inputString;

		configuration << indentation << indentation << "authSource: " << inputString << std::endl;

		std::cout << "what is connection mechanism for mongodb (defalut : SCRAM-SHA-256)" << std::endl;
		std::cin >> inputString;

		configuration << indentation << indentation << "authMechanism: " << inputString << std::endl;

		std::cout << "what is database use for mongodb (default brainers_db)" << std::endl;
		std::cin >> inputString;

		configuration << indentation << "database: " << inputString << std::endl;

		std::cout << "what is collection use for mongodb (default questions)" << std::endl;
		std::cin >> inputString;

		configuration << indentation << "questions: " << inputString << std::endl;

	}

    return 0;
}