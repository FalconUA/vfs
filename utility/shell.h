#ifndef __VIRTUAL_UTILITY_SHELL_HEADER__
#define __VIRTUAL_UTILITY_SHELL_HEADER__

#include <string>
#include <map>
#include <iostream>
#include <algorithm>
#include "../virtualfs.h"
#include "../virtualos.h"

namespace virt {
namespace util {

	class shell: public virt::os::utility {
	public:
		virt::filesystem::dir_iterator shell_iterator;

		shell(virt::operatingsystem* os):
				utility(os), shell_iterator(os->fs.root()) {
			description = "Создаёт виртуальную консоль, через которой можно запускать утилиты в данной виртуальной системе. Для детальной информации пропишите 'help shell'.\n";

			help_text = description + "Синтаксис: shell [shellname], где [shellname] (пишите без квадратных скобочек) это необязательный параметр, который задаёт название нового консоля. Для выхода из текущего консоля просто пропишите 'exit'.\n";
		}

		void process_command(std::string appname, std::string command){
			if (working_os->app(appname) == NULL)
				return ;
			std::string output = working_os->app(appname)->launch(command);
			std::cout << output;
		}

		std::string launch(std::string param){
			std::string command;

			std::cout << "[" << param << "]~> ";
			while (std::getline(std::cin, command)){
				if (command == "exit")
					break;

				std::size_t p = std::min(command.find(' '), command.length());	
				std::string appname = command.substr(0, p);
				command.erase(0, p+1);
				process_command(appname, command);
				std::cout << "[" << param << "]~> ";
			}
			return "";
		}
	};

} // end of namespace util
} // end of namespace virt

#endif
